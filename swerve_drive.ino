// Controls: 
// SWD (Channel 6) -> Up - enabled, down - disabled
// SWA (Channel 5) -> Up - Field relative swerve, down - robot relative swerve
// Left Stick X axis (Channel 1) -> Rotate
// Right Stick X axis (Channel 4) -> Translate left/right
// Right Stick Y axis (Channel 2) -> Translate up/down



unsigned long lastPIDTime = 0;
const unsigned long PIDSampleTime = 100;

struct moduleState {
  float speed;
  float angle;
};
  
struct swerveState{
  moduleState FR;
  moduleState FL;
  moduleState BR;
  moduleState BL;
};

swerveState calculateSwerve(float inputVX, float inputVY, float inputRotation, bool fieldOriented);
#include "driveMotors.h"
#include "turnMotors.h"
#include "fsRCcontrol.h"
#include "gyro.h"
#include "swerveKinematics.h"
#include "constants.h"
#include <SimpleFOC.h>


float target_velocity = 0;
float target_angle = 50;

float estop = 0;

bool fieldOriented = false;

Commander command = Commander(Serial);
void setSpeed(char* cmd) { command.scalar(&target_velocity, cmd); }
void setAngle(char* cmd) { command.scalar(&target_angle, cmd); }

void setP(char* cmd) { command.scalar(&FLKp, cmd); }
void setI(char* cmd) { command.scalar(&FLKi, cmd); }
void setD(char* cmd) { command.scalar(&FLKd, cmd); }


void activateEstop(char* cmd) { command.scalar(&estop, cmd); }

void setup() {
  Serial.begin(115200);

  setupFSRCcontrol();
  setupGyro(); //init gyro first to enable wire2
  setupDriveMotors(); 
  setupTurnMotors(); 
  

  // add target command T
  command.add('F', setSpeed, "target velocity");
  command.add('T', setAngle, "target angle");
  command.add('E', activateEstop, "estop");

  command.add('P', setP, "P");
  command.add('I', setI, "I");
  command.add('D', setD, "D");


}

void loop() {
  //Serial.println("starting loop");
  while (estop == 0 && getFSRCData(6) < 0 ){ //
    
    // Serial.print(getFSRCData(2));
    // Serial.print(" | ");
    // Serial.print(getAngleFR());
    // Serial.print(" ");
    // Serial.print(getAngleFL());
    // Serial.print(" ");
    // Serial.print(getAngleBR());
    // Serial.print(" ");
    // Serial.print(getAngleBL());
    // Serial.print(" | ");
    
    // Serial.print(states.FL.speed);
    // Serial.print(" ");
    // Serial.print(states.FL.angle);
    // Serial.print(" | ");
    // Serial.print(getYaw());
    // Serial.print(" ");
    // Serial.print(states.FL.angle - getYaw());
    // Serial.print(" | ");
    // turnModuleBR(states.BR.angle);
    // driveBR(states.BR.speed);
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    if (getFSRCData(5) <= 0) {
      fieldOriented = true;
    } else {
      fieldOriented = false;
    }

    swerveState states = calculateSwerve(getFSRCData(4), getFSRCData(2), getFSRCData(1)/Constants::wheelRadius, fieldOriented);

    driveFL(states.FL.speed);
    driveFR(states.FR.speed);
    driveBR(states.BR.speed);
    driveBL(states.BL.speed);

    unsigned long currentTime = millis();
    if (getFSRCData(4) == 0 && getFSRCData(2) == 0 && getFSRCData(1) < 10 && getFSRCData(1) > -10){
        estopTurnMotors();
        // Serial.print("turn motors off        ");
    } else {
      if (currentTime - lastPIDTime >= PIDSampleTime) {
      
        turnModuleFL(states.FL.angle);
        turnModuleFR(states.FR.angle);
        turnModuleBR(states.BR.angle);
        turnModuleBL(states.BL.angle);
      }
    }
    Serial.print(fieldOriented);
    Serial.print(" ");
    Serial.print(getYaw());
    Serial.print(" | ");
    Serial.print(getFSRCData(4));
    Serial.print(" ");
    Serial.print(getFSRCData(2));
    Serial.print(" ");
    Serial.print(getFSRCData(1));
    Serial.print(" | ");
    Serial.print(states.FL.angle);
    Serial.print(" ");
    Serial.print(states.FR.angle);
    Serial.print(" ");
    Serial.print(states.BL.angle);
    Serial.print(" ");
    Serial.print(states.BR.angle);
    Serial.print(" ");
    Serial.print(" | ");
    Serial.print(states.FL.speed);
    Serial.print(" ");
    Serial.print(states.FR.speed);
    Serial.print(" ");
    Serial.print(states.BL.speed);
    Serial.print(" ");
    Serial.print(states.BR.speed);
    Serial.print(" ");
    //////////////////////////////////////////////////////////////////////////////////////////////////
    
    //Serial.print(states.BR.speed);

    // Serial.print(FLKp);
    // Serial.print(" ");
    // Serial.print(FLKi);
    // Serial.print(" ");
    // Serial.print(FLKd);
    // Serial.print(" | ");
    //turnModuleFL(target_angle);
    
    
    
    // Serial.print(getYaw());
    // Serial.print(" | ");

    // Serial.print(getAngleFR());
    // Serial.print(" ");
    // Serial.print(getAngleFL());
    // Serial.print(" ");
    // Serial.print(getAngleBL());
    // Serial.print(" ");
    // Serial.println(getAngleBR());

    // driveBR(target_velocity);
    // driveFR(target_velocity);
    // driveFL(target_velocity);
    // driveBL(target_velocity);

    // Serial.println(target_velocity);

    // Serial.print("Ch 2: ");
    // Serial.print(getFSRCData(2));
    // Serial.print(" | ");
    // Serial.print("Ch 3: ");
    // Serial.println(getFSRCData(3));
    Serial.println("");
    command.run();
  }
  Serial.println("E-stop is active. Reset to continue");
  estopTurnMotors();
  estopDriveMotors();
  
  
}


