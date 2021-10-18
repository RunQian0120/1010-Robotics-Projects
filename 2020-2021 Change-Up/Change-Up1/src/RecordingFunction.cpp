#include "main.h"

void write () {
  FILE*file = fopen("/usd/motor_voltages.txt", "w");

  for(int i = 0; i<motor_voltages.size() - 8; i=i+8) {
    string a = to_string(motor_voltages[i]) + " " +
    to_string(motor_voltages[i + 1]) + " " +
    to_string(motor_voltages[i + 2]) + " " +
    to_string(motor_voltages[i + 3]) + " " +
    to_string(motor_voltages[i + 4]) + " " +
    to_string(motor_voltages[i + 5]) + " " +
    to_string(motor_voltages[i + 6]) + " " +
    to_string(motor_voltages[i + 7]) + " ";

    fputs(a.c_str(), file);
  }

  fclose(file);
}

void read() {

  for(int i = 0; i<motor_voltages.size()-8; i=i+8) {
    FR.move_voltage(motor_voltages[i]);
    BR.move_voltage(motor_voltages[i + 1]);
    FL.move_voltage(motor_voltages[i + 2]);
    BL.move_voltage(motor_voltages[i + 3]);
    RollerTop.move_voltage(motor_voltages[i + 4]);
    RollerBot.move_voltage(motor_voltages[i + 5]);
    IntakeR.move_voltage(motor_voltages[i + 6]);
    IntakeL.move_voltage(motor_voltages[i + 7]);
    pros::delay(1);
  }
}

void recorderFunction(void*param) {
  /*int timeStamp = pros::millis() + 60000;
  while (pros::millis() < timeStamp){
      motor_voltages.push_back(FR.get_voltage());
      motor_voltages.push_back(BR.get_voltage());
      motor_voltages.push_back(FL.get_voltage());
      motor_voltages.push_back(BL.get_voltage());
      motor_voltages.push_back(RollerTop.get_voltage());
      motor_voltages.push_back(RollerBot.get_voltage());
      motor_voltages.push_back(IntakeR.get_voltage());
      motor_voltages.push_back(IntakeL.get_voltage());

      pros::delay(1);
  }
  write();*/
}
