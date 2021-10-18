#include "main.h"


std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
    .withMotors({flPort, blPort}, {frPort, brPort})

    .withDimensions(AbstractMotor::gearset::green, {{4_in, 10_in}, imev5GreenTPR})
    .withSensors(okapi::ADIEncoder{'B', 'C'}, okapi::ADIEncoder{'D', 'E', true})
    .withOdometry({{2.75_in, 10.4_in}, quadEncoderTPR}, StateMode::FRAME_TRANSFORMATION) // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis

void flipOut() {
  LiftM.move(-127);
  pros::delay(600);
  LiftM.move(127);
  pros::delay(600);
  LiftM.move(0);
}

void driveBumper(int speed) {
  bool breaker = false;
  int startTime = pros::millis();
  int netTime = 0;
  while(breaker == false && netTime <= 2000) {
    netTime  = pros::millis() - startTime;
    if(placeBump.get_value() == 0) {
      FL.move_velocity(70);
      BL.move_velocity(70);
      FR.move_velocity(70);
      BR.move_velocity(70);
    } else {
      FL.move_velocity(0);
      BL.move_velocity(0);
      FR.move_velocity(0);
      BR.move_velocity(0);
      breaker = true;
    }
  }

}

void blueProtected() {
    flipOut();
    lift.setIntakePower(127);

    base.pidDrive(-1, 400, 1200, 127);
    base.pidDrive(1, 200, 1000, 127);
    base.pidStrafe(-1, 700, 1000, 127);
    base.pidDrive(1, 500, 1000, 127);
    base.pidStrafe(1, 200, 700, 127);
    base.pidDrive(1, 500, 1000, 127);
    base.pidTurn(-1, 350, 1000, 127);
    base.pidDrive(1, 1300, 1200, 127);
    base.pidTurn(-1, 650, 1200, 127);
    base.pidDrive(1, 1500, 3000, 70);
}

void redProtected() {

  LiftM.move(-127);
  pros::delay(600);
  LiftM.move(0);
  lift.setIntakePower(127);

  base.lineUp(600, 127, 100);
  base.setLeftPower(-127);
  base.pidStrafe(left, 1200, 1000, 127);
  LiftM.move(127);
  pros::delay(600);

  base.pidDriveUltra(1, 340, 340, 1000,127);

  base.pidIMUTurn(right,90,1000,127);
  base.pidDrive(forward, 2200, 1500,127);
  base.pidDrive(-1, 300, 700, 127);
  base.pidIMUTurn(270, left, 2300,127);
  multiPlace = true;
  base.pidDriveBumper(2200,3000, 127);

  base.pidStrafe(left,600, 1000,127);

}

void redUnprotected() {
/*
 flipOut();
  lift.setIntakePower(127);
  pros::delay(600);
  //autoTopCube = true;
  base.pidDrive(1, 1800, 1400, 100);
  lift.movePos(750, 600);
  base.pidDrive(1, 500, 500, 110);
  resetLift = true;
  pros::delay(600);
  base.pidTurn(left, 625, 1000,127);
  base.pidDrive(-1, 2755, 1500, 127);
  base.pidTurn(right, 600, 800, 127);
  base.lineUp(500, 127, 200);
  base.pidDrive(1, 2700, 2500, 80);
  base.lineUp(1800, 127, 200);
  base.pidTurn(right, 1000, 1000, 127);
  multiPlace = true;
  base.pidStrafe(right, 800, 800, 127);
  base.pidDriveBumper(3000, 2000, 100);
  */
//start jank TURN
  FR = -80;
  BR = -80;
  FL = -80;
  BL = -80;
  TrayM.tare_position();
  flipOut();
  lift.setIntakePower(127);
  pros::delay(200);
  FR = 0;
  BR = 0;
  FL = 0;
  BL = 0;

  base.lineUp(300, 127, 100);
  base.pidDriveUltra(1, 665, 667, 1200, 100); // 680 682
  lift.movePos(450, 500);//450

  lift.setIntakePower(127);
  base.pidDrive(1, 700, 800, 50);
  resetLift = true;
  pros::delay(200);

  base.pidIMUTurn(left, 318, 550, 127);
  base.pidIMUDrive(-1, 3000,0, 1200, 127);

  //base.pidTurn(left, 620, 550,127);
  //base.pidDrive(-1, 2800, 1200, 127);
  //base.pidTurn(right, 650, 550, 127);
//  base.lineUp(400, 127, 200); // 500
  //base.lineUp(500, 127, 200);

  autoTrayUp = true;
  base.pidDriveUltra(1, 1125, 1125, 2300, 80); //2750
  //base.pidStrafe(left, 800, 1000, 127);
  //base.pidDrive(1,500, 1000, 127);
<<<<<<< HEAD
=======
  autoTrayUp = true;

  //base.pidIMUTurn(right, 162, 1800, 90);
  base.pidTurn(-1, 1850, 3000, 80);
  multiPlace = true;
  base.pidDriveBumper(3000, 2000, 85);
  lift.setIntakePower(-10);
>>>>>>> bbd9f9e898f39ad9d7e9cf30d4d7a5d40d00401c


  //base.pidTurn(-1, 1850, 3000, 80);
  base.pidIMUTurn(right, 150, 1100, 127);
  //lift.setIntakePower(70);
  multiPlace = true;
  base.pidDriveBumper(3000, 2000, 85);
  base.pidDrive(1, 100, 1800, 30);
  pros::delay(1000);//800
  base.pidDrive(-1, 2000, 1200, 70);

  //base.pidDrive(-1, 1000, 1000, 127);

  /*
  base.lineUp(1800, 100, 180);
  base.pidIMUTurn(right, 90, 1200,90);
  multiPlace = true;
  base.pidStrafe(right, 1400, 1200, 127);
  driveBumper();
  base.pidDrive(-1, 200, 1000, 127);*/
/*
  flipOut();
  lift.setIntakePower(127);
  pros::delay(1000);
  base.lineUp(500, 127, 100);
  base.pidDriveUltra(1, 680, 682, 1400, 100); //550, 555
  base.pidTurn(left, 720, 1000,127);
  base.pidDrive(-1, 2600, 1500, 127);
  base.pidTurn(right, 700, 800, 127);
  base.lineUp(500, 127, 200);
  base.pidDrive(1, 2400, 2500, 80);
  //base.pidStrafe(left, 800, 1000, 127);
  //base.pidDrive(1,500, 1000, 127);
  base.lineUp(1800, 127, 300);
  base.pidTurn(right, 1000, 1000, 127);
  multiPlace = true;
  base.pidStrafe(right, 1000, 900, 127);
  driveBumper();
  //autoTopCube = true;*/

}

