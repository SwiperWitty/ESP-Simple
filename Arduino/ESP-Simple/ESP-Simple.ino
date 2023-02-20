
#define BLINKER_WIFI

#include <Blinker.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define KEY 16    //D0
#define MOS_1 4
#define MOS_2 2
#define BZZ 5     //D1
#define IIC_SDA 12
#define IIC_SCL 13
#define ADC A0

char auth[] = "48e6a252f124";
char ssid[] = "Caven_ESP";
char pswd[] = "012345678";

// 新建组件对象
BlinkerNumber Number1("num-abc");
BlinkerNumber PF("num-pf");
BlinkerNumber HP("num-hlep");

BlinkerButton Button1("btn-abc");
BlinkerButton Button2("btn-bzz");

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int counter = 0;
int key_en = 0;
int pf_num = 0;
int bzz_en = 0;

// 按下按键即会执行该函数
void button1_callback(const String & state)
{
    BLINKER_LOG("get button state: ", state);
//    BLINKER_LOG("hlep !");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));     //LED
    digitalWrite(MOS_1, !digitalRead(MOS_1));                 //MOS_1
    digitalWrite(MOS_2, !digitalRead(MOS_1));                 //MOS_2是MOS_1的取反
}

void button2_callback(const String & state)
{
    bzz_en = !bzz_en;

}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}

void setup()
{
    // 初始化串口
    Serial.begin(115200);

    // 初始化OLED
    Wire.begin(IIC_SDA, IIC_SCL);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // 设置OLED的I2C地址
    delay(100);
    
    //[x] (0 - 7) [y] (0 - 30)
    display.clearDisplay(); // 清空屏幕
    display.setTextSize(1); // 设置字体大小
    display.setTextColor(SSD1306_WHITE); // 设置字体颜色
    display.setCursor((8)*4,(0)*8); // 设置开始显示文字的坐标
    display.println("Hello World!"); // 输出的字符
    display.setCursor((0)*4,(1)*8); // 设置开始显示文字的坐标
    display.println(">"); // 输出的字符
    display.setCursor((0)*4,(2)*8); // 设置开始显示文字的坐标
    display.println(" "); // 输出的字符
    display.setCursor((0)*4,(3)*8); // 设置开始显示文字的坐标
    display.println(" "); // 输出的字符
    display.setCursor((0)*4,(4)*8); // 设置开始显示文字的坐标
    display.println(" "); // 输出的字符
    display.setCursor((0)*4,(5)*8); // 设置开始显示文字的坐标
    display.println(" "); // 输出的字符
    display.setCursor((0)*4,(6)*8); // 设置开始显示文字的坐标
    display.println(" "); // 输出的字符
    display.setCursor((24)*4,(7)*8); // 设置开始显示文字的坐标
    display.println("Caven"); // 输出的字符

    display.display(); // 使更改的显示生效

    BLINKER_DEBUG.stream(Serial);
    BLINKER_DEBUG.debugAll();
    
    // 初始化有LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    pinMode(BZZ, OUTPUT);
    digitalWrite(BZZ, LOW);
    pinMode(MOS_1, OUTPUT);
    digitalWrite(MOS_1, LOW);
    pinMode(MOS_2, OUTPUT);
    digitalWrite(MOS_2, LOW);

    pinMode(KEY, INPUT);

    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);

    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Serial.printf("UART0\r\n");
}



void loop() {
    Blinker.run();
    pf_num = analogRead(ADC);
    if(pf_num <= 30)
    {
      // pf_num = 0;
    }
    else if(pf_num > 300)
    {
      pf_num = 300;
    }
    PF.print(pf_num);
    delay(30);

    if(digitalRead(KEY) == 0)
    {
      delay(10);
      if(digitalRead(KEY) == 0)
      {
        if(key_en == 1)
        {
          key_en = 0;
        }
        else
        {
          key_en = 1;
        }
      }
      do{delay(10);}
      while(!digitalRead(KEY));
    }

/**下面是驱动**/

    if(key_en == 1 || pf_num == 0)
    {
      bzz_en = 1;
      key_en = 1;
      HP.print(1);
    }
    else if(key_en == 0)
    {
      bzz_en = 0;
      HP.print(0);
      key_en = 2;
    }

    if(bzz_en)
    {
      digitalWrite(BZZ, HIGH);
    }
    else{digitalWrite(BZZ, LOW);}
    delay(10);
}
