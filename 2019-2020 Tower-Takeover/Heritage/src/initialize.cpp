#include "main.h"

pros::Motor FR(frPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
pros::Motor BR(brPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
pros::Motor FL(flPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor BL(blPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

pros::Controller master (E_CONTROLLER_MASTER);
pros::Controller partner (E_CONTROLLER_PARTNER);

pros::Motor LiftM(liftPort, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_COUNTS);

pros::Motor Intake1(intake1Port, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor Intake2(intake2Port, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);

pros::Motor TrayM(trayPort, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_COUNTS);

bool multiPlace = false;
bool multiArmUp = false;
bool multiArmDown = false;
bool slowOutTake = false;

Base base;
Lift lift;
Tray tray;

pros::ADIDigitalIn anglerLimit('c');
pros::ADIDigitalIn liftLimit('f');
pros::ADIDigitalIn placeBump('d');
pros::ADIAnalogIn placeLight('e');


void initialize() {
  //multiPlace = false;
  Task task(taskFunction, (void*)"PROS",
    TASK_PRIORITY_DEFAULT,
    TASK_STACK_DEPTH_DEFAULT,
    "General Task"
  );

  pros::lcd::initialize();
  pros::lcd::print(0, "Hello");

  TrayM.tare_position();
  LiftM.tare_position();
  base.resetEncoder();

  FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  LiftM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  TrayM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  Intake1.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  Intake2.set_brake_mode(E_MOTOR_BRAKE_HOLD);

}
