import yaml, time, sys
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
        print(f"Received `{payload}` from `{topic}` topic")

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
