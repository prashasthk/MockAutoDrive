#include "Commands/AutoTest.h"
#include "iostream"
using namespace std;

AutoTest::AutoTest(double _setpoint) : setpoint(_setpoint),
		distancePID(new WVPIDController(distKp, disKi, distKd, setpoint, false)),
				anglePid(new WVPIDController(angleKp, angleKi, angleKd, 0, false)) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::m_drive);
	std::cout << "Autonomous Constructor" << std::endl;

}

// Called just before this Command runs the first time
void AutoTest::Initialize() {
	
	Robot::m_drive->resetEncoders();
	
	Robot::m_drive->gyroReset();
	
	angle = Robot::m_drive->getAngle();
	

	//drive->setStartAbsTicks();
}

// Called repeatedly when this Command is scheduled to run
void AutoTest::Execute() {
	average = fabs((Robot::m_drive->getLeftDistance() + Robot::m_drive->getRightDistance()) / 2);
	double distPidValue = distancePID->Tick(average)/1.66;
  std::cout << "Value: " << average << std::endl;
	//angle = drive->getAngle();
	cout << "Angle: " << angle << endl;
	//double anglePidValue = anglePid->Tick(angle / 100);

	//drive->arcadeDrive(distPidValue, anglePidValue, 0.5);
	//drive->arcadeDrive(pidValue, 0, 0.2);
	//std::cout << "Value: " << average << std::endl;
	iterator += .2;
	double error = Robot::m_drive->getAngle() - angle;
	
	cout << "   Distance: " << average <<endl;

	//cout<<"Error"<< error<<endl;
	//double multiplier = ;
	if(error > .1) {
		//cout << "too much" << endl;
		//drive -> tankDrive(0.5, 0.5);
		/*drive->tankDrive(0.15+ distPidValue + error/15 , 0.15 + distPidValue - error/15);
		std::cout << "Left power More: " << 0.15+ distPidValue + error/15 << std::endl;
		std::cout << "Right power More: " << 0.15 + distPidValue - error/15 << std::endl;*/
		isLeft = true;
		isRight =  false;
	}
	else if (error < -0.1){
		//cout << "too less" << endl;
		//drive -> tankDrive(0.5, 0.5);
		/*drive->tankDrive(0.15+ distPidValue - error/15 , 0.15+ distPidValue + error/15);
		std::cout << "Left power Less: " << 0.15+ distPidValue - error/15 << std::endl;
		std::cout << "Right power Less: " << 0.15+ distPidValue + error/15 << std::endl;*/
		isRight = true;
		isLeft = false;
	}
	if(isLeft){
		Robot::m_drive->tankDrive(0.15+ distPidValue + error/10 , 0.15 + distPidValue - error/10);
		std::cout << "Left power More: " << 0.15+ distPidValue + error/15 << std::endl;
		std::cout << "Right power More: " << 0.15 + distPidValue - error/15 << std::endl;
	}
	else if(isRight){
		Robot::m_drive->tankDrive(0.15+ distPidValue - error/10 , 0.15+ distPidValue + error/10);
		std::cout << "Left power Less: " << 0.15+ distPidValue - error/15 << std::endl;
		std::cout << "Right power Less: " << 0.15+ distPidValue + error/15 << std::endl;
	}
	else {
		Robot::m_drive->tankDrive(0.2+ distPidValue, 0.2+ distPidValue);
		std::cout << "Both power: " << 0.2+ distPidValue << std::endl;
	}

}

// Make this return true when this Command no longer needs to run execute()
bool AutoTest::IsFinished() {
	std::cout << "error is finished VALUE " << fabs(average - setpoint) << std::endl;
	return fabs(average - setpoint) < 3;
}

// Called once after isFinished returns true
void AutoTest::End() {
	std::cout << "error is finished and REACHED END " << fabs(average - setpoint) << std::endl;
	Robot::m_drive->tankDrive(0,0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoTest::Interrupted() {

}
