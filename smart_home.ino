#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "Ea5ZYzCi3ivGUl8ak6YhHpjwQElQ4jus";   //รหัส Token Blynk
char ssid[] = "NAVANITILAW_HOME_2.4GHz"; // 2.4G only ชื่อ Wi-Fi
char pass[] = "0813434814"; //รหัสผ่าน

#define LED_PIN_1 D0 //Led เปิด-ปิด แบบปุ่ม(เชื่อม Blynk)
#define LED_PIN_2 D2 //Led เปิด-ปิด แบบอัตโนมัติ
//Led Alarm sensor ตรวจจับน้ำฝน เนย
//Led Alarm sensor ตรวจจับสิ่งกีดขวาง น้อยหน่า
//ขาของ Raindrop เนย

int analogPin = A0; //ประกาศตัวแปร ให้ analogPin แทนขา analog ขาที่5 ของ ไฟเปิด-ปิด auto
//ประกาศตัวแปร ให้ digitalPin ของ sensor ตรวจจับสิ่งกีดขวาง น้อยหน่า
int val = 0; //แสดงค่าความสว่างของแสง เปิด-ปิดไฟ auto
//แสดงสถานะของ sensor ตรวจจับสิ่งกีดขวาง น้อยหน่า

BLYNK_WRITE(D0)//เป็นฟังก์ชันในการสั่งการทำงานเมื่อกดปุ่ม D0 ใน Blynk Application ซึ่งในที่นี้คือ การเปิดปิดไฟแบบปุ่ม
{ 
  //ค่าที่ได้จาก Widget_Button จะเป็น 0 และ 1 ถ้ามีการปดปุ่ม
  if (param.asInt() == 1) {
    //เรียกใช้เปิดไฟ LED
    digitalWrite(LED_PIN_1, HIGH); 
  }
  else {
    //เรียกใช้ปิดไฟ LED
    digitalWrite(LED_PIN_1, LOW);
  }
}

void setup() { 
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass); //Token, ชื่อ Wi-Fi, รหัสผ่าน
  pinMode(LED_PIN_1, OUTPUT); //แสดงค่าทาง Led เปิด-ปิด แบบปุ่ม(เชื่อม Blynk)
  pinMode(LED_PIN_2, OUTPUT); //แสดงค่าทาง Led เปิด-ปิด แบบอัตโนมัติ
  //แสดงค่าทาง Led Alarm sensor ตรวจจับน้ำฝน เนย
  //น้อยหน่า
  //รับจาก sensor ตรวจจับน้ำฝน เนย
}
void loop() {
  Blynk.run();
  val = analogRead(analogPin); //อ่านค่า Analog จาก LDR sensor วัดความสว่าง
  //อ่านค่า Digital จาก sensor raindrop เนย
  //อ่านค่า Digital จาก sensor infared ตรวจจับสิ่งกีดขวาง น้อยหน่า
  Serial.print("val_LDR = "); //แสดงค่าบรรทัดเดียวกัน
  Serial.println(val); // พิมพ์ค่าของตัวแปร val //แสดงค่าขึ้นบรรทัดใหม่
  //เนย
  //น้อยหน่า
  if (val < 900 or val == 900 or val > 900) { // ค่า 900 สามารถกำหนดปรับได้ตามค่าแสงในห้องต่างๆ การเปิด-ปิดไฟแบบ auto
    if (val < 900){
      digitalWrite(LED_PIN_2, LOW);} // สั่งให้ LED ติดสว่าง
    else{
      digitalWrite(LED_PIN_2, HIGH); // สั่งให้ LED ดับ
    }
  }
  //ฝน เนย
  //IR น้อยหน่า
  delay(100);
}