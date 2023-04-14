# coding:utf-8
import asyncio
import zlib
import json
import sys
import yaml

from aiowebsocket.converses import AioWebSocket

import serial

cfg = yaml.load(open(sys.path[0] + '/dm_cfg.yaml', 'r', encoding='utf-8').read(), Loader=yaml.FullLoader)

ser = serial.Serial(port=cfg['serial_port'],
                    baudrate=115200,
                    timeout=0.5)

KEYS = {'ball': [0xA5, 0xA5, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00],
        'laser': [0xA5, 0xA5, 0x05, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00],
        'stick': [0xA5, 0xA5, 0x0A, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00]}


status_counter = {'ball': 0,
                  'laser': 0,
                  'stick': 0}


def statusWrite():
    global status_counter
    max_p = max(zip(status_counter.values(), status_counter.keys()))
    if max_p[0] > 0:
        data = KEYS[max_p[1]]
        ser.write(bytes(data))
        print("\033[0;;42m[Publisher]\033[0m:   Use item: ", max_p[1], "  \033[0;36m[Counter]\033[0m: Clear")
    else:
        print("\033[0;;41m[Publisher]\033[0m:   No items are selected.  \033[0;36m[Counter]\033[0m: Clear")

    status_counter = {'ball': 0, 'laser': 0, 'stick': 0}


SER_WRITE_INTERVAL = cfg['serial_interval']


async def intervalSend():
    global status_counter
    while True:
        await asyncio.sleep(SER_WRITE_INTERVAL)
        statusWrite()


# DANMU Hunter
remote = 'ws://broadcastlv.chat.bilibili.com:2244/sub'
room_id = cfg['room_id']

data_raw = '000000{Header}0010000100000007000000017b22726f6f6d6964223a{ID}7d'
data_raw = data_raw.format(Header=hex(27 + len(room_id))[2:],
                           ID=''.join(map(lambda x: hex(ord(x))[2:], list(room_id))))


async def startUp():
    async with AioWebSocket(remote) as aws:
        converse = aws.manipulator
        await converse.send(bytes.fromhex(data_raw))
        task_heart_beat = asyncio.create_task(sendHeartBeat(converse))
        task_receive_package = asyncio.create_task(receivePackage(converse))
        task_serial_send = asyncio.create_task(intervalSend())
        await asyncio.wait({task_heart_beat,
                            task_receive_package,
                            task_serial_send})


heart_beat_msg = '00 00 00 10 00 10 00 01  00 00 00 02 00 00 00 01'
send_heart_beat_interval = 30


async def sendHeartBeat(_webscoket):
    while True:
        await asyncio.sleep(send_heart_beat_interval)
        await _webscoket.send(bytes.fromhex(heart_beat_msg))
        # print('[Notice] Sent HeartBeat.')


async def receivePackage(_webscoket):
    while True:
        recv_text = await _webscoket.receive()

        if recv_text == None:
            recv_text = b'\x00\x00\x00\x1a\x00\x10\x00\x01\x00\x00\x00\x08\x00\x00\x00\x01{"code":0}'

        parseData(recv_text)


# DANMU Hunter
def parseData(_data):
    # 获取数据包的长度，版本和操作类型
    packet_len = int(_data[:4].hex(), 16)
    ver = int(_data[6:8].hex(), 16)
    op = int(_data[8:12].hex(), 16)

    if len(_data) > packet_len:
        parseData(_data[packet_len:])
        _data = _data[:packet_len]
    if ver == 2:
        _data = zlib.decompress(_data[16:])
        parseData(_data)
        return
    if ver == 1:
        return

    if op == 5:
        global status_counter
        try:
            jd = json.loads(_data[16:].decode('utf-8', errors='ignore'))
            if jd['cmd'] == 'DANMU_MSG':
                msg = jd['info'][1]
                user = jd['info'][2][1]
                print("[DANMU_MSG]:   User: {}  Msg: {}".format(user, msg))
                if msg in KEYS.keys():
                    status_counter[msg] += 1
                    print("\033[0;36m[Counter]:   {} + 1\033[0m".format(msg))
                    print("\033[0;36m[Counter]\033[0m:   {}".format(status_counter))

        except Exception as e:
            pass


if __name__ == '__main__':
    try:
        loop = asyncio.get_event_loop()
        loop.run_until_complete(startUp())

    except KeyboardInterrupt as exc:
        print('Quit.')
