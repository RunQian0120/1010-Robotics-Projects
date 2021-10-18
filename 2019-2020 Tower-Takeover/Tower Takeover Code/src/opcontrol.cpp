#include "main.h"

void opcontrol() {
  //Set brake mode of base motors at the beginning of driver control
  FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);

  while(true) {
    //Sensor values outputted to lcd screen of the robot
    pros::lcd::print(0, "LiftPos: %f", LiftM.get_position());
    pros::lcd::print(1, "TrayPos: %f", TrayM.get_position());
    pros::lcd::print(2, "TrayLimit: %d", anglerLimit.get_value());
    pros::lcd::print(4, "Right Ultra Distance: %d", rightUltra.get_value());
    pros::lcd::print(5, "Left Ultra Distance: %d", leftUltra.get_value());
    pros::lcd::print(6, "Light Value: %d", placeLight.get_value());

    //Driving all the class drive functions
    base.drive();
    lift.drive();
    tray.drive();

    pros::delay(10); //Makes sure no errors occur with no delay
  }
}
