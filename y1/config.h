//จอTFT
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#include "TFT_A.h"

//วัดระยะ
#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;

//นับการทำงาน
long elapsedTime = 0; //นับเวลาการทำงาน
long nowTime = 0;     //นับเวลาการทำงาน

//แกน
const int MPU_addr = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

//รูป
#include "photo.h"

//ลำโพง
#include "SoundData.h"
#include "XT_DAC_Audio.h"

XT_Wav_Class ForceWithYou(Force);     // create an object of type XT_Wav_Class that is used by
// the dac audio class (below), passing wav data as parameter.

XT_DAC_Audio_Class DacAudio(26, 0);   // Create the main player class object.
// Use GPIO 25, one of the 2 DAC pins and timer 0
