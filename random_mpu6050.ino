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

unsigned long seedValue = (ax + ay + az);

int randomNumber = random(1, 21);

 Serial.print("Accell: "); Serial.println(az + ay + az);
 Serial.print("Gyro: "); Serial.println(gx + gy + gz);

 Serial.println(randomNumber);

 delay(500);

}
