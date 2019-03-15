// pages/detail/detail.js
Page({

    /**
     * 页面的初始数据
     */
    data: {
        connect: false,
        send_hex: false,
        send_string: false,
        send_string_val: 'Ascii',
        recv_string: false,
        recv_string_val: 'Ascii',
        recv_value: '',
        send_number: 0,
        recv_number: 0,
        recv_hex: false,
        yellowValue:200,
        whiteValue:200
    },

    /**
     * 生命周期函数--监听页面加载
     */
    onLoad: function (options) {
        wx.stopBluetoothDevicesDiscovery({
            success: function (res) {
                console.log('停止搜索设备', res)
            }
        })
        console.log(options);
        this.setData({
            deviceId: options.id,
            deviceName: options.name
        });
        console.log('设备的ID', this.data.deviceId);
    },

    /**
     * 生命周期函数--监听页面显示
     */
    onShow: function () {
        wx.stopBluetoothDevicesDiscovery({
            success: function (res) {
                console.log('停止搜索设备', res)
            }
        })
        var that = this;
        /* 连接中动画 */
        wx.showLoading({
            title: '连接中...',
        });
        /* 开始连接蓝牙设备 */
        wx.createBLEConnection({
            deviceId: that.data.deviceId,
            success: function (res) {
                console.log('连接成功', res);
                wx.hideLoading();
                /* 获取设备的服务UUID */
                wx.getBLEDeviceServices({
                    deviceId: that.data.deviceId,
                    success: function (service) {
                        var all_UUID = service.services;    //取出所有的服务
                        console.log('所有的服务', all_UUID);
                        var UUID_lenght = all_UUID.length;  //获取到服务数组的长度
                        /* 遍历服务数组 */
                        for (var index = 0; index < UUID_lenght; index++) {
                            var ergodic_UUID = all_UUID[index].uuid;    //取出服务里面的UUID
                            var UUID_slice = ergodic_UUID.slice(4, 8);   //截取4到8位
                            /* 判断是否是我们需要的FEE0 */
                            if (UUID_slice == 'FEE0' || UUID_slice == 'fee0') {
                                var index_uuid = index;
                                that.setData({
                                    serviceId: all_UUID[index_uuid].uuid    //确定需要的服务UUID
                                });
                            };
                        };
                        console.log('需要的服务UUID', that.data.serviceId)
                        that.Characteristics();     //调用获取特征值函数
                    },
                });
                that.setData({
                    connect: true
                })
            },
        })
    },

    Characteristics: function () {
        var that = this;
        var device_characteristics = [];
        var characteristics_uuid = {};
        wx.getBLEDeviceCharacteristics({
            deviceId: that.data.deviceId,
            serviceId: that.data.serviceId,
            success: function (res) {
                var characteristics = res.characteristics;      //获取到所有特征值
                var characteristics_length = characteristics.length;    //获取到特征值数组的长度
                console.log('获取到特征值', characteristics);
                console.log('获取到特征值数组长度', characteristics_length);
                /* 遍历数组获取notycharacteristicsId */
                for (var index = 0; index < characteristics_length; index++) {
                    var noty_characteristics_UUID = characteristics[index].uuid;    //取出特征值里面的UUID
                    var characteristics_slice = noty_characteristics_UUID.slice(4, 8);   //截取4到8位
                    /* 判断是否是我们需要的FEE1 */
                    if (characteristics_slice == 'FEE1' || characteristics_slice == 'fee1') {
                        var index_uuid = index;
                        that.setData({
                            notycharacteristicsId: characteristics[index_uuid].uuid,    //需确定要的使能UUID
                            characteristicsId: characteristics[index_uuid].uuid         //暂时确定的写入UUID
                        });
                        /* 遍历获取characteristicsId */
                        for (var index = 0; index < characteristics_length; index++) {
                            var characteristics_UUID = characteristics[index].uuid;    //取出特征值里面的UUID
                            var characteristics_slice = characteristics_UUID.slice(4, 8);   //截取4到8位
                            /* 判断是否是我们需要的FEE2 */
                            if (characteristics_slice == 'FEE2' || characteristics_slice == 'fee2') {
                                var index_uuid = index;
                                that.setData({
                                    characteristicsId: characteristics[index_uuid].uuid         //确定的写入UUID
                                });
                            };
                        };
                    };
                };
                console.log('使能characteristicsId', that.data.notycharacteristicsId);
                console.log('写入characteristicsId', that.data.characteristicsId);
                that.notycharacteristicsId();       //使能事件

            },
        })
    },

    /* 使能函数 */
    notycharacteristicsId: function () {
        var that = this;
        var recv_value_ascii = "";
        var string_value = "";
        var recve_value = "";
        wx.notifyBLECharacteristicValueChange({
            deviceId: that.data.deviceId,
            serviceId: that.data.serviceId,
            characteristicId: that.data.notycharacteristicsId,
            state: true,
            success: function (res) {
                console.log('使能成功', res);
                /* 设备返回值 */
                wx.onBLECharacteristicValueChange(function (res) {
                    var length_hex = [];
                    var turn_back = "";
                    var result = res.value;
                    var hex = that.buf2hex(result);
                    console.log('返回的值', hex);
                    if (that.data.recv_string == true) {
                        /* 成功接收到的值的展示 */
                        that.setData({
                            recv_value: that.data.recv_value + hex
                        });
                        /* 接收成功的值的字节 */
                        var recv_number_1 = that.data.recv_number + hex.length / 2;
                        var recv_number = Math.round(recv_number_1);
                        that.setData({
                            recv_number: recv_number
                        });
                    } else {
                        console.log('设备返回来的值', hex);
                        var f_hex = hex;
                        var length_soy = f_hex.length / 2;
                        var length = Math.round(length_soy);
                        for (var i = 0; i < length; i++) {
                            var hex_spalit = f_hex.slice(0, 2);
                            length_hex.push(hex_spalit);
                            f_hex = f_hex.substring(2);
                        }
                        console.log('length_hex', length_hex);
                        for (var j = 0; j < length_hex.length; j++) {

                            var integar = length_hex[j];    //十六进制
                            recve_value = parseInt(integar, 16);    //十进制
                            console.log('recve_value', recve_value);

                            turn_back = turn_back + String.fromCharCode(recve_value);
                            console.log('turn_back', turn_back);
                        }

                        console.log('最终转回来的值', turn_back)
                        var recv_number_1 = that.data.recv_number + turn_back.length;
                        var recv_number = Math.round(recv_number_1);
                        that.setData({
                            recv_number: recv_number,
                            recv_value: that.data.recv_value + turn_back
                        })
                    }
                });
            },

            fail: function (res) {
                console.log('使能失败', res);
            }
        })
    },

  write: function (str) {
        var that = this;
        var value = str;

        console.log('value', value);
        /* 将数值转为ArrayBuffer类型数据 */
        var typedArray = new Uint8Array(value.match(/[\da-f]{2}/gi).map(function (h) {
            return parseInt(h, 16)
        }));
        
        var buffer = typedArray.buffer;
        wx.writeBLECharacteristicValue({
            deviceId: that.data.deviceId,
            serviceId: that.data.serviceId,
            characteristicId: that.data.characteristicsId,
            value: buffer,
            success: function (res) {
                console.log('数据发送成功', res);
            },
            fail: function (res) {
                console.log('调用失败', res);
                /* 调用失败时，再次调用 */
                wx.writeBLECharacteristicValue({
                    deviceId: that.data.deviceId,
                    serviceId: that.data.serviceId,
                    characteristicId: that.data.characteristicsId,
                    value: buffer,
                    success: function (res) {
                        console.log('第2次数据发送成功', res);
                    },
                    fail: function (res) {
                        console.log('第2次调用失败', res);
                        /* 调用失败时，再次调用 */
                        wx.writeBLECharacteristicValue({
                            deviceId: that.data.deviceId,
                            serviceId: that.data.serviceId,
                            characteristicId: that.data.characteristicsId,
                            value: buffer,
                            success: function (res) {
                                console.log('第3次数据发送成功', res);
                            },
                            fail: function (res) {
                                console.log('第3次调用失败', res);
                            }
                        });
                    }
                });
            }
        });
    },

    /* 断开连接 */
    DisConnectTap: function () {
        var that = this;
        wx.closeBLEConnection({
            deviceId: that.data.deviceId,
            success: function (res) {
                console.log('断开设备连接', res);
                wx.reLaunch({
                    url: '../index/index',
                })
            }
        });
    },

    /**
    * 生命周期函数--监听页面卸载
    */
    onUnload: function () {
        var that = this;
        wx.closeBLEConnection({
            deviceId: that.data.deviceId,
            success: function (res) {
                console.log('断开设备连接', res);
            }
        });
    },
    
  /**
  *  ArrayBuffer类型数据转为16进制字符串
  */
  buf2hex: function (buffer) { // buffer is an ArrayBuffer
      return Array.prototype.map.call(new Uint8Array(buffer), x => ('00' + x.toString(16)).slice(-2)).join('');
  }, 
  //---------------------------------------------------------------------------------------------------------
  // user code 
  //--------------------------------------------------------------------------------------------------------
  CRC16: function (buf = []) {
    var crc = 0xffff;
    var crc_16_tab =
      [
        0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
        0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
        0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
        0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
        0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
        0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
        0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
        0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
        0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
        0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
        0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
        0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
        0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
        0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
        0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
        0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
        0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
        0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
        0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
        0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
        0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
        0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
        0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
        0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
        0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
        0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
        0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
        0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
        0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
        0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
        0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
        0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040
      ];

    for (var i = 0; i < buf.length; i++) {
      crc = ((crc >> 8) ^ crc_16_tab[(crc ^ buf[i]) & 0xff]);
    }

    return crc;
  },

  MCS_Building: function (srcAddr, tarAddr, frum, cmd, data) {
    var that = this;
    var i = 0;
    var buff = [];

    buff[i++] = 0x5b;

    buff[i++] = srcAddr;
    buff[i++] = tarAddr;

    buff[i++] = (frum >> 8) & 0xff;
    buff[i++] = frum & 0xff;

    buff[i++] = (cmd >> 8) & 0xff;
    buff[i++] = cmd & 0xff;

    buff[i++] = data.length;

    if (data.length > 0) {
      for (var j = 0; j < data.length; j++) {
        buff[i++] = data[j];
      }
  }

  var crc = that.CRC16(buff);

    buff[i++] = crc & 0xff;
    buff[i++] = (crc >> 8) & 0xff;
    buff[i++] = 0x5d;

    return buff;
  },

  stringCmd: function (parbuff) {
    var str = "";

    for (var k = 0; k < parbuff.length; k++) {
      if (parbuff[k] > 0X0F) {
        str += parbuff[k].toString(16);
      }
      else {
        str += ("0" + parbuff[k].toString(16));
      }
    }

    return str;
  },

  sendmcsCmd: function (cmdBuff) {
    var that = this;
    var arraybuff = [];
    var mcsbuff = [];
    var str = "";

    mcsbuff = that.MCS_Building(0, 0, 0, 0x0013, cmdBuff);
    str = that.stringCmd(mcsbuff);
    arraybuff.push(str);
    arraybuff.map(function (val, index) {
      setTimeout(function () {
        var value_set = val;
        console.log('value_set', value_set);
        var write_function = that.write(value_set);       //调用数据发送函数
      }, index * 100)
    });
  },

  /* 发送输入框的值 */
  SendCmdInterface: function ( devType, ID, devRes ) {
    var cmdBuff = [0x03, 0x03, 0x01];
    cmdBuff[0] = devType;
    cmdBuff[1] = ID;
    cmdBuff[2] = devRes;

    this.sendmcsCmd(cmdBuff);
  },

  SendCmdLightInterface: function ( devRes) {
    var cmdBuff = [0, 0, 0x01,0,0];
    cmdBuff[0] = 0x05;
    cmdBuff[1] = 0x01;
    cmdBuff[2] = devRes[0];
    cmdBuff[3] = devRes[1];
    cmdBuff[4] = devRes[2];

    this.sendmcsCmd(cmdBuff);
  },  

//控制平台
SendPingTaiUp:function(){
  var that = this;
  that.SendCmdInterface(0x01, 0x07, 0x01);
},

SendPingTaiDown: function () {
  var that = this;
  that.SendCmdInterface(0x01, 0x07, 0x00);
},

SendPingTaiStop: function () {
  var that = this;
  that.SendCmdInterface(0x01, 0x07, 0x02);
},

  //控制靠背-1
  SendKaoBei_1Up: function () {
    var that = this;
    that.SendCmdInterface(0x03, 0x03, 0x01);
  },

  SendKaoBei_1Down: function () {
    var that = this;
    that.SendCmdInterface(0x03, 0x03, 0x00);
  },

  SendKaoBei_1Stop: function () {
    var that = this;
    that.SendCmdInterface(0x03, 0x03, 0x02);
  },

  //控制靠背-2
  SendKaoBei_2Up: function () {
    var that = this;
    that.SendCmdInterface(0x03, 0x04, 0x01);
  },

  SendKaoBei_2Down: function () {
    var that = this;
    that.SendCmdInterface(0x03, 0x04, 0x00);
  },

  SendKaoBei_2Stop: function () {
    var that = this;
    that.SendCmdInterface(0x03, 0x04, 0x02);
  },

  //桌子
  SendDesk_Up: function () {
    var that = this;
    that.SendCmdInterface(0x04, 0x06, 0x01);
  },

  SendDesk_Down: function () {
    var that = this;
    that.SendCmdInterface(0x04, 0x06, 0x00);
  },

  SendDesk_Stop: function () {
    var that = this;
    that.SendCmdInterface(0x04, 0x06, 0x02);
  },

  //楼梯
  SendStair_Up: function () {
    var that = this;
    that.SendCmdInterface(0x02, 0x08, 0x01);
  },

  SendStair_Down: function () {
    var that = this;
    that.SendCmdInterface(0x02, 0x08, 0x00);
  },

  SendStair_Stop: function () {
    var that = this;
    that.SendCmdInterface(0x02, 0x08, 0x02);
  },

  //灯控制
  light_Open:function(){
    var that = this;
    var res=[0x01, 0, 0];

    res[1] = that.data.whiteValue;
    res[2] = that.data.yellowValue;
    that.SendCmdLightInterface(res);
  },

  light_Close: function () {
    var that = this;
    var res = [0, 0, 0];

    res[1] = that.data.whiteValue;
    res[2] = that.data.yellowValue;
    that.SendCmdLightInterface(res);
  },

  slideryellowchange: function (e) {
    var that = this;
    var res = [0x01, 0x63, 0x63];

    //获取滑动后的值
    that.data.yellowValue = e.detail.value;
    res[1] = that.data.whiteValue;
    res[2] = that.data.yellowValue;
    that.SendCmdLightInterface(res);  
    console.log("yellow: " + e.detail.value);
  },

  sliderwhitechange: function (e) {
    var that = this;
    var res = [0x01, 0x63, 0x63];

    //获取滑动后的值
    that.data.whiteValue = e.detail.value;
    res[1] = that.data.whiteValue;
    res[2] = that.data.yellowValue;
    that.SendCmdLightInterface(res);  
    console.log("white: " + e.detail.value);
  }, 
})