// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotBase/RobotContainer.hpp"
#include "headers/Headers.hpp"

RobotContainer::RobotContainer() {
	ConfigureDashboard();
	ConfigureButtonBindings();
	ConfigureDefaultCommands();
}

void RobotContainer::ConfigureDefaultCommands() {
	m_driver.SetDefaultCommand(frc2::RunCommand( [this] { m_driver.update(); } , {&m_driver} ));
	m_operator.SetDefaultCommand(frc2::RunCommand( [this] { m_operator.update(); } , {&m_operator} ));
	m_drive.SetDefaultCommand(frc2::RunCommand( 
		[this] { m_drive.Drive({ 
			m_driver.forward * Drivetrain::Movement::Maximum::Linear::Velocity, 
			m_driver.strafe * Drivetrain::Movement::Maximum::Linear::Velocity, 
			m_driver.rotate * Drivetrain::Movement::Maximum::Angular::Velocity, 
			m_driver.field_relative,
			Drivetrain::Movement::Rotate::Around::Center,
			m_driver.coast_mode_toggle });}, 
		{&m_drive}
	));
}

void RobotContainer::ConfigureButtonBindings() {
	frc2::Trigger resetGyro([this] { return m_driver.gyro_reset; });
	resetGyro.OnTrue(frc2::InstantCommand( [] {Gyro::GetInstance()->ahrs.Reset();} ).ToPtr());

}

void RobotContainer::ConfigureAutonomousChooser() {

	//Starting position option
	c_position.AddOption("Team Center", 0);
	c_position.AddOption("Field Center", 1);
	c_position.AddOption("Outside of Field", 2);

	frc::Shuffleboard::GetTab("Autonomous").Add(c_position);

	//Position set option
	c_target.AddOption("10/21", 0); //The front
	c_target.AddOption("9/20", 1); 
	c_target.AddOption("8/19", 2);
	c_target.AddOption("7/18", 3); //The back
	c_target.AddOption("6/17", 4);
	c_target.AddOption("11/22", 5);

	frc::Shuffleboard::GetTab("Autonomous").Add(c_target);

	//Alliancee override option
	c_allianceOverride.SetDefaultOption("--",0);
	c_allianceOverride.AddOption("Red",1);
	c_allianceOverride.AddOption("Blue",2);

	frc::Shuffleboard::GetTab("Autonomous").Add(c_allianceOverride);
}


void RobotContainer::ConfigureDashboard() {

	cs::UsbCamera DriveCamera = frc::CameraServer::StartAutomaticCapture(0);

}