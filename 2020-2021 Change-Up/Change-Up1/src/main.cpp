#include "main.h"

// Motor Definitions
pros::Motor FR(frPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor BR(brPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor FL(flPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
pros::Motor BL(blPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

pros::Motor IntakeR(intakeRPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
pros::Motor IntakeL(intakeLPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor RollerTop(rollerTopPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor RollerBot(rollerBotPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);


pros::Controller master(E_CONTROLLER_MASTER);
pros::Imu imu (16);

Base base;

vector<int> motor_voltages;

void initRecord() {
		FILE*file = fopen("/usd/motor_voltages.txt", "r");

		char buff[1000];
		string s = "";

		while (fgets(buff, 1000, file) != NULL) { //750 for 15 seconds, 3000 for 1 minut
				string a = buff;
				s = s + a;
		}

		fclose(file);

		vector<string> motor_string;

		istringstream ss (s);
		string voltage;

		while(ss>>voltage) {
				motor_string.push_back(voltage);
		}

		for (int i = 0; i<motor_string.size(); i++) {
			motor_voltages.push_back(stoi(motor_string[i]));
		}
}

void initialize() {
	FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	IntakeR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	IntakeL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	RollerTop.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	RollerBot.set_brake_mode(E_MOTOR_BRAKE_HOLD);

	pros::lcd::initialize();
	imu.reset();

	Task record(recorderFunction, (void*)"PROS", //Initialize multitask function
    TASK_PRIORITY_DEFAULT,
    TASK_STACK_DEPTH_DEFAULT,
    "Records and plays autonomouses"
  );


	//initRecord();
}

void autonomous() {
	/*for(int i = 0; i<motor_voltages.size()-8; i=i+8) {
		FR.move_voltage(motor_voltages[i]);
		BR.move_voltage(motor_voltages[i + 1]);
		FL.move_voltage(motor_voltages[i + 2]);
		BL.move_voltage(motor_voltages[i + 3]);
		RollerTop.move_voltage(motor_voltages[i + 4]);
		RollerBot.move_voltage(motor_voltages[i + 5]);
		IntakeR.move_voltage(motor_voltages[i + 6]);
		IntakeL.move_voltage(motor_voltages[i + 7]);
		pros::delay(1);
	}*/
	/*RollerTop = 127;
	RollerBot = 127;
	pros::delay(500);
	RollerTop = 0;
	RollerBot = 0;

	IntakeL = 127;
	IntakeR = 127;

	base.pidDrive(1,200, 1000, 50);

	FR = 50;
	BR = 50;
	FL = -50;
	BL = -50;

	pros::delay(400);
	FR = 0;
	BR = 0;
	FL = 0;
	BL = 0;
	IntakeL = 0;
	IntakeR = 0;

	base.pidDrive(1,700, 1000, 50);
	RollerTop = 127;
	RollerBot = 127;
	pros::delay(1000);
	RollerTop = 0;
	RollerBot = 0;

	FR = -60;
	BR = -60;
	FL = -60;
	BL = -60;

	pros::delay(700);
	FR = 0;
	BR = 0;
	FL = 0;
	BL = 0;*/
	/*
	RollerTop = 127;
	RollerBot = 127;
	pros::delay(500);
	RollerTop = 0;
	RollerBot = 0;

	base.pidDrive(-1, 1000, 1000, 127);

	FR = -50;
	BR = -50;
	FL = 50;
	BL = 50;

	pros::delay(500);

	FR = -50;
	BR = -50;
	FL = 50;
	BL = 50;


	IntakeL = -127;
	IntakeR = -127;

	base.pidDrive(1, 1000, 1000, 127);

	RollerTop = 127;
	RollerBot = 127;*/

}


void opcontrol() {
	while(true) {
		base.drive();
		if(master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			IntakeR = 127;
			IntakeL = 127;
		} else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			IntakeR = -127;
			IntakeL = -127;
		} else {
			IntakeR = 0;
			IntakeL = 0;
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
			RollerTop = -127;
			RollerBot = -127;
		}else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			RollerTop = 127;
			RollerBot = 127;
		} else {
			RollerTop = 0;
			RollerBot = 0;
		}
		pros::delay(1);
	}

}
