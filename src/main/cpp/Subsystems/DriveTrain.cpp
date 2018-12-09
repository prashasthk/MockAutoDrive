/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Subsystems/DriveTrain.h"
#include "Commands/TankDrive.h"
#include "RobotMap.h"
#include "WPILib.h"
#include "math.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain"), left(new TalonSRX(3)), right(new TalonSRX(2)), gyro(new ADXRS450_Gyro()){
  left->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,0,10);
  left->SetSelectedSensorPosition(0,0,10);
  right->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,0,10);
  right->SetSelectedSensorPosition(0,0,10);
  gyro->Reset();
}

void DriveTrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  //SetDefaultCommand(new TankDrive());
}

void DriveTrain::gyroReset() {
	gyro->Reset();
}
double DriveTrain::getAngle() {
	double angle = gyro->GetAngle();
	//-180 to 180
	while (angle > 180) {
		angle -= 360;
	}
	while (angle < -180) {
		angle += 360;
	}
	return angle;
}

void DriveTrain::tankDrive(double leftPow, double rightPow){
  left->Set(ControlMode::PercentOutput, -leftPow);
  right->Set(ControlMode::PercentOutput, rightPow);
}
void DriveTrain::resetEncoders() {
  left->SetSelectedSensorPosition(0,0,10);
  right->SetSelectedSensorPosition(0,0,10);
}

double DriveTrain::getLeftDistance() {
  double relativePosition = left->GetSensorCollection().GetQuadraturePosition();
  return relativePosition*6*M_PI /4096; //6pi is the circumferece (needs to be double checked) and 4096 is ticks per rev
}

double DriveTrain::getRightDistance() {
  double relativePosition = right->GetSensorCollection().GetQuadraturePosition();
  return relativePosition*6*M_PI /4096; //6pi is the circumferece (needs to be double checked) and 4096 is ticks per rev
} 
// Put methods for controlling this subsystem
// here. Call these from Commands.
