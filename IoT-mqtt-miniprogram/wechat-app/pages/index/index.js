var mqtt = require('../../utils/mqtt.min.js')
const crypto = require('../../utils/hex_hmac_sha1.js')
var client;

/*
项目说明：
参考博客地址：https://blog.csdn.net/Koevas/article/details/103684222
正式发布小程序时，请在 项目配置 - socket合法域名  填上自己的阿里云连接
例如：wxs://a1UlGaNaaa.iot-as-mqtt.cn-shanghai.aliyuncs.com  (要改为自己的!!)
如果未修改阿里云三元组，项目里的三元组是连不上，而且会有提示xxx不在合法域名中
*/

Page({
  data: {
    img_url3: "/img/laser.png",
    img_url: "/img/stick.png",
    img_url2: "/img/ball.png",
    password_input:"",
    key:"123456",
    login: false,
    button_clicking: false,
    iot_connect: false,
    connect_text: "未连接",
  },

  doConnect() {
    var that = this;
    // 下面的信息要换成自己的阿里云三元组
    const deviceConfig = {
      productKey: "xxxxxx",
      deviceName: "xx",
      deviceSecret: "",
      regionId: "cn-shanghai"
    };
    const options = this.initMqttOptions(deviceConfig);
    console.log(options)
    //替换productKey为你自己的产品的
    client = mqtt.connect('wxs://xxxxxx.iot-as-mqtt.cn-shanghai.aliyuncs.com', options)
    client.on('connect', function () {
      that.setData({
        connect_text: "连接服务器成功",
        iot_connect: true
      })

      //订阅主题，替换productKey和deviceName(这里的主题可能会不一样，具体请查看后台设备Topic列表或使用自定义主题)
      // client.subscribe('', function (err) {
      //   if (!err) {
      //     console.log('订阅成功！');
      //   }
      // })
    })
    //接收消息监听
    client.on('message', function (topic, message) {
      // message is Buffer
      console.log('收到消息：' + message.toString())
      //关闭连接 client.end()
    })
  },
  //IoT平台mqtt连接参数初始化
  initMqttOptions(deviceConfig) {
    const params = {
      productKey: deviceConfig.productKey,
      deviceName: deviceConfig.deviceName,
      timestamp: Date.now(),
      clientId: Math.random().toString(36).substr(2),
    }
    //CONNECT参数
    const options = {
      keepalive: 60, //60s
      clean: true, //cleanSession不保持持久会话
      protocolVersion: 4 //MQTT v3.1.1
    }
    //1.生成clientId，username，password
    options.password = this.signHmacSha1(params, deviceConfig.deviceSecret);
    options.clientId = `${params.clientId}|securemode=2,signmethod=hmacsha1,timestamp=${params.timestamp}|`;
    options.username = `${params.deviceName}&${params.productKey}`;

    return options;
  },

  command_stick(res){
    let value = res.currentTarget.dataset.value
    if(!this.data.button_clicking && this.data.iot_connect){
      this.button_style()
      
      var connectText = value
      client.publish('/xxxxxx/xx/user/update', connectText, function (err){
        if (!err) {
          console.log('');
        }
      })
    }
  },



  button_style(){
    var that = this
    this.openHalfMini()
    this.setData({
     // img_url: "/img/jiguang.png",
      button_clicking: true
    })

    
    setTimeout(function(){
      that.setData({
      //  img_url: "/img/dou.png",
        button_clicking: false
        
      })
    }, 10)
  },

  /*
    生成基于HmacSha1的password
    参考文档：https://help.aliyun.com/document_detail/73742.html?#h2-url-1
  */
  signHmacSha1(params, deviceSecret) {

    let keys = Object.keys(params).sort();
    // 按字典序排序
    keys = keys.sort();
    const list = [];
    keys.map((key) => {
      list.push(`${key}${params[key]}`);
    });
    const contentStr = list.join('');
    return crypto.hex_hmac_sha1(deviceSecret, contentStr);
  },

  
})


