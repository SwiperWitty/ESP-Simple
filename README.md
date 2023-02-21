# ESP-Simple
服务于ESP8266，硬件开源在立创开源社区，软件在GitHub。

[软件链接](https://github.com/SwiperWitty/ESP-Simple)

[硬件链接](https://oshwhub.com/)



![bcccb8194d3e00026a2e94544f552ba](https://gitee.com/Swiper_witty/caven_img/raw/master/img/202302210900163.png)



![64a339d38aea23f69ef5eead13ecdfa](https://gitee.com/Swiper_witty/caven_img/raw/master/img/202302210900093.png)

### 硬件的坑

ESP8266或者说ESP32家族的自动下载方式都是这样的，ESP8266有个人把EN替换成RST。

![image-20230207111925954](https://gitee.com/Swiper_witty/caven_img/raw/master/img/202302071119983.png)

ESP8266的IO2,IO15分别要上拉，下拉（烧入）。一般的开发板并没有上拉IO2，但是本次设计有作为mos使用，所以默认有下拉导致芯片烧入错误。

![image-20230207112434003](https://gitee.com/Swiper_witty/caven_img/raw/master/img/202302071124034.png)



### 软件的坑

主要是OLED的Adafruit_SSD1306库，把OLED屏幕翻转的宏是无效的，因为c++文件中写死了这个参数要 | 0x1，。修改Adafruit_SSD1306.cpp就好了（去掉 | 0x1），如果你也想要旋转的效果，是需要修改Adafruit_SSD1306.h中两个宏定义的。

![cpp文件](https://gitee.com/Swiper_witty/caven_img/raw/master/img/202302071136104.png)







______

![b3270d258eef3f22e0fd0c237d45169](https://gitee.com/Swiper_witty/caven_img/raw/master/img/202302210900718.jpg)

我叫**卡文迪许怪**！又称**哆啦A梦本梦**！

我的网址

[卡文迪许怪-bilibili](https://space.bilibili.com/102898291) （常用）

[SwiperWitty-GitHub](https://github.com/SwiperWitty) （常用）

[Swiper_witty-Gitee](https://gitee.com/Swiper_witty) (不常用)

QQ群：455839434 （讨论、问问题）
