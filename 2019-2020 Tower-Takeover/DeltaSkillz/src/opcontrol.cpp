#include "main.h"

void opcontrol() {
  pros::lcd::initialize();
  while(true) {
    //master.print(0,0, "Heading: %f", imu.get_heading());
    pros::lcd::print(0, "Heading: %f", imu.get_heading());
    base.drive();
    lift.drive();
    tray.drive();

    pros::delay(10);
    //lcd::initialize();
    //pros::lcd::print(0, "%d", placeLight.get_value());
  }
}
