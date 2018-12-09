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
class AutoMoveForward : public frc::Command {
 private:
 double targetL;
 double targetR;
 double distKp = 0.1;
 double distKi = 0;
 double distKd = 0;
 double power = 0;

 WVPIDController * drivingPIDL;
 WVPIDController * drivingPIDR;
 public:
  AutoMoveForward(double setpoint);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
