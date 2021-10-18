#include "main.h"

//Okapii lib used for motion profiling
//DID NOT USE IN FINAL CODE
/*
std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
    .withMotors({flPort, blPort}, {frPort, brPort})

    .withDimensions(AbstractMotor::gearset::green, {{4_in, 10_in}, imev5GreenTPR})
    .withSensors(okapi::ADIEncoder{'B', 'C'}, okapi::ADIEncoder{'D', 'E', true})
    .withOdometry({{2.75_in, 10.4_in}, quadEncoderTPR}, StateMode::FRAME_TRANSFORMATION) // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis
*/

//Flips out robot at the beginning of matches from compressed version
void flipOut() {
  LiftM.move(-127);
  pros::delay(600);
  LiftM.move(127);
  pros::delay(600);
  LiftM.move(0);
}

//Autonomous for redside unprotected
void redUnprotected() {
  FR = -80; //Backing up during flipout to make sure the robot is squared against the wall
  BR = -80;
  FL = -80;
  BL = -80;
  flipOut(); //Flipout the robot
  lift.setIntakePower(127); //Start intake
  pros::delay(200);
  FR = 0; //Stop backing up
  BR = 0;
  FL = 0;
  BL = 0;

  base.lineUp(300, 127, 100); //Line up at the beginning in order to account for shift in flipout
  base.pidDriveUltra(1, 680, 682, 1200, 100); //Drive foward using Ultrasonic sensor as guide to keep straight
  lift.movePos(460, 500);//Move up lift

  base.pidDrive(1, 700, 800, 50); //Move forwards again to take last cube
  resetLift = true; // Move lift down

  pros::delay(250);

  base.pidIMUTurn(left, 319, 550, 127); //Turn for second line of cubes
  base.pidIMUDrive(-1, 3000,0, 1300, 127); //Using PID to backup and straighten the robot

  autoTrayUp = true; //Move tray up to change weight distribution

  base.pidDriveUltra(1, 1125, 1125, 2300, 80); //Drive forward to intake cubes


  base.pidIMUTurn(right, 149, 1050, 127); //Turn towards goal

  ninePlace = true; // Start placing action
  base.pidDriveBumper(3000, 2000, 85); //Drive until hits bumper at the bottom of the robot
  base.pidDrive(1, 100, 1800, 30); //Drive forward a bit after hitting bumper
  pros::delay(1000);// Wait for stack to place
  base.pidDrive(-1, 2000, 1200, 70); //Drive backwards
}

//Flipped autonomous for blueside unprotected
void blueUnprotected() {
  FR = -80; //Backing up during flipout to make sure the robot is squared against the wall
  BR = -80;
  FL = -80;
  BL = -80;
  flipOut(); //Flipout the robot
  lift.setIntakePower(127); //Start intake
  pros::delay(200);
  FR = 0; //Stop backing up
  BR = 0;
  FL = 0;
  BL = 0;

  base.lineUp(300, 127, 100); //Line up at the beginning in order to account for shift in flipout
  base.pidDriveUltra(1, 680, 682, 1200, 100); //Drive foward using Ultrasonic sensor as guide to keep straight
  lift.movePos(460, 500);//Move up lift

  base.pidDrive(1, 700, 800, 50); //Move forwards again to take last cube
  resetLift = true;; // Move lift down

  pros::delay(250);

  base.pidIMUTurn(right, 41, 550, 127);//Turn for second line of cubes
  base.pidIMUDrive(-1, 3000,0, 1500, 127); //Using PID to backup and straighten the robot

  autoTrayUp = true; //Move tray up to change weight distribution

  base.pidDriveUltra(1, 1125, 1125, 2300, 80);  //Drive forward to intake cubes

  base.pidIMUTurn(left, 211, 1050, 127); //Turn towards goal

  ninePlace = true; // Start placing action
  base.pidDriveBumper(3000, 2000, 85); //Drive until hits bumper at the bottom of the robot
  base.pidDrive(1, 100, 1800, 30); //Drive forward a bit after hitting bumper
  pros::delay(1000);// Wait for stack to place
  base.pidDrive(-1, 2000, 1200, 70); //Drive backwards
}

