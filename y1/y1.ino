
#include <TaskScheduler.h>
int Distance = 0;
char choice;


// Callback methods prototypes
void t1Callback();
void t2Callback();
void t3Callback();
void t4Callback();
void t5Callback();

//Tasks
Task t1(500, TASK_FOREVER, &t1Callback);
Task t2(500, TASK_FOREVER, &t2Callback);
Task t3(500, TASK_FOREVER, &t3Callback);
Task t4(500, TASK_FOREVER, &t4Callback);
Task t5(500, TASK_FOREVER, &t5Callback);
#include "config.h"

Scheduler runner;

void setup () {

  Serial.begin(9600);
  runner.init();
  runner.addTask(t1);
  runner.addTask(t2);
  runner.addTask(t3);
  runner.addTask(t4);
  runner.addTask(t5);
  t1.enable();
  t2.enable();
  t3.enable();
  t4.enable();
  t5.enable();

  //setupจอTFT
  tft.init();
  tft.setRotation(1);
  TFT_AA();


  //setupวัดระยะ
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous();//วัดระยะ

  //setupแกน
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  //setupวัดหัวใจ




}/*********************************************void***********************************************/

void t1Callback() {

  //แสดงระยะ
  long phase = sensor.readRangeContinuousMillimeters();
  tft.fillRect(200, 50, 80, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(200, 50);
  tft.print(phase);

  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred())
  {
    Serial.print(" TIMEOUT");
  }
  Serial.println();
  if (sensor.readRangeContinuousMillimeters() < Distance)
  {
    tft.fillRect(0, 85, 480, 95, tft.color24to16(0xFFFFFF));//ปิดข้อความแจ้งเตือนตรงกลาง
    tft.setTextSize(3);
    tft.setTextColor(tft.color24to16(0xFF4500));
    tft.setTextSize(5);//ขนาดข้อความ
    tft.drawString("Be Careful", 100, 120);
  }
  else
  {
    tft.fillRect(0, 85, 480, 95, tft.color24to16(0xFFFFFF));//ปิดข้อความแจ้งเตือนตรงกลาง
    tft.setTextSize(3);
    tft.setTextColor(tft.color24to16(0xFF4500));
    tft.setTextSize(5);//ขนาดข้อความ
    tft.drawString("****safe****", 70, 120);
  }

}
void t2Callback() {

  //แสดงแกน
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("ACC X:");
  Serial.print(AcX);
  Serial.print("  ACC Y:");
  Serial.print(AcY);
  Serial.print("  ACC Z:");
  Serial.print(AcZ);
  Serial.println();
  //แสดงแกนบนจอ
  tft.fillRect(0, 20, 130, 45, tft.color24to16(0xFFFFFF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(1);//ขนาดข้อความ
  tft.drawString("ACC X: ", 10, 20);//ข้อความ
  tft.setCursor(45, 20);
  tft.print(AcX);

  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(1);//ขนาดข้อความ
  tft.drawString("ACC Y: ", 10, 30);//ข้อความ
  tft.setCursor(45, 30);
  tft.print(AcY);

  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(1);//ขนาดข้อความ
  tft.drawString("ACC Z: ", 10, 40);//ข้อความ
  tft.setCursor(45, 40);
  tft.print(AcZ);

}
void t3Callback() {

  //จำลองแสดงค่า Tmp
  tft.fillRect(360, 250, 80, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(370, 250);
  tft.print(37.6);


}
void t4Callback() {

  //หัวใจ
  tft.fillRect(30, 250, 100, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(50, 250);
  tft.print(97);
  //ออกซิเจน
  tft.fillRect(180, 250, 80, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(3);//ขนาดข้อความ
  tft.setCursor(200, 250);
  tft.print(99);


}
void t5Callback() {
  //นับเวลาการทำงาน
  int a = millis() / 1000;
  tft.fillRect(0, 0, 120, 20, tft.color24to16(0xFFFFFF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(1);//ขนาดข้อความ
  tft.drawString("Time: ", 10, 10);//ข้อความ
  tft.setCursor(40, 10);
  tft.print(a);
  a++;
}

/*****************************************void loop*************************************************/
void loop()
{
  runner.execute();

  long i = sensor.readRangeContinuousMillimeters();
  DacAudio.FillBuffer();                       // Fill the sound buffer with data
  if (i > Distance)
  {
    char c = 'A';
    switch (c) {
      case 'A':
        DacAudio.Play(&ForceWithYou);       // play it, this will cause it to repeat and repeat...
        break;                                 //การพักคำสั่ง เมื่อ case ตรงตามเงื่อนไขจะออกจาก switch ทันที
    }
  }
}


//tft.pushImage(0,0,480,320,photo_A);          //คำสั่งปริ้นรูป*******
