/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/AutoMoveForward.h"
#include "iostream"
using namespace std;

AutoMoveForward::AutoMoveForward(double setpoint):
drivingPIDL(new WVPIDController(distKp, distKi, distKd, targetL, false)), 
drivingPIDR(new WVPIDController(distKp, distKi, distKd, targetR, false)) {
  Requires(Robot::m_drive);
  targetL = setpoint + Robot::m_drive->getLeftDistance();
  targetR = setpoint + Robot::m_drive->getRightDistance();
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void AutoMoveForward::Initialize() {
  Robot::m_drive->resetEncoders();
  drivingPIDL->SetSetPoint(targetL);
  drivingPIDR->SetSetPoint(targetR);
}
// Called repeatedly when this Command is scheduled to run
void AutoMoveForward::Execute() {
  //Robot::m_drive->resetEncoders();

  double distL = Robot::m_drive->getLeftDistance(); 
  double distR = Robot::m_drive->getRightDistance();
  double powerL = -0.5 * drivingPIDL->Tick(distL);
  double powerR = -0.5 * drivingPIDR->Tick(distR);
  cout << "DistanceL: " << distL << " " << distR << endl;
  Robot::m_drive->tankDrive(0.1 + powerL, 0.1 + powerR);
}
// Make this return true when this Command no longer needs to run execute()
bool AutoMoveForward::IsFinished() { 
  double distL = Robot::m_drive->getLeftDistance(); 
  double distR = Robot::m_drive->getRightDistance();
  cout << "Error: " << targetL - distL << " " << targetR - distR << endl;
  if (fabs(distL - targetL) < 3 && fabs(distR - targetR) < 3) {
    return true;
  }
  else {
    return false;
  }
}
// Called once after isFinished returns true
void AutoMoveForward::End() {
  Robot::m_drive->tankDrive(0,0);
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoMoveForward::Interrupted() {}
