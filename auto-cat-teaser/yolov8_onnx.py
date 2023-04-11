import cv2
import numpy as np
import sys
import yaml

class Model:
    def __init__(self, _classes_path, _model_path, _size=(640,640), _is_cuda=True):
        self.model = cv2.dnn.readNetFromONNX(_model_path)
        if _is_cuda:
            self.model.setPreferableBackend(cv2.dnn.DNN_BACKEND_CUDA)
            self.model.setPreferableTarget(cv2.dnn.DNN_TARGET_CUDA);

        self.CLASSES = yaml.load(open(_classes_path, 'r', encoding='utf-8').read(), Loader=yaml.FullLoader)['names']
        self.size = _size
        self.colors = np.random.uniform(0, 255, size=(len(self.CLASSES), 3))
        # warm-up
        warmup_img = np.zeros((self.size[0], self.size[1], 3), dtype=np.uint8)
        self.det(warmup_img)

    def draw_bounding_box(self, _img, class_id, confidence, x, y, x_plus_w, y_plus_h, _color=None):
        label = f'{self.CLASSES[class_id]} ({confidence:.2f})'
        color = _color
        if color == None:
            color = self.colors[class_id]
        cv2.rectangle(_img, (x, y), (x_plus_w, y_plus_h), color, 2)
        cv2.putText(_img, label, (x - 10, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)

    def det(self, _img , _score_th=0.25, _NMS_th = 0.45):
        [height, width, _] = _img.shape
        length = max(height, width)
        img = np.zeros((length, length, 3), np.uint8)
        img[0:height, 0:width] = _img
        scale = length / self.size[0]
        blob = cv2.dnn.blobFromImage(img, scalefactor= 1/255, size=self.size)
        self.model.setInput(blob)
        outputs = self.model.forward()

        outputs = np.array([cv2.transpose(outputs[0])])
        rows = outputs.shape[1]

        boxes = []
        scores = []
        class_ids = []

        for i in range(rows):
            classes_scores = outputs[0][i][4:]
            (min_score, max_score, min_class_loc, (x, max_class_index)) = cv2.minMaxLoc(classes_scores)
            if max_score >= _score_th:
                box = [outputs[0][i][0] - (0.5 * outputs[0][i][2]),
                       outputs[0][i][1] - (0.5 * outputs[0][i][3]),
                       outputs[0][i][2],
                       outputs[0][i][3]]
                boxes.append(box)
                scores.append(max_score)
                class_ids.append(max_class_index)

        result_boxes = cv2.dnn.NMSBoxes(boxes, scores, _score_th, _NMS_th, 0.5)
        detections = []
        for i in range(len(result_boxes)):
            index = result_boxes[i]
            box = boxes[index]
            detection = {
                'class_id': class_ids[index],
                'class_name': self.CLASSES[class_ids[index]],
                'confidence': scores[index],
                'box': box,
                'scale': scale}
            detections.append(detection)

        return detections
