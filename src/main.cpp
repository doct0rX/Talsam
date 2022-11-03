#include <Arduino.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <GOTStateMachine.h>


GOTStateMachine stateMachine(50);	// execute every 50 milliseconds
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BLINKING_LIGHT_RONDOMLY_INTERVAL 3000	// blinking light time

const int pushButtonPin = 11;  // the number of the push button pin

int leds[9] = {4, 5, 8, // LEDs [D2.. D10]
			   3, 6, 9,
			   2, 7, 10};

int gridNumbers[8][3] = {
					{49, 48, 53},
					{54, 50, 46},
					{47, 52, 51},
					{49, 54, 47},
					{48, 50, 52},
					{53, 46, 51},
					{49, 50, 51},
					{53, 50, 47}
				};

bool pushButtonState = false;
int selectedAxis = 0;
int counter = 1;

void initialize();
void start();
void randomLedsBlinking();
void setupStateMachine();
void printOnScreenAndStopLeds();
void turnOffLeds();
void lightCoordinatedLeds();
void printYa3aleemAndCount();
void turnOffLedsAndCLearScreen();
void writesTamatOrDoneOnLcd();
void turnOffLedsAndCLearScreen();

void setup() {
	initialize();	
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
	lcd.clear();
	selectedAxis = random(0, 9);

	lcd.setCursor(5,0);
	lcd.print("TALSAM");

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
	lcd.setCursor(0,0);
	String stringNumbers = " ";
	for (size_t c = 0; c < sizeof(gridNumbers[0])/sizeof(int); c++) {
		if (c != 2) {
			stringNumbers += String(gridNumbers[selectedAxis][c]) + "+";
		} else {
			stringNumbers += String(gridNumbers[selectedAxis][c]);
		}
	}
	delay(300);
	stringNumbers += " = 150";
	lcd.print(stringNumbers);
	if (stateMachine.isDelayComplete(500)) {
		stateMachine.changeState(turnOffLeds);
		return;
	}
}

void turnOffLeds() {
	for (size_t led = 0; led < sizeof(leds)/sizeof(int); led++) {
			digitalWrite(leds[led], LOW);
	}
	if (stateMachine.isDelayComplete(1000)) {
		stateMachine.changeState(lightCoordinatedLeds);
		return;
	}
}

void lightCoordinatedLeds() {
	switch (selectedAxis) {
		case 0:
			for (size_t i = 0; i < 3; i++)
				digitalWrite(leds[i], HIGH);
			break;
		case 1:
			for (size_t i = 3; i < 6; i++)
				digitalWrite(leds[i], HIGH);
			break;
		case 2:
			for (size_t i = 6; i < 9; i++)
				digitalWrite(leds[i], HIGH);
			break;
		case 3:
			for (size_t i = 0; i < 7; i+=3)
				digitalWrite(leds[i], HIGH);
			break;
		case 4:
			for (size_t i = 1; i < 8; i+=3)
				digitalWrite(leds[i], HIGH);
			break;
		case 5:
			for (size_t i = 2; i < 9; i+=3)
				digitalWrite(leds[i], HIGH);
			break;
		case 6:
			for (size_t i = 0; i < 9; i+=4)
				digitalWrite(leds[i], HIGH);
			break;
		case 7:
			for (size_t i = 2; i < 7; i+=2)
				digitalWrite(leds[i], HIGH);
			break;
		default:
			break;;
	}
	if (stateMachine.isDelayComplete(100)) {
		stateMachine.changeState(printYa3aleemAndCount);
		counter = 1;
		return;
	}
}

void printYa3aleemAndCount() {
	lcd.setCursor(12, 0);
	lcd.print(counter);
	lcd.setCursor(1, 1);
	lcd.print("Ya 3aleem");
	delay(500);
	lcd.setCursor(12, 0);
	lcd.print("   ");
	lcd.setCursor(1, 1);
	lcd.print("           ");
	delay(500);
	counter++;
	if (stateMachine.isDelayComplete(10000) || counter >= 10) {
		stateMachine.changeState(writesTamatOrDoneOnLcd);
		return;
	}
}

void writesTamatOrDoneOnLcd() {
	lcd.clear();
	lcd.setCursor(1, 6);
	lcd.print("TAMAT");
	if (stateMachine.isDelayComplete(2000)) {
		stateMachine.changeState(turnOffLedsAndCLearScreen);
		return;
	}
}

void turnOffLedsAndCLearScreen() {
	turnOffLeds();
	lcd.clear();
	if (stateMachine.isDelayComplete(2000)) {
		stateMachine.changeState(turnOffLedsAndCLearScreen);
		return;
	}
}
