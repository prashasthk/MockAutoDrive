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
class AutoTurn : public frc::Command {
 private:
double setpoint;
double error;
double angleKp = 0.03;
double angleKi = 0;
double angleKd = 0;
double power = 0;
double angle = 0;
WVPIDController * anglePID;
 public:
  AutoTurn(double angleInput);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
