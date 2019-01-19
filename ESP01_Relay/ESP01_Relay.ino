/*
 Name:		ESP01_Relay.ino
 Created:	1/19/2019 9:17:47 PM
 Author:	guebr
*/


#define INITIAL_TICK_DELAY  200
long tickDelay = INITIAL_TICK_DELAY;
long lastTick = 0;
boolean state = false;
boolean desiredState = false;

// data to be sent through the serial port to manage the relais
byte reBufferON[] = { 0xA0, 0x01, 0x01, 0xA2 };
byte reBufferOFF[] = { 0xA0, 0x01, 0x00, 0xA1 };
byte *reMessage = NULL;
int reMessageSize = 0;


// the setup function runs once when you press reset or power the board
void setup() {
	// start communication with Serial port
	Serial.begin(9600);
	lastTick = 0;
	state = false;
	reMessage = reBufferOFF;
	reMessageSize = sizeof(reBufferOFF);
	desiredState = false;
}

void updateTick(long current) {

	if (desiredState != state) {
		if (desiredState) {
			reMessage = reBufferOFF;
			reMessageSize = sizeof(reBufferON);
		}
		else {
			reMessage = reBufferON;
			reMessageSize = sizeof(reBufferON);
		}

		state = desiredState;
		lastTick = current;
		tickDelay = INITIAL_TICK_DELAY;
	}
	else if (lastTick > current || (current - lastTick) > tickDelay) {
		Serial.write(reMessage, reMessageSize);
	}

}

void setRelais(boolean on_off) {
	desiredState = on_off;
}


// the loop function runs over and over again until power down or reset
void loop() {
	long currentTime = millis();
	// todo : MQQT STuff



	updateTick(currentTime);
}
