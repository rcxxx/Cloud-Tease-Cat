import threading

import cv2
import serial
import yaml
import sys
import logging

from yolov8_onnx import Model
from threading import Thread
thread_lock = threading.Lock()
thread_exit = False
class videoStream(Thread):
    def __init__(self, _cap=0):
        super(videoStream, self).__init__()
        self.cap = cv2.VideoCapture(_cap)
        self.ret, self.frame = self.cap.read()

    def getFrame(self):
        return self.frame
    def run(self):
        global thread_exit
        while not thread_exit:
            self.ret, self.frame = self.cap.read()
            # cv2.imshow('frame', self.frame)

        self.cap.release()

def main():
    global thread_exit
    cfg = yaml.load(open('cfg.yaml', 'r', encoding='utf-8').read(), Loader=yaml.FullLoader)
    t = videoStream(_cap=cfg['cap'])
    t.start()

    net = Model(sys.path[0] + '/models/yolov8s-480x.onnx', _size=(480,480))

    while not thread_exit:
        thread_lock.acquire()
        src_img = t.getFrame()
        thread_lock.release()

        detections = net.det(src_img)

        for i in range(len(detections)):
            detection = detections[i]
            id = detection['class_id']
            if id == 0:
                # Draw Person
                net.draw_bounding_box(src_img,
                                       detection['class_id'],
                                       detection['confidence'],
                                       round(detection['box'][0] * detection['scale']),
                                       round(detection['box'][1] * detection['scale']),
                                       round((detection['box'][0] + detection['box'][2]) * detection['scale']),
                                       round((detection['box'][1] + detection['box'][3]) * detection['scale']))

            if (id == 15 or id == 16):
                net.draw_bounding_box(src_img,
                                       15,  # only cat
                                       detection['confidence'],
                                       round(detection['box'][0] * detection['scale']),
                                       round(detection['box'][1] * detection['scale']),
                                       round((detection['box'][0] + detection['box'][2]) * detection['scale']),
                                       round((detection['box'][1] + detection['box'][3]) * detection['scale']))

        cv2.imshow('src_img', src_img)
        if cv2.waitKey(1) & 0xFF == 27:
            thread_exit = True
    t.join()

if __name__ == "__main__":
    main()
