/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "WVPIDController.h"
#include "OI.h"
#include "Subsystems/DriveTrain.h"
#include "../Robot.h"
class AutoTest : public frc::Command {
  private:
double distKp = 0.005;
	double disKi = 0;
	double distKd = 0;
	double angleKp = 0.05;
	double angleKi = 0;
	double angleKd = 0;
	double setpoint;
	double average = 0;
	double angle = 0;
	double iterator = 0.0;
	double MULT = 1.2;
	bool isLeft = false;
	bool isRight = false;

  WVPIDController*distancePID;
  WVPIDController* anglePid;
 public:
  AutoTest(double _setpoint);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
