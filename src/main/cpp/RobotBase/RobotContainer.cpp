// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotBase/RobotContainer.hpp"
#include "headers/Headers.hpp"
#include "Subsystems/Drivetrain/AutoAim.hpp"

RobotContainer::RobotContainer() {
	ConfigureDashboard();
	ConfigureButtonBindings();
	ConfigureDefaultCommands();
	ConfigureAutonomousChooser();
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
	/*
	m_mechanism.SetDefaultCommand(frc2::RunCommand( 
		[this] { m_mechanism.alignArm(false); },
		{&m_mechanism}
	));
	*/
}

void RobotContainer::ConfigureButtonBindings() {
	frc2::Trigger resetGyro([this] { return m_driver.gyro_reset; });
	resetGyro.OnTrue(frc2::InstantCommand( [] {Gyro::GetInstance()->ahrs.Reset();} ).ToPtr());

	frc2::Trigger leftCoral([this] { return m_driver.leftCoral; });
	leftCoral.OnTrue(m_drive.AutoAlignLeft(&m_drive).ToPtr());

	frc2::Trigger rightCoral([this] { return m_driver.rightCoral; });
	rightCoral.OnTrue(m_drive.AutoAlignRight(&m_drive).ToPtr());

	frc2::Trigger elevatorUp([this] { return m_operator.elevatorUp; });
	elevatorUp.WhileTrue(m_mechanism.coralElevatorUp().ToPtr());

	frc2::Trigger elevatorDown([this] { return m_operator.elevatorDown; });
	elevatorDown.WhileTrue(m_mechanism.coralElevatorDown().ToPtr());

	frc2::Trigger punchUp([this] { return m_operator.punchUp; });
	punchUp.WhileTrue(m_mechanism.algaePunchUp().ToPtr());

	frc2::Trigger punchDown([this] { return m_operator.punchDown; });
	punchDown.WhileTrue(m_mechanism.algaePunchDown().ToPtr());

	frc2::Trigger armDown([this] { return m_operator.armDown; });
	armDown.WhileTrue(m_mechanism.coralArmPassiveDown().ToPtr());

	frc2::Trigger armUp([this] { return m_operator.armUp; });
	armUp.WhileTrue(m_mechanism.coralArmPassiveUp().ToPtr());


}

void RobotContainer::ConfigureAutonomousChooser() {

	//Starting position option
	
	c_position.AddOption("Field Center", 1);
	c_position.AddOption("Team Center", 2);
	c_position.AddOption("Outside of Field", 3);
	

	frc::SmartDashboard::PutData("Auto Position", &c_position);
	//create c_position dropdown menu

	//Position set option
	c_target.AddOption("10/21", 1); //The front
	c_target.AddOption("9/20", 2); 
	c_target.AddOption("8/19", 3);
	c_target.AddOption("7/18", 4); //The back
	c_target.AddOption("6/17", 5);
	c_target.AddOption("11/22", 6);

	frc::SmartDashboard::PutData("Auto Target", &c_target);

	//Alliancee override option
	c_allianceOverride.SetDefaultOption("Base Option",0);
	c_allianceOverride.AddOption("Red",1);
	c_allianceOverride.AddOption("Blue",2);

	frc::SmartDashboard::PutData("Alliance Override", &c_allianceOverride);
}

void RobotContainer::setAutoValues() {
	//Set team color, which will provide positive/negative multiplier:
	if(c_allianceOverride.GetSelected() == 0){
		if(auto check = frc::DriverStation::GetAlliance()){
			AutoInfo::colorSet = frc::DriverStation::GetAlliance();
		}
		else{
			AutoInfo::colorSet = frc::DriverStation::Alliance::kRed; //default to red on issue
		}
	}else{
		switch(c_allianceOverride.GetSelected()){
			case 1: AutoInfo::colorSet = frc::DriverStation::Alliance::kRed;
				[[fallthrough]];
			case 2: AutoInfo::colorSet = frc::DriverStation::Alliance::kBlue;
			
		}
	}
	//Set the starting position, which affects arching angle
	switch(c_position.GetSelected()){
		case 1: AutoInfo::positionSet = 1;//true center value
		case 2: AutoInfo::positionSet = 2;//team center value
		case 3: AutoInfo::positionSet = 3;//edge value
		default: AutoInfo::positionSet = 3;
	}
	//Set the Apriltag Target and provide speed and rotation modifiers
	switch(c_target.GetSelected()){
		case 1: AutoInfo::targetSetR = 10; //set red target
				AutoInfo::targetSetB = 21; //set blue target
		case 2: AutoInfo::targetSetR = 9;
				AutoInfo::targetSetB = 20;
		case 3: AutoInfo::targetSetR = 8;
				AutoInfo::targetSetB = 19;
		case 4: AutoInfo::targetSetR = 7;
				AutoInfo::targetSetB = 18;
		case 5: AutoInfo::targetSetR = 6;
				AutoInfo::targetSetB = 17;
		case 6: AutoInfo::targetSetR = 11;
				AutoInfo::targetSetB = 22;
		default: AutoInfo::targetSetR = 10;
				AutoInfo::targetSetB = 21;
	}
}

void RobotContainer::ConfigureDashboard() {

	cs::UsbCamera DriveCamera = frc::CameraServer::StartAutomaticCapture(0);

}

frc2::Command* RobotContainer::GetAutonomousCommand() {
	return RobotContainer::a_main.get();
}