void skillsAuto() {
  FR = -80; //Backing up during flipout to make sure the robot is squared against the wall
  BR = -80;
  FL = -80;
  BL = -80;
  flipOut(); //Flipout the robot
  lift.setIntakePower(127); //Start intake
  pros::delay(200);
  FR = 0; //Stop backing up
  BR = 0;
  FL = 0;
  BL = 0;

  base.pidDrive(1, 200, 300, 127);  //Drive forward a bit
  pros::delay(500);

  base.pidIMUTurn(right, 43, 500, 127);//Turn towards tower

  slowOutTake = true; //Outtake to get cube into the intake
  lowTower = true; //Move lift up to score low tower

  base.pidDrive(forward, 1300, 900, 127); //Drive towards low tower

  lift.setIntakePower(-65); //Score cube into the tower
  pros::delay(1000);

  base.pidDrive(-1, 1150, 1000, 127); //Drive back

  base.pidIMUTurn(left, 0, 1000, 127); //Turn towards line of cubes straight


  base.lineUp(1000, 127, 150); //line up against the wall

  resetLift = true; //Move lift back down


  lift.setIntakePower(127); //Intake line of cubes
  base.pidDrive(1, 4000, 2300, 80);

  base.pidTurnNearest(0, 600, 127); //Straighten robot off tower

  base.pidIMUDrive(1, 4500, 0,  2800, 80); //Intake next line of cubes

  autoTrayUp = true; //Move tray up for more accurate turns (weight distribution)

  base.pidIMUTurn(right, 90, 1000, 127); //Turn towards scoring zone


  base.pidStrafe(left, 4000, 2500, 127); //Line up sideways against fence


  base.pidDriveBumper(500, 1000,60); //Drive forward and place stack of cubes
  skillsPlace = true;
  pros::delay(5000);


  base.pidDrive(-1, 2000, 2000, 100); //drive back and turn around

  traydown = true;//Reset tray of robot

  base.pidStrafe(left, 600, 800, 127); //Square up against wall
  base.pidStrafe(right, 1590, 2000, 127); //Strafe out to score tower

  lift.setIntakePower(127); //Start intaking

  base.pidIMUTurn(left, 270, 2000, 127); //Turn towards tower with cube
  base.pidDrive(1, 1200, 1500, 60); //Drive and intake the cube
  base.pidDrive(-1, 400, 800, 127); //Back up to score the tower

  lift.setIntakePower(0); //Stop intaking
  slowOutTake = true; //Out take cube into the intakes of the robot

  lift.movePos(2300, 1200); //Move lift up to score tower
  base.pidDrive(1, 350, 600, 60); //Drive forward

  //Set brake mode to make sure outtaking cube into the towers down push the robot backwards
  FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);

  lift.setIntakePower(-127); //Outtake cube into the tower
  pros::delay(1300);

  //Reset brake mode to allow for coast (less drift)
  FL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  FR.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BR.set_brake_mode(E_MOTOR_BRAKE_COAST);

  base.pidDrive(-1, 400, 1000, 60); //Back up after scoring the tower
  base.pidIMUTurn(left, 180, 1000, 127); //Turn towards line of cubes

  lift.setIntakePower(127); //Start intaking

  resetLift = true; //Reset lift

  base.pidDriveUltra(1, 1200,1200, 2500, 80); //Using ultrasonics to move forward
  base.pidTurnNearest(180, 700, 127); //Straighten out the robot in case it hits the fence

  base.pidIMUDrive(1, 6000, 180,3000, 80); //Drive forward and intake second line of cubess

  autoTrayUp = true; //Tray up for more accurate turns

  base.pidIMUTurn(left,90, 1200,127); //Turn towards scoring zone

  base.pidDrive(1, 1700, 1800, 127); //Forward towards zone
  base.pidStrafe(right, 3500, 2000, 127); //Line up against the fence

  base.pidDriveBumper(1500, 1800,70); //Drive until bumper is triggered
  skillsPlace = true; //Place final stack of cubes

  pros::delay(5000); //Wait for place
  base.pidDrive(-1, 2000, 3000, 127); //Drive backwards to complete place
}


void autonomous() {
  redUnprotected();
}
