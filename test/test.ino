#include <Arduino.h>
#include <Servo.h>

#define RELAIS_MAINS	4
#define RELAIS_F		2
#define RELAIS_R		3

#define PWM_DRIVE		9
#define PWM_BREAK		6

#define VOLTAGE_1 		A0
#define VOLTAGE_2 		A1

uint8_t status;
uint8_t drive_val = 30;
uint8_t break_val = 30;


void setup(void) {

	Serial.begin(115200);


	pinMode(RELAIS_MAINS, OUTPUT);
	pinMode(RELAIS_F, OUTPUT);
	pinMode(RELAIS_R, OUTPUT);

	pinMode(PWM_DRIVE, OUTPUT);
	pinMode(PWM_BREAK, OUTPUT);

	set_drive(0);
	set_break(0);

	pinMode(VOLTAGE_1, INPUT);
	pinMode(VOLTAGE_2, INPUT);

	digitalWrite(RELAIS_MAINS, LOW);
	digitalWrite(RELAIS_F, LOW);
	digitalWrite(RELAIS_R, LOW);


	Serial.println("startup complete");


	// MAIN ON
	// DIRECTION OFF
	Serial.println("all off");

	off();
	dir_off();

	// on();
	// set_dir(1);
	// set_drive(50);

	// delay(5000);

	// set_drive(0);
	// off();
}

void loop(void) {

	uint8_t cmd;

	if (Serial.available()) {

		cmd = Serial.read();

		if (cmd != 10) {
			dir(cmd);
			val(cmd);
		}
	}

}


void set_drive(uint8_t val) {

	if (status != 0) {

		Serial.print("set drive to ");
		Serial.println(val);

		analogWrite(PWM_DRIVE, val);
	}

	else {
		Serial.println("is switched off");
	}
}

void set_break(uint8_t val) {

	if (status != 0) {

		Serial.print("set break to ");
		Serial.println(val);

		analogWrite(PWM_BREAK, val);
	}
	else {
		Serial.println("is switched off");
	}
}

void on(void) {
  digitalWrite(RELAIS_MAINS, HIGH);

}

void off(void) {

	set_break(0);
	set_drive(0);
	wait();

	dir_off();
  digitalWrite(RELAIS_MAINS, LOW);
  status = 0;
}

void dir_off(void) {

	set_break(0);
	set_drive(0);
	wait();

  digitalWrite(RELAIS_F, LOW);
  digitalWrite(RELAIS_R, HIGH);
}


void set_dir(uint8_t dir) {

	Serial.println("off");

	dir_off();
	status = 0;

	switch(dir) {

		case (1):
			digitalWrite(RELAIS_F, HIGH);
			digitalWrite(RELAIS_R, HIGH);

			Serial.println("forward");

			status = 1;
			break;

		case (2):
			digitalWrite(RELAIS_F, LOW);
			digitalWrite(RELAIS_R, LOW);

			status = 2;
			Serial.println("reward");
			break;
	}
}


void val(uint8_t val) {

	// can set analog
	if (status != 0) {
// Serial.println(val);
		switch(val) {

			case 100:

				Serial.println("break off");

				set_break(0);
				wait();
				set_drive(drive_val);

				break;

			case 98:

				Serial.println("drive off");

				set_drive(0);
				wait();
				set_break(break_val);

				break;

			default:

				Serial.println("idle");

				set_drive(0);
				set_break(0);

				break;
		}

	}

}


void dir(uint8_t dir) {

	switch(dir) {

		case 102:
			on();
			dir_off();

			wait();

		  set_dir(1);

		  status = 2;

			Serial.println("forward");
			break;

		case 114:
			on();
			dir_off();

			wait();

		  status = 1;

		  set_dir(2);
		  Serial.println("reward");

		  break;

		case 115:
			dir_off();

			wait();

			off();

		  status = 0;

		  Serial.println("off");
		  break;
	}
}


void wait(void) {
	delay(500);
}