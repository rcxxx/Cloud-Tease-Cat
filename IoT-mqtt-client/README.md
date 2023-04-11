# 阿里云物联网平台与小程序 MQTT 连接

## 配置
所使用的物联网平台为阿里云物联网平台

根据已准备好的物联网平台设备信息，创建链接参数

- `mqtt_cfg.yaml` 文件中填入自己的平台信息

``` yaml title ="mqtt_cfg.yaml"
# DeviceSecret
productKey: ""
deviceName: ""
deviceSecret: ""

# MQTT Connection Parameters
clientId: ""
username: ""
mqttHostUrl: ""
port: 1883
passwd: ""
```

![]()

## 参考

- **[paho-mqtt](https://pypi.org/project/paho-mqtt/)**
- **[Paho-MQTT Python接入示例](https://help.aliyun.com/document_detail/438290.html?spm=a2c4g.146611.0.0.35fc31b7IbAeRf)**

