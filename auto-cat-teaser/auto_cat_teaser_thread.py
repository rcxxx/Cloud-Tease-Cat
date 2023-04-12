import logging
import cv2
import yaml
import sys
import serial
import threading
import time

from yolov8_onnx import Model

td_lock = threading.Lock()
td_exit = False

g_ctrl = {'tease': 0, 'find': 0, 'free': 0}


class videoStream(threading.Thread):
    def __init__(self, _cap=0, _record=0):
        super(videoStream, self).__init__()
        self.cap = cv2.VideoCapture(_cap)
        self.ret, self.frame = self.cap.read()
        self.record = _record
        if self.record:
            width, height = int(self.cap.get(cv2.CAP_PROP_FRAME_WIDTH)), int(self.cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
            import datetime
            now_t = datetime.datetime.now().strftime('%Y-%m-%d-%H-%M-%S')
            self.writer = cv2.VideoWriter(sys.path[0] + '/videos/' + now_t + '-record.mp4',
                                          cv2.VideoWriter_fourcc('M', 'P', '4', 'V'), 24, (width, height))

    def run(self):
        global td_exit
        while not td_exit:
            self.ret, self.frame = self.cap.read()
            if self.record:
                self.writer.write(self.frame)

        if self.record:
            self.writer.release()
        self.cap.release()

    def getFrame(self, _scale):
        return cv2.resize(self.frame, None, fx=_scale, fy=_scale)


class serialCTRL(threading.Thread):
    def __init__(self, _port, _interval):
        super(serialCTRL, self).__init__()
        self.port = _port
        self.interval = _interval

    def run(self):
        try:
            ser = serial.Serial(port=self.port, baudrate=115200, timeout=0.5)
            global td_exit
            while not td_exit:
                self.serialWrite(ser)
                time.sleep(self.interval)

            return
        except Exception as e:
            logging.warning(e)
            return

    def serialWrite(self, _ser):
        global g_ctrl
        td_lock.acquire()
        ctrl = g_ctrl
        print("\033[0;;42m[Publisher]\033[0m: CTRL Status:  ", ctrl)
        td_lock.release()
        if ctrl['find']:
            if ctrl['free'] < 4:
                ctrl['free'] += 1
                data = [0xA5, 0xA5, 0x0A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00]
                _ser.write(bytes(data))
            else:
                data = [0xA5, 0xA5, 0x0A, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00]
                _ser.write(bytes(data))
        elif ctrl['tease']:
            data = [0xA5, 0xA5, 0x0A, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00]
            _ser.write(bytes(data))
            td_lock.acquire()
            g_ctrl = {'tease': 0, 'find': 0, 'free': 0}
            td_lock.release()


def main():
    cfg = yaml.load(open(sys.path[0] + '/cfg.yaml', 'r', encoding='utf-8').read(), Loader=yaml.FullLoader)

    video_td = videoStream(_cap=cfg['cap'], _record=cfg['record'])
    video_td.start()
    serial_td = serialCTRL(_port=cfg['serial_port'], _interval=cfg['serial_interval'])
    serial_td.start()

    # yolo model
    net = Model(
        _classes_path=sys.path[0] + cfg['classes_path'],
        _model_path=sys.path[0] + cfg['model_path'],
        _size=(cfg['imgsz'], cfg['imgsz']),
        _is_cuda=cfg['is_cuda'])

    global td_exit
    while not td_exit:
        td_lock.acquire()
        src_img = video_td.getFrame(_scale=cfg['img_scale'])
        td_lock.release()

        have_cat = False
        # have_person = False
        # | OpenCV Predict | np.ndarray | HWC, BGR to RGB |
        rgb_img = src_img[:, :, ::-1]
        detections = net.det(rgb_img, _score_th=0.45, _NMS_th=0.45)
        for i in range(len(detections)):
            detection = detections[i]
            id = detection['class_id']
            name = net.CLASSES[id]
            if name == 'cat' or name == 'dog':
                have_cat = True
                draw_id = id if (name == 'cat') else (id - 1)
                net.draw_bounding_box(src_img,
                                      draw_id,  # only cat
                                      detection['confidence'],
                                      round(detection['box'][0] * detection['scale']),
                                      round(detection['box'][1] * detection['scale']),
                                      round((detection['box'][0] + detection['box'][2]) * detection['scale']),
                                      round((detection['box'][1] + detection['box'][3]) * detection['scale']),
                                      _color=(127, 255, 0))

            # if id == 0:
            #     have_person = True
            #     net.draw_bounding_box(src_img,
            #                        detection['class_id'],
            #                        detection['confidence'],
            #                        round(detection['box'][0] * detection['scale']),
            #                        round(detection['box'][1] * detection['scale']),
            #                        round((detection['box'][0] + detection['box'][2]) * detection['scale']),
            #                        round((detection['box'][1] + detection['box'][3]) * detection['scale']),
            #                        _color=(180, 130, 70))

        if have_cat:
            g_ctrl['find'] = 0
            g_ctrl['tease'] = 1
        else:
            g_ctrl['find'] = 1
            g_ctrl['tease'] = 0

        cv2.imshow('src', src_img)
        if cv2.waitKey(1) & 0xFF == 27:
            td_exit = True

    video_td.join()
    serial_td.join()


if __name__ == "__main__":
    main()
