#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6 //Digital PIN for LED Strip
#define NUM_LEDS 20 //Total LEDs

MPU6050 mpu; //Create MPU object

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800); //Create LED objects

const int buttonPin = 2; // Digital Pin for the button
bool buttonState = HIGH;
bool lastButtonState = HIGH;
bool readOnce = false;
int randomNumber = 0;

int16_t ax, ay, az;
int16_t gx, gy, gz;
float fax, fay, faz;
float fgx, fgy, fgz;
float aSum, gSum;

void setup() {

  Serial.begin(9600); // Serial debugging baudrate
  Wire.begin(); // Initialise I2C bus
  mpu.initialize(); // Initialise MPU6050

  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor

  strip.begin();
  strip.show(); // Initialize all pixels to off

  // Debug for MPU6050 connection
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
  }

}

void loop() {

  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH){
    readOnce = true;
  }

  if (readOnce){
    readOnce = false;

    // Read accelerometer and gyroscope values
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);


      // Conver to float to avoid 32bit overflow
      float fax = (float)ax;
      float fay = (float)ay;
      float faz = (float)az;

      float fgx = (float)gx;
      float fgy = (float)gy;
      float fgz = (float)gz;

    float aSum = sqrt(fax * fax + fay * fay + faz * faz); // Calculate magnitude of acceleration vector
    float gSum = sqrt(fgx * fgx + fgy * fgy + fgz * fgz); // Calculate magnitude of gyroscope vector

    unsigned long seedValue = (aSum + gSum); // Seed Value for the RandomNumber
    randomSeed(seedValue);

    randomNumber = random(1, 21); // RandomNumber generator based on seed value

    Serial.print("Acc: "); Serial.println(aSum); // Debug Output of Acc
    Serial.print("Gyro: "); Serial.println(gSum); // Debug Output of Gyro
    Serial.print("Total: "); Serial.println(aSum + gSum); // Debug Output of combined values
    Serial.print("D20 Roll: "); Serial.println(randomNumber); // Debug Output of D20 roll

    for(int i = 0; i < NUM_LEDS; i++){
        if(i < randomNumber){
            strip.setPixelColor(i, strip.Color(255, 0, 0)); //Set LEDs to red
        } else {
          strip.setPixelColor(i, strip.Color(0, 0, 0)); //Turn LEDs off
        }
        strip.show();
      }

    }

  lastButtonState = buttonState;

  delay(50);

}
