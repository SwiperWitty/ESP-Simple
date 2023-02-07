# ESP-Simple
服务于ESP8266，硬件开源在立创开源社区，软件在GitHub。





![image-20230207111723039](https://gitee.com/Swiper_witty/caven_img/raw/master/img/202302071117096.png)



### 硬件的坑

ESP8266或者说ESP32家族的自动下载方式都是这样的，ESP8266有个人把EN替换成RST。

![image-20230207111925954](https://gitee.com/Swiper_witty/caven_img/raw/master/img/202302071119983.png)

ESP8266的IO2,IO15分别要上拉，下拉（烧入）。一般的开发板并没有上拉IO2，但是本次设计有作为mos使用，所以默认有下拉导致芯片烧入错误。

![image-20230207112434003](https://gitee.com/Swiper_witty/caven_img/raw/master/img/202302071124034.png)



### 软件的坑

主要是OLED的Adafruit_SSD1306库，把OLED屏幕翻转的宏是无效的，因为c++文件中写死了这个参数要 | 0x1，。修改Adafruit_SSD1306.cpp就好了（去掉 | 0x1），如果你也想要旋转的效果，是需要修改Adafruit_SSD1306.h中两个宏定义的。

![cpp文件](https://gitee.com/Swiper_witty/caven_img/raw/master/img/202302071136104.png)



