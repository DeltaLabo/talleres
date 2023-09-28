#include <Wire.h>
#include <vl53l0x_api.h>

int TOFAddress = 0x29;
int read = 0;
int result;
uint8_t I2cDevAddr;

class pMyDevice{
  private:
  VL53L0X_Dev_t MyDevice;
  VL53L0X_Dev_t *pMyDevice = &MyDevice;
  VL53L0X_DeviceInfo_t DeviceInfo;
  uint8_t _rangeStatus;
};

pMyDevice->I2cDevAddr = VL53L0X_I2C_ADDR;
pMyDevice->comms_type = 1;
pMyDevice->comms_speed_khz = 400;
pMyDevice->i2c = i2c;
pMyDevice->i2c->begin(); 

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(100);
}

void loop() {
  
  VL53L0X_PerformSingleRangingMeasurement(VL53L0X_DEV, VL53L0X_DataInit);
  VL53L0X_ClearInterruptMask (VL53L0X_DEV Dev, uint32_t InterruptMask);

  Serial.print(read);


  // byte error;
  // 
  // Wire.beginTransmission(TOFAddress);
  // delay(100);

  // error = Wire.endTransmission();

  // if(error == 0) {  // 
  //   Serial.print("HOLA:");
  //   Wire.requestFrom(TOFAddress, 8); 

  //   if (8 <= Wire.available()) { 
  //     read = Wire.read(); 
  //     Serial.println(read); 

  //   }

  delay(250); 
  }


