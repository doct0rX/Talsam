#include <Arduino.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pushButtonPin = 11;  // the number of the pushbutton pin
const int firstLed = 4;		// LEDs
const int secondLed = 5;
const int thirdLed = 8;
const int forthLed = 3;
const int fifthLed = 6;
const int sixthLed = 9;
const int seventhLed = 2;
const int eighthLed = 7;
const int ninthLed = 10;

int pushButtonState = 0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(firstLed, OUTPUT);
	pinMode(secondLed, OUTPUT);
	pinMode(thirdLed, OUTPUT);
	pinMode(forthLed, OUTPUT);
	pinMode(fifthLed, OUTPUT);
	pinMode(sixthLed, OUTPUT);
	pinMode(seventhLed, OUTPUT);
	pinMode(eighthLed, OUTPUT);
	pinMode(ninthLed, OUTPUT);

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

void start() {
	digitalWrite(3, HIGH);
}