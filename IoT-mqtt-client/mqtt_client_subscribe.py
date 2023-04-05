import yaml
import time
import sys
import json
import paho.mqtt.client as mqtt

cfg = yaml.load(open(sys.path[0] + '/mqtt_cfg.yaml', 'r', encoding='utf-8').read(), Loader=yaml.FullLoader)

productKey = cfg['productKey']
deviceName = cfg['deviceName']
deviceSecret = cfg['deviceSecret']
subTopic = "/" + productKey + "/" + deviceName + "/user/get"

clientId = cfg['clientId']
username = cfg['username']
mqttHostUrl = cfg['mqttHostUrl']
port = cfg['port']
passwd= cfg['passwd']

keepAlive = 300

import serial

ser = serial.Serial(port='/dev/ttyUSB0',
                    baudrate=115200,
                    timeout=0.5)

KEYS = {'小球':[0xA5, 0xA5, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00],
        '激光笔':[0xA5, 0xA5, 0x05, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00],
        '逗猫棒':[0xA5, 0xA5, 0x0A, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00]}

def connect_mqtt() -> mqtt:
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("[Connect]: Connected to MQTT Host! ......")
            print("[Connect]: Connect aliyun IoT Cloud Sucess")

        else:
            print("[Connect]: Connect failed...  error code is:" + str(rc))
    client = mqtt.Client(clientId)
    client.username_pw_set(username=username, password=passwd)
    client.on_connect = on_connect
    client.connect(mqttHostUrl, port, keepAlive)
    return client

def subscribe(client: mqtt):
    def on_message(client, userdata, msg):
        topic = msg.topic
        payload = msg.payload.decode()
        print("\033[0;;42m[Message]\033[0m: receive message ---------- topic is : " + topic)
        print("\033[0;;42m[Message]\033[0m: receive message ---------- payload is : " + payload)
        payload_dict = json.loads(payload)
        if 'stick' in payload_dict['params']:
            data = KEYS['逗猫棒']
            ser.write(bytes(data))
            print("\033[0;36m[Publisher]:  Use item: stick\033[0m")
        elif 'ball' in payload_dict['params']:
            data = KEYS['小球']
            ser.write(bytes(data))
            print("\033[0;36m[Publisher]:  Use item: ball\033[0m")
        elif 'laser' in payload_dict['params']:
            data = KEYS['激光笔']
            ser.write(bytes(data))
            print("\033[0;36m[Publisher]:  Use item: laser\033[0m")


    print("[Subscribe]: Waiting for reception")
    client.subscribe(subTopic)
    client.on_message = on_message

def run():
    client = connect_mqtt()
    client.loop_start()
    time.sleep(2)
    subscribe(client)
    while True:
        time.sleep(1)

if __name__ == '__main__':
    run()
