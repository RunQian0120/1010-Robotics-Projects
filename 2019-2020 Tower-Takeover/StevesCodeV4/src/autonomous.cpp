#include "main.h"

#define right -1;
#define left 1;
#define forward 1;
#define backward -1;

void flipOut() {
  lift.setIntakePower(90);
  pros::delay(1000);
  lift.setIntakePower(0);

  pros::delay(100);
  LiftM = -127;
  pros::delay(1000);
  LiftM = 0;
  pros::delay(500);
  LiftM = 127;

}


void blueProtected() {
    flipOut();
    lift.setIntakePower(127);

    base.pidDrive(-1, 400, 1200, .2, 1.2, 127);
    base.pidDrive(1, 200, 1000, .2, 1.2, 127);
    base.pidStrafe(-1, 700, 1000, .35, 1.2, 127);
    base.pidDrive(1, 500, 1000, .2, 1.2, 127);
    base.pidStrafe(1, 200, 700, .35, 1.2, 127);
    base.pidDrive(1, 500, 1000, .2, 1.2, 127);
    base.pidTurn(-1, 350, 1000, .2, 1.2, 127);
    base.pidDrive(1, 1300, 1200, .2, 1.2, 127);
    base.pidTurn(-1, 650, 1200, .2 ,1.2, 127);
    base.pidDrive(1, 1500, 3000, .2, 1.2, 70);
}

void redProtected() {
  flipOut();
  lift.setIntakePower(127);

  base.pidDrive(-1, 500, 1200, .2, 1.2, 127);
  base.pidDrive(1, 200, 1000, .2, 1.2, 127);
  base.pidStrafe(1, 700, 1000, .35, 1.2, 127);
  base.pidDrive(1, 500, 1000, .2, 1.2, 127);
  base.pidStrafe(-1, 200, 700, .35, 1.2, 127);
  base.pidDrive(1, 500, 1000, .2, 1.2, 127);
  base.pidTurn(1, 350, 1000, .2, 1.2, 127);
  base.pidDrive(1, 1300, 1200, .2, 1.2, 127);
  base.pidTurn(1, 650, 1200, .2 ,1.2, 127);
  base.pidDrive(1, 1500, 3000, .2, 1.2, 70);
}

void redUnprotected() {
  flipOut();

  lift.setIntakePower(127);
  base.pidDrive(1, 1200, 2500, .2, 1.2, 127);

  base.pidDrive(-1, 1150, 2000, .2, 1.2, 127);

  base.pidStrafe(-1, 1050, 2000, .35, 1.1, 127);

  base.pidDrive(1, 1200, 2000, .2, 1.2, 100);
  lift.setIntakePower(0);

  base.pidTurn(-1, 850, 1500, .2, 1.2, 127);

  multiAutonomousBool = true;
  base.pidDrive(1, 950, 1500, .2, 1.2, 127);

}


