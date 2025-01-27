// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotBase/Robot.hpp"
#include "Control/Autonomous.hpp"

void Robot::RobotInit() {}
void Robot::RobotPeriodic() { 
	frc2::CommandScheduler::GetInstance().Run(); 
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}
void Robot::DisabledExit() {}

void Robot::AutonomousInit() {
	frc::Timer().Restart();
	//RobotContainer().setAutoValues();
	//AutoFctns::setAutoRoutineValues(AutoInfo::positionSet, AutoInfo::targetSetR, AutoInfo::targetSetB, AutoInfo::colorSet);
	m_autonomousCommand = m_container.GetAutonomousCommand(); //Likely not going to use, delete later
	//m_autonomousCommand = RobotContainer::a_main; //sets the auto command to the one and only.  Must change if more get added
	//add new way to get autonomous command
	
	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Schedule(); 
	}
}
void Robot::AutonomousPeriodic() {}
void Robot::AutonomousExit() {}

void Robot::TeleopInit() {
	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Cancel();
		m_autonomousCommand = nullptr;
	}
}
void Robot::TeleopPeriodic() {}
void Robot::TeleopExit() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}
void Robot::TestExit() {}

#ifndef RUNNING_FRC_TESTS
int main() {return frc::StartRobot<Robot>();}
#endif
