#include <Arduino.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <GOTStateMachine.h>


GOTStateMachine stateMachine(50);	// execute every 50 milliseconds
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BLINKING_LIGHT_RONDOMLY_INTERVAL 3000	// blinking light time

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

bool pushButtonState = false;
int publicMs = (millis() + 500)/1000;

void initialize();
void start();
void randomLedsBlinking();
void setupStateMachine();
void printOnScreenAndStopLeds();

void setup() {
  	// initialize the Pins
	initialize();
	
	lcd.setCursor(4,0);
	lcd.print("Hackster");
	
	stateMachine.setStartState(randomLedsBlinking);
}


void loop() {
	pushButtonState = digitalRead(pushButtonPin);
	stateMachine.execute();
	if (pushButtonState == HIGH) {
		stateMachine.setStartState(randomLedsBlinking);
	}
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


void randomLedsBlinking() {
	digitalWrite(leds[random(0, sizeof(leds)/sizeof(int))], HIGH);
	delay(random(0, 200));
	digitalWrite(leds[random(0, sizeof(leds)/sizeof(int))], LOW);
	
	if (stateMachine.isDelayComplete(BLINKING_LIGHT_RONDOMLY_INTERVAL)) {
		stateMachine.changeState(printOnScreenAndStopLeds);
		return;
	}
}

void printOnScreenAndStopLeds() {
	lcd.clear();
	lcd.setCursor(4,0);
	lcd.print("DONE!!!");
	for (size_t led = 0; led < sizeof(leds)/sizeof(int); led++) {
		digitalWrite(leds[led], LOW);
	}
}
