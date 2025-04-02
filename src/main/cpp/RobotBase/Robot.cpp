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
	m_autonomousCommand = m_container.GetAutonomousCommand(); // obtains the auto command that is needed
	
	if (m_autonomousCommand != nullptr) { // ensures the command exists
		m_autonomousCommand->Schedule();  // gets ready to begin the command
	}
}
void Robot::AutonomousPeriodic() {}
void Robot::AutonomousExit() {}

void Robot::TeleopInit() {
	if (m_autonomousCommand != nullptr) { // ensures there is an auto command
		m_autonomousCommand->Cancel(); // ends the auto command if it hasn't ended yet
		m_autonomousCommand = nullptr; // ensures the auto command can't be started
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
