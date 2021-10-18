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

bool multiAutonomousBool = false;
bool slowOutTake = false;

Base base;
Lift lift;
Tray tray;

pros::ADIDigitalIn anglerLimit('c');
pros::ADIDigitalIn liftLimit('f');
pros::ADIDigitalIn placeBump('d');
ADIAnalogIn placeLight('e');
pros::ADIEncoder encoderR('a','b', false);
pros::ADIEncoder encoderL('g','h', true);

void multiAutonomous(void*param) {
  while(true) {


    if(pros::competition::is_autonomous()) {
      if(multiAutonomousBool == true) {
    //    Intake1.tare_position();
    //    Intake2.tare_position();
        while(true) {
          if(placeLight.get_value() > 1000) {
            Intake1 = -100;
            Intake2 = -100;
          }
          if(placeLight.get_value() < 1000) {
            Intake1 = 0;
            Intake2 = 0;
            break;
          }
        }
        int time = pros::millis(); //Current Timestamp
        int netTime = 0;
        while(netTime < 5000) { //Sets timeout to 3 seconds
          netTime = pros::millis() - time;
          if(TrayM.get_position() > -2000) { //Sets boundaries for fast movement using encoder position
            TrayM = -127;
          } else if(TrayM.get_position() <= -2000 && TrayM.get_position() > -3800) { //Changes speeds based on encoder positions
            TrayM = -80;
          } else if (TrayM.get_position() <= -3800 && TrayM.get_position() > -5500) {
            TrayM = -60;
          }

          if(TrayM.get_position() <= -5500) { //Tops the place if target position of tray is hit
            break;
          }
        }
        TrayM = 0;
        multiAutonomousBool = false;
      }
    } else if(!pros::competition::is_autonomous()) {
        if(slowOutTake == true) {
          Intake1.tare_position();
          Intake2.tare_position();
          while(Intake1.get_position() > -600){
            Intake1 = -100;
            Intake2 = -100;
          }
          Intake1 = 0;
          Intake2 = 0;
          slowOutTake = false;
        }
    }
    delay(10);
  }
}

void initialize() {
  //multiAutonomousBool = false;
  Task multiAuton(multiAutonomous, (void*)"PROS",
    TASK_PRIORITY_DEFAULT,
    TASK_STACK_DEPTH_DEFAULT,
    "Test1"
  );

  pros::lcd::initialize();
  pros::lcd::print(0, "Hello");

  TrayM.tare_position();
  LiftM.tare_position();
  base.resetEncoder();
  encoderR.reset();
  encoderL.reset();

  FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  LiftM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  TrayM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  Intake1.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  Intake2.set_brake_mode(E_MOTOR_BRAKE_HOLD);

}
