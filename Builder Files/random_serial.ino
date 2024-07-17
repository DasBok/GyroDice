void setup() {

  Serial.begin(9600);

}

void loop() {
  
  unsigned long seedValue = millis();

  randomSeed(seedValue);

  int randomNumber = random(1, 21);

  Serial.println(randomNumber);

  delay(5000);

}
