/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/AutoTurn.h"

AutoTurn::AutoTurn(double angleInput):
anglePID(new WVPIDController(angleKp, angleKi, angleKd, setpoint, false)) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	setpoint = angleInput;
	Requires(Robot::m_drive); 
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void AutoTurn::Initialize() {
Robot::m_drive->resetEncoders();
Robot::m_drive->gyroReset();
anglePID->SetSetPoint(setpoint);
}
// Called repeatedly when this Command is scheduled to run
void AutoTurn::Execute() {
power = anglePID->Tick((Robot::m_drive->getLeftDistance() + Robot::m_drive->getRightDistance())/2);
	if (setpoint > 0) {
		Robot::m_drive->tankDrive(0.15 + power, -0.15 - power);
	}
	else {
		Robot::m_drive->tankDrive(-0.15 - power, 0.15 + power);
	}
}
// Make this return true when this Command no longer needs to run execute()
bool AutoTurn::IsFinished() { 
	if (fabs(anglePID->GetError()) < 1) {
  		return true;
	}
	else { 
		return false;
	}
}

// Called once after isFinished returns true
void AutoTurn::End() {
	Robot::m_drive->tankDrive(0,0);
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoTurn::Interrupted() {}