void redUnprotectedSix() {
  //flipOut();
  TrayM.tare_position();
  lift.setIntakePower(127);
  base.lineUp(600, 127, 100);
  base.pidDriveUltra(1, 1070, 1070, 1200, 100);
  base.pidStrafe(left, 700, 1500, 127);
  base.pidDriveUltra(1, 1250, 1250,700, 127);
  base.lineUp(1500, 127, 200);
  base.pidIMUTurn(right, 90, 1200, 100);
  base.pidStrafe(right, 1200, 1200, 127);
  multiPlace = true;
  base.pidDriveBumper(700, 1000, 127);

}

void blueUnprotected() {
  FR = -80;
  BR = -80;
  FL = -80;
  BL = -80;
  TrayM.tare_position();
  flipOut();
  lift.setIntakePower(127);
  pros::delay(200);
  FR = 0;
  BR = 0;
  FL = 0;
  BL = 0;

  base.lineUp(300, 127, 100);
  base.pidDriveUltra(1, 680, 682, 1200, 100);
  lift.movePos(450, 500);//450

  lift.setIntakePower(127);
  base.pidDrive(1, 700, 800, 50);
  resetLift = true;
  pros::delay(200);

  base.pidIMUTurn(right, 42, 550, 127);
  base.pidIMUDrive(-1, 3000,0, 1200, 127);

  //base.pidTurn(left, 620, 550,127);
  //base.pidDrive(-1, 2800, 1200, 127);
  //base.pidTurn(right, 650, 550, 127);
//  base.lineUp(400, 127, 200); // 500
  //base.lineUp(500, 127, 200);

  autoTrayUp = true;
  base.pidDriveUltra(1, 1125, 1125, 2300, 80); //2750
  //base.pidStrafe(left, 800, 1000, 127);
  //base.pidDrive(1,500, 1000, 127);


  //base.pidTurn(-1, 1850, 3000, 80);
  base.pidIMUTurn(left, 209, 1100, 127);
  //lift.setIntakePower(70);
  multiPlace = true;
  base.pidDriveBumper(3000, 2000, 85);
  base.pidDrive(1, 100, 1800, 30);
  pros::delay(1000);//800
  base.pidDrive(-1, 2000, 1200, 70);
}



void moveLiftPos(int speed, int timeOut) {
  //LiftM.tare_position();
  int timeStamp = pros::millis();
  int netTime = 0;
  while(netTime < timeOut) {
    netTime = pros::millis() - timeStamp;
    LiftM = speed;
    //delay(50);
  }
  LiftM = 0;
}


