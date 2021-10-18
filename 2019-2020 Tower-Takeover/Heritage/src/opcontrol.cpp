#include "main.h"

void opcontrol() {
  pros::lcd::initialize();
  while(true) {
    base.drive();
    lift.drive();
    tray.drive();



    //lcd::initialize();
    //pros::lcd::print(0, "%d", placeLight.get_value());
  }
}
