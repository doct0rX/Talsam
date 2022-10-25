#include <Arduino.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pushButtonPin = 11;  // the number of the pushbutton pin

int pushButtonState = 0;

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

	pinMode(pushButtonPin, INPUT);

  // digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  // digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  // digitalWrite(6, HIGH);
  // digitalWrite(7, HIGH);
  // digitalWrite(8, HIGH);
  // digitalWrite(9, HIGH);
  // digitalWrite(10, HIGH);

	Serial.begin(9600);
	lcd.begin();
	lcd.backlight();
	lcd.clear();
	lcd.setCursor(4,0);
	lcd.print("Hackster");
}


void loop() {
	pushButtonState = digitalRead(pushButtonPin);
	// digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
	// delay(1500);                       // wait for a second
	// digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
	// delay(1500);

	if (pushButtonState == HIGH) {
		Serial.print("clicked");
		digitalWrite(6, HIGH);
	} else {
		digitalWrite(6, LOW);
	}
}