void skillsAuto() {
  //Flipout start
  LiftM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  base.pidDrive(1, 200, 300, 127);//400
  flipOut();
  lift.setIntakePower(127);
  pros::delay(500);

  //turn to tower
  base.pidIMUTurn(right, 40, 500, 127);//1000
//make a task
  slowOutTake = true;
  lift.movePos(1800, 900);//1000

  base.pidDrive(forward, 1300, 1000, 127);

  //score on tower
  lift.setIntakePower(-65);
  pros::delay(1000);

  //Drive back
  base.pidDrive(-1, 1150, 1500, 127);

  //turn straight
  base.pidIMUTurn(left, 0, 1000, 127);

  //smack fence
  base.lineUp(2000, 127, 150);

  //Arm down
  LiftM = 127;
  pros::delay(500);
  LiftM = 0;

  //intake line
  lift.setIntakePower(127);
  base.pidDrive(1, 4000, 3000, 80);

  //turn off tower
  base.pidIMUTurn(right, 0, 600,127);

  //next line
  //base.pidDrive(1, 4000, 1700, 80);

  base.pidIMUDrive(1, 4500, 0,  2800, 80);

  autoTrayUp = true;

  //turn to score
  base.pidIMUTurn(right, 90, 1000, 127);

  //line up on fence
  base.pidStrafe(left, 3500, 2000, 127);

  //driveBumper(70);

  //score
  base.pidDriveBumper(500, 1000,60);
  skillsPlace = true;

  pros::delay(5000);//4000

  //drive back and turn around
  base.pidDrive(-1, 2000, 2000, 100);
  //use multitasking
  TrayM = 127;
  pros::delay(2700);
  TrayM = 0;
  base.pidStrafe(left, 600, 1200, 127);
  base.pidStrafe(right, 1590, 2000, 127); //1550

  lift.setIntakePower(127);


  base.pidIMUTurn(left, 270, 1950, 127);
  base.pidDrive(1, 1200, 1500, 60);//1300
  base.pidDrive(-1, 400, 1000, 127);
  lift.setIntakePower(0);
  slowOutTake = true;
  lift.movePos(2200, 1200);
  base.pidDrive(1, 300, 1000, 60);


  FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);

  lift.setIntakePower(-127);
  pros::delay(1300);


  FL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  FR.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BR.set_brake_mode(E_MOTOR_BRAKE_COAST);


  base.pidDrive(-1, 400, 1000, 60);//300
  base.pidIMUTurn(left, 180, 1000, 127);
  //base.lineUp(1500, 127, 400);
  lift.setIntakePower(127);

  LiftM = 127;
  pros::delay(1000);
  LiftM = 0;
  pros::delay(500);

  //base.pidIMUDrive(1, right, 4000, 180, 3000, 80);
  base.pidDrive(-1, 500, 1000, 127);
  base.pidDriveUltra(1, 1200,1200, 18000, 80);
  base.pidTurnNearest(180, 800, 127);
  lift.setIntakePower(-60);
  pros::delay(300);
  lift.setIntakePower(127);
  base.pidIMUDrive(1, 6000, 180,3000, 80);

  // base.pidIMUDrive(1, right, 5000, 180, 3000, 80);
  autoTrayUp = true;

  //turn to score

  base.pidIMUTurn(left,90, 1200,127);
  //line up on fence
  base.pidDrive(1, 1700, 1800, 127);
  base.pidStrafe(right, 3500, 2000, 127);

  //driveBumper(70);

  //score
  base.pidDriveBumper(1500, 1800,70);
  skillsPlace = true;

  pros::delay(5000);//4000
  base.pidDrive(-1, 2000, 3000, 127);

}


void autonomous() {

  FL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  FR.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BR.set_brake_mode(E_MOTOR_BRAKE_COAST);
<<<<<<< HEAD
//  base.pidIMUTurn(right, 150, 10000, 127);
  //skillsAuto();
  //skillsPlace = true;
//  multiPlace = true;
  //autoTrayUp = true;
  //pros::delay(1000);
  //base.pidIMUTurn(right, 151, 2000, 127);
//  base.pidIMUTurn(left, 270, 2000, 127);
  //base.pidIMUDrive(1, 2000, 180,  5000, 80);
//  base.pidDriveBumper(300, 1000, 70);
  //base.pidTurn(1, 1275, 3000, 80);
//  blueUnprotected();
=======
//  base.pidIMUTurn(right, 90, 10000, 127);
//  skillsAuto();


  //base.pidIMUDrive(1, 2000, 180,  5000, 80);
//  base.pidDriveBumper(300, 1000, 70);
  //base.pidTurn(1, 1275, 3000, 80);
  redUnprotected();
<<<<<<< HEAD
>>>>>>> bbd9f9e898f39ad9d7e9cf30d4d7a5d40d00401c
=======
>>>>>>> bbd9f9e898f39ad9d7e9cf30d4d7a5d40d00401c
  //base.pidIMUDrive(1, right, 2000, 0, 10000, 127);

  /*autoTrayUp = true;
  pros::delay(2000);
  multiPlace = true;*/
  redUnprotected();
//  moveLiftPos(-127, 1000);
/*
  base.pidDrive(1, 250, 1000, 127);
  LiftM = -127;
  pros::delay(1000);
  LiftM = 127;
  pros::delay(1400);
  LiftM = 0;
  lift.setIntakePower(127);
  base.pidDrive(1, 800, 1400, 127);
  base.pidDrive(-1, 900, 1400, 127);
  //base.pidDrive(1, 50, 00, 127);
  base.pidStrafe(-1, 1000, 1800, 127);
  base.pidDrive(-1, 250, 500, 127);
  base.pidDrive(1, 1100, 1700, 90);
  base.pidDrive(-1, 950, 1500, 127);
  lift.setIntakePower(0);
  base.pidTurn(-1, 400, 1000, 127);
  multiPlace = true;
  base.pidStrafe(-1, 600, 1100, 127);
  base.pidDrive(1, 200, 1500, 127);
  pros::delay(1200);
  base.pidDrive(-1, 500, 1000, 127);
*/

  //  moveLiftPos(-127, 1000);


}
