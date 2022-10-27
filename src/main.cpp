#include <Arduino.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pushButtonPin = 11;  // the number of the push button pin
const int firstLed = 4;		// LEDs [D2.. D10]
const int secondLed = 5;
const int thirdLed = 8;
const int forthLed = 3;
const int fifthLed = 6;
const int sixthLed = 9;
const int seventhLed = 2;
const int eighthLed = 7;
const int ninthLed = 10;

// TODO: remove this vars later and work with numbers directly
int leds[9] = {firstLed, secondLed, thirdLed,
			   forthLed, fifthLed, sixthLed,
			   seventhLed, eighthLed, ninthLed};

int pushButtonState = 0;
int publicMs = (millis() + 500)/1000;

void initialize();
void start();
void randomLedsBlinking(unsigned long millisecondsInterval, unsigned long currentMs);

void setup() {
  	// initialize the Pins
	initialize();
  // digitalWrite(6, HIGH);
  // digitalWrite(7, HIGH);
  // digitalWrite(8, HIGH);
  // digitalWrite(9, HIGH);
  // digitalWrite(10, HIGH);

	
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
		publicMs = (millis() + 500)/1000 + 5;
	}
	randomLedsBlinking(5000, publicMs);
	start();
}


/**
 *****  Helpers ******
*/
void initialize() {
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(pushButtonPin, INPUT);
	for (size_t led = 0; led < sizeof(leds)/sizeof(int); led++) {
		pinMode(leds[led], OUTPUT);
	}
	Serial.begin(9600);
	lcd.begin();
	lcd.backlight();
	lcd.clear();
}

void start() {
	
}


/** making a state machine function to count the Leds seconds **/
int liveMs = (millis() + 500) / 1000;
// int ms = ((publicMs + millisecondsInterval) + 500) / 1000;

void randomLedsBlinking(unsigned long millisecondsInterval, unsigned long currentMs) {
	Serial.print("here ");
	Serial.println(((publicMs + millisecondsInterval) + 500) / 1000);
	if (liveMs < currentMs) {
		digitalWrite(leds[random(0, sizeof(leds)/sizeof(int))], HIGH);
		delay(random(0, 200));
		digitalWrite(leds[random(0, sizeof(leds)/sizeof(int))], LOW);
	} else {
		for (size_t i = 0; i < sizeof(leds)/sizeof(int); i++) {
			digitalWrite(leds[i], LOW);
		}
	}
	Serial.println((millis()+500)/1000);
}