import serial
import yaml
import cv2
import numpy as np

def main():
    cfg = yaml.load(open('cfg.yaml', 'r', encoding='utf-8').read(), Loader=yaml.FullLoader)
    ser = serial.Serial(port=cfg['serial_port'], baudrate=115200, timeout=0.5)
    img = np.zeros((100, 100), np.uint8)
    while True:
        cv2.imshow('image', img)
        key = cv2.waitKey(0)
        if key == 'f':
            # find cat
            data = [0xA5, 0xA5, 0x0A, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00]
            ser.write(bytes(data))
        elif key == 't':
            # tease cat
            data = [0xA5, 0xA5, 0x0A, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00]
            ser.write(bytes(data))
        elif key == 's':
            # stop
            data = [0xA5, 0xA5, 0x0A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00]
            ser.write(bytes(data))
        elif key &0xff == 27:
            break

if __name__ == "__main__":
    main()
