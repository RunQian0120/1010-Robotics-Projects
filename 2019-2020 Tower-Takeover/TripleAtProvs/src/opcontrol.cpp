#include "main.h"

void opcontrol() {

  pros::lcd::initialize();

  FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);

  while(true) {
    //master.print(0,0, "Heading: %f", imu.get_heading());
    pros::lcd::print(0, "LiftPos: %f", LiftM.get_position());
    pros::lcd::print(1, "TrayPos: %f", TrayM.get_position());
    pros::lcd::print(2, "TrayLimit: %d", anglerLimit.get_value());

    pros::lcd::print(3, "TrayMotor: %d", TrayM.get_power());
    pros::lcd::print(4, "Right Ultra Distance: %d", rightUltra.get_value());
    pros::lcd::print(5, "Left Ultra Distance: %d", leftUltra.get_value());
    pros::lcd::print(6, "Light Value: %d", placeLight.get_value());

    base.drive();
    lift.drive();
    tray.drive();

    pros::delay(10);
    //lcd::initialize();
    //pros::lcd::print(0, "%d", placeLight.get_value());
  }
}
