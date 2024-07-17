#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {

  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
  }

}

void loop() {
  
 int16_t ax, ay, az;
 int16_t gx, gy, gz;

 mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float fax = (float)ax;
  float fay = (float)ay;
  float faz = (float)az;

  float fgx = (float)gx;
  float fgy = (float)gy;
  float fgz = (float)gz;

 float aSum = sqrt(fax * fax + fay * fay + faz * faz);
 float gSum = sqrt(fgx * fgx + fgy * fgy + fgz * fgz);

unsigned long seedValue = (aSum + gSum);

int randomNumber = random(1, 21);

 Serial.print("Acc: "); Serial.println(aSum);
 Serial.print("Gyro: "); Serial.println(gSum);
 Serial.print("Total: "); Serial.println(aSum + gSum);

 Serial.print("D20 Roll: "); Serial.println(randomNumber);

 delay(1000);

}
