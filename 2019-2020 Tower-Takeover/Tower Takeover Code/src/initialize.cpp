#include "main.h"

//Initializing pros base motor
pros::Motor BR(brPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Back right motor
pros::Motor BL(blPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); //Back left motor
pros::Motor FR(frPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Front right motor
pros::Motor FL(flPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); //Front left motor


//Initializing okapii base motor
//NOT USED IN FINAL BOT
/*
okapi::Motor RB(brPort, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::counts); //Back right motor
okapi::Motor LB(blPort, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::counts); //Back left motor
okapi::Motor RF(frPort, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::counts); //Front right motor
okapi::Motor LF(flPort, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::counts); //Front left motor
*/

//Initializing controllers
pros::Controller master (E_CONTROLLER_MASTER); //Main controller
pros::Controller partner (E_CONTROLLER_PARTNER); //Partner controller

//Initializing other motors
pros::Motor LiftM(liftPort, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_COUNTS); //Arm motor
pros::Motor Intake1(intake1Port, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); //Intake 1 motor
pros::Motor Intake2(intake2Port, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //Intake 2 motor
pros::Motor TrayM(trayPort, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_COUNTS); //Tray motor

//Multitasking booleans
bool multiPlace = false;
bool multiArmUp = false;
bool multiArmDown = false;
bool slowOutTake = false;
bool dunk = false;
bool autoTopCube = false;
bool traydown = false;
bool autoTrayUp = false;
bool autoTrayDown = false;
bool lowTower = false;
bool highTower = false;
bool resetAngler = false;
bool resetLift = false;
bool placeLogic = false;
bool skillsPlace = false;
bool ninePlace = false;
bool lightS = false;

//Initializing classes
Base base;
Lift lift;
Tray tray;

//Initializing sensors
pros::ADIDigitalIn anglerLimit(anglerLimitP);
pros::ADIDigitalIn liftLimit(liftLimitP);
pros::ADIDigitalIn placeBump(bumperP);
pros::ADIAnalogIn placeLight(placeLightP);
pros::ADIUltrasonic rightUltra (rightUltraP1, rightUltraP2);
pros::ADIUltrasonic leftUltra (leftUltraP1, leftUltraP2);
pros::Imu imu (imuPort);


void initialize() {
  imu.reset(); //Start gyroscope

  Task task(taskFunction, (void*)"PROS", //Initialize multitask function
    TASK_PRIORITY_DEFAULT,
    TASK_STACK_DEPTH_DEFAULT,
    "General Task"
  );

  pros::lcd::initialize(); //Initialize lcd

  //Resetting encoders
  TrayM.tare_position();
  LiftM.tare_position();
  base.resetEncoder();

  //Setting brakemode of motors
  LiftM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  TrayM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  Intake1.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  Intake2.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  FL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  FR.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BR.set_brake_mode(E_MOTOR_BRAKE_COAST);


}
