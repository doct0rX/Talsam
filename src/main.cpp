#include <Arduino.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  // digitalWrite(2, HIGH);
  // digitalWrite(3, HIGH);
  // digitalWrite(4, HIGH);
  // digitalWrite(5, HIGH);
  // digitalWrite(6, HIGH);
  // digitalWrite(7, HIGH);
  // digitalWrite(8, HIGH);
  // digitalWrite(9, HIGH);
  // digitalWrite(10, HIGH);

  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1500); 
  
  
  // I2C
  byte error, address;
  int Devices;
  Serial.println("Scanning...");
  Devices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      Devices++;
    } else if (error==4) {
    Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
      }
  }
  if (Devices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
  delay(5000);        // wait for a second
}