void autonomous() {
  //blueProtected();
  

//  multiAutonomousBool = true;
//  base.pidDrive(1, 500, 1000, .2, 1.2, 127);
//  base.pidTurn(1, 500, 1000, .2, 1.2, 127);
//  base.pidStrafe(1, 500, 1000, .35, 1.2, 127);

//Skills auto
/*
lift.setIntakePower(-127);
pros::delay(600);
LiftM = -127;

pros::delay(1000);
LiftM = 127;
lift.setIntakePower(127);
pros::delay(600);
LiftM = 15;
pros::delay(300);

base.pidDrive(1, 1200, 2500, .35, 1.2, 85);

base.pidDrive(-1, 1150, 2000, .35, 1.2, 127);

base.pidStrafe(-1, 1050, 2000, .3, 1.1, 127);
base.pidDrive(-1, 200, 700, .35, 1.2, 90);
base.pidDrive(1, 1400, 5000, .35, 1.2, 60);
lift.setIntakePower(0);

base.pidDrive(-1, 950, 3000, .35, 1.2, 90);
base.pidTurn(-1, 500, 1000, .4, 1.2, 127);
base.pidStrafe(-1, 1000, 1000, .3, 1.1, 127);
base.pidDrive(1, 150, 700, .35, 1.2, 85);

lift.setIntakePower(-90);
pros::delay(250);
lift.setIntakePower(0);
pros::delay(300);
lift.autoTrayPID();

pros::delay(1000);

base.pidDrive(-1, 300, 1000, .35, 1.2, 127);
//COLLINGWOOD AUTONOMOUS

//base.pidStrafe(1, 530, 1100, .3, 1.1, 127);
//base.pidDrive(1, 500, 1000, .35, 1.2, 127);
//base.pidTurn(1, 500, 1000, .4, 1.2, 127);

//  pros::lcd::initialize();
//  pros::lcd::print(0, "Redside");

*/
  //Redside Protecc

  /*base.pidStrafe(1, 530, 1100, .3, 1.1, 127); //.29, 1.1
  base.pidStrafe(-1, 400, 1000, .3, 1.1, 127);

  //Flipout
  lift.setIntakePower(-127);
  pros::delay(600);
  LiftM = -127;

  pros::delay(1000);
  LiftM = 127;
  lift.setIntakePower(127);
  pros::delay(600);
  LiftM = 15;
  pros::delay(300);
  //End of Flipout


  base.pidDrive(1, 600, 1000, .35, 1.2, 90); //.29, 1.1
  base.pidTurn(-1, 640, 1000, .4, 1.2, 90); //.23 1.7

  base.pidDrive(1, 1000, 1500, .35, 1.2, 90);

  lift.setIntakePower(0);

  base.pidDrive(-1, 1000, 1500, .35, 1.2, 127);
  base.pidTurn(-1, 950, 1500, .4, 1.2, 90);
  base.pidDrive(1, 400, 1000, .35, 1.2, 127);
  lift.autoTrayPID();

  base.pidDrive(-1, 500, 1000, .35, 1.2, 127);*/
  //End of Redside Protecc

  //////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  //Blueside Protecc

  /*
  base.pidStrafe(-1, 530, 1100, .3, 1.1, 127); //.29, 1.1

  base.pidStrafe(1, 400, 1000, .3, 1.1, 127);

  //Flipout
  lift.setIntakePower(-127);
  pros::delay(600);
  LiftM = -127;

  pros::delay(1000);
  LiftM = 127;
  lift.setIntakePower(127);
  pros::delay(600);
  LiftM = 15;
  pros::delay(300);
  //End of Flipout

  base.pidDrive(1, 600, 1000, .35, 1.2, 90); //.29, 1.1
  base.pidTurn(1, 640, 1000, .4, 1.2, 90); //.23 1.7

  base.pidDrive(1, 1000, 1500, .35, 1.2, 90);

  lift.setIntakePower(0);

  base.pidDrive(-1, 1000, 1500, .35, 1.2, 127);
  base.pidTurn(1, 950, 1500, .4, 1.2, 90);
  base.pidDrive(1, 400, 1000, .35, 1.2, 127);
  lift.autoTrayPID();

  base.pidDrive(-1, 500, 1000, .35, 1.2, 127);*/
  //End of Blueside Protecc











































///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


//FIRST COMP AUTOS
















///BLUESIDE
/*
    base.pidDrive(-1, 400, 1000, .29, 1.1, 90);

    base.pidDrive(1, 400, 1000, .29, 1.1, 90);

    base.pidTurn(-1, 660 ,1000,.23, 1.7, 127);

    lift.setIntakePower(-127);
    //pros::delay(300);
    //LiftM.move_absolute(-500, 127);
    //pros::delay(500);


    LiftM = -127;
    pros::delay(400);
    //pros::delay(600);
    LiftM = 127;
    pros::delay(400);
    LiftM = 50;
    lift.setIntakePower(127);

    base.pidDrive(1, 400, 1000, .29, 1.1, 90);
    base.pidTurn(-1, 690, 1000, .23, 1.7, 127);
  //  base.pidDrive(1, 100, 500, .23, 1.7, 127);
    lift.setIntakePower(-127);
    pros::delay(1000);
    base.pidDrive(-1, 300, 1000, .29, 1.1, 90);*/

  //////////////////////////////////////////////////

  //REDSIDE
/*
  base.pidDrive(-1, 400, 1000, .29, 1.1, 90);

  base.pidDrive(1, 400, 1000, .29, 1.1, 90);

  //base.pidTurn(1, 660 ,1000,.23, 1.7, 127);
  lift.setIntakePower(-127);
  //pros::delay(300);
  //LiftM.move_absolute(-500, 127);
  //pros::delay(500);


  LiftM = -127;
  pros::delay(400);
  //pros::delay(600);
  LiftM = 127;
  pros::delay(400);
  LiftM = 50;
  lift.setIntakePower(127);*/

//  base.pidDrive(1, 400, 1000, .29, 1.1, 90);
//  base.pidTurn(1, 690, 1000, .23, 1.7, 127);

//  lift.setIntakePower(-127);
//  pros::delay(1000);
//  base.pidDrive(-1, 300, 1000, .29, 1.1, 90);
//////////////////////////////////////////////////////////////////////////
  //lift.setIntakePower(127);
  //base.pidTurn(1, 500, 1000, .23, 1.7, 127);


  /*lift.setIntakePower(-127);
  //pros::delay(300);
  //LiftM.move_absolute(-500, 127);
  //pros::delay(500);


  LiftM = -127;
  pros::delay(400);
  //pros::delay(600);
  LiftM = 127;
  pros::delay(400);
  LiftM = 50;

  lift.setIntakePower(127);


  base.pidDrive(1, 1300, 2500, .29, 1.1, 70); //.68 // .5


  base.pidTurn(-1, 310, 900, .23, 1.7, 127); // .7 // 1.1

  base.pidDrive(-1, 1330, 1700, .29, 1.1, 127);

  base.pidTurn(1, 300, 800, .23, 1.7, 127);

  base.pidDrive(1, 1300, 3000, .29, 1.1, 70);
  base.pidTurn(1, 860, 1300, .23, 1.7, 127);
  lift.setIntakePower(0);
  base.pidDrive(1, 1200, 1500, .29, 1.1, 127);


  lift.autoTrayPID();
  pros::delay(100);
  base.pidDrive(-1, 500, 800, .29, 1.1, 90);*/

  /*
  lift.setIntakePower(-127);
  //pros::delay(300);
  //LiftM.move_absolute(-500, 127);
  //pros::delay(500);


  LiftM = -127;
  pros::delay(400);
  //pros::delay(600);
  LiftM = 127;
  pros::delay(400);
  LiftM = 50;

  lift.setIntakePower(127);


  base.pidDrive(1, 1300, 2500, .29, 1.1, 70); //.68 // .5


  base.pidTurn(1, 260, 900, .23, 1.7, 127); // .7 // 1.1

  base.pidDrive(-1, 1330, 1700, .29, 1.1, 127);

  base.pidTurn(-1, 300, 900, .23, 1.7, 127);

  base.pidDrive(1, 1300, 3000, .29, 1.1, 70);
  base.pidTurn(-1, 860, 1300, .23, 1.7, 127);
  lift.setIntakePower(0);
  base.pidDrive(1, 1200, 1500, .29, 1.1, 127);


  lift.autoTrayPID();
  pros::delay(100);
  base.pidDrive(-1, 500, 800, .29, 1.1, 90);*/



  ///////////////////////////////////////
  /*
  pros::delay(500);
  base.pidDrive(1, 1300, 4000, .68, .5, 70);


  base.pidTurn(-1, 965, 1300, .7, 1.1, 127);
  lift.setIntakePower(0);
  base.pidDrive(1, 1100, 1500, .68, .5, 90);


  ////////////////////////////////////////////////////////////
  lift.autoTrayPID();
  base.pidDrive(-1, 500, 800, .68, .5, 90);
  */
  ///////////////////////////////////////

  /*lift.setIntakePower(-127);
  //pros::delay(300);
  //LiftM.move_absolute(-500, 127);
  //pros::delay(500);


  LiftM = -127;
  pros::delay(400);
  //pros::delay(600);
  LiftM = 127;
  pros::delay(400);
  LiftM = 50;

  lift.setIntakePower(127);
  pControllerB.generatePath(
    {Point{0_ft,0_ft,0_deg},
    Point{3.1_ft, 4_ft, 0_deg}},
    //Point{5_ft, 5_ft, 0_deg},
    //Point{7_ft, 7_ft, 0_deg}},
    "B"
  );

//  pController.generatePath(
//    {Point{0_ft,0_ft,0_deg},
//    Point{3.5_ft, 0_ft, 0_deg}},
//    //Point{5_ft, 5_ft, 0_deg},
//    //Point{7_ft, 7_ft, 0_deg}},
//    "A"
//  );


  //pController.generatePath(
  //  {Point{0_ft,0_ft,0_deg},
  //  Point{3.6_ft, 0_ft, 0_deg}},
    //Point{5_ft, 5_ft, 0_deg},
    //Point{7_ft, 7_ft, 0_deg}},
  //  "C"
  //)
  //pController.setTarget("A");
//  .waitUntilSettled();


  base.pidDrive(1, 1300, 2000, .68, .5, 70);
//  pros::delay(2100);

  //pController.removePath("A");
  pros::delay(800);
  pControllerB.setTarget("B", true);
  //pControllerB.waitUntilSettled();
  pros::delay(3000);
  pControllerB.removePath("B");




  base.pidDrive(1, 1100, 1600, .68, .5, 70);

  //pController.waitUntilSettled();
  //pController.removePath("C");


  pros::delay(1500);


  base.pidTurn(-1, 870, 1200, .7, 1.1, 127);//715
  lift.setIntakePower(0);
  base.pidDrive(1, 800, 1500, .68, .5, 90);


  ////////////////////////////////////////////////////////////
  lift.autoTrayPID();
  base.pidDrive(-1, 300, 300, .68, .5, 90);*/
  /*
  pController.generatePath(
    {Point{0_ft, 0_ft, 0_deg},
    Point{1_ft, -1.5_ft, 270_deg}},
    "B"
  );

  pController.setTarget("B");
  pController.waitUntilSettled();
  pController.removePath("B");
  */
  /*
  base.pidDrive(-1, 1500, 1300, .7, 1.1, 100);

  pController.generatePath(
    {Point{0_ft,0_ft,0_deg},
    Point{0.5_ft, 2.2_ft, 0_deg}},
    //Point{5_ft, 5_ft, 0_deg},
    //Point{7_ft, 7_ft, 0_deg}},
    "B"
  );

  pController.setTarget("B");
  pController.waitUntilSettled();*/
  /*
  pController.generatePath(
    {Point{0_ft,0_ft,0_deg},
    Point{0.1_ft, -0.2_ft, 90_deg}},
    "B"
  );
  pController.setTarget("B");
  pController.waitUntilSettled();
  pController.removePath("B");*/

  //base.pidTurn(-1, 500, 1000, .68, .5, 127);
}
