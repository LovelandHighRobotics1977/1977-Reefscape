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
			1,
			Drivetrain::Movement::Rotate::Around::Center,
			m_driver.coast_mode_toggle });}, 
		{&m_drive}
	));
}

void RobotContainer::ConfigureButtonBindings() {
	frc2::Trigger resetGyro([this] { return m_driver.gyro_reset; });
	resetGyro.OnTrue(frc2::InstantCommand( [] {Gyro::GetInstance()->ahrs.Reset();} ).ToPtr());
	
	frc2::Trigger leftCoral([this] { return m_driver.leftCoral; });
	leftCoral.OnTrue(m_drive.AutoAlignLeft(&m_drive).ToPtr());

	frc2::Trigger rightCoral([this] { return m_driver.rightCoral; });
	rightCoral.OnTrue(m_drive.AutoAlignRight(&m_drive).ToPtr());
	
	frc2::Trigger shootCoral([this] { return m_operator.shootCoral; });
	shootCoral.WhileTrue(m_mechanism.coralRev().ToPtr());

	frc2::Trigger pickUpAlgae([this] { return m_operator.pickUpAlgae; });
	pickUpAlgae.WhileTrue(m_mechanism.algaeRev().ToPtr());

	frc2::Trigger dropAlgae([this] { return m_operator.dropAlgae; });
	dropAlgae.WhileTrue(m_mechanism.algaeRevReverse().ToPtr());

	frc2::Trigger punchAlgae([this] { return m_operator.punchAlgae; });
	punchAlgae.OnTrue(m_mechanism.algaePunch().ToPtr());

	frc2::Trigger dropPunch([this] { return m_operator.dropPunch; });
	dropPunch.OnTrue(m_mechanism.algaePunchDrop().ToPtr());

	frc2::Trigger reverseCoral([this] { return m_operator.reverseCoral; });
	reverseCoral.WhileTrue(m_mechanism.coralRevReverse().ToPtr());

	frc2::Trigger winchUp([this] { return m_operator.winchUp; });
	winchUp.WhileTrue(m_mechanism.winchUp().ToPtr());

	frc2::Trigger winchDown([this] { return m_operator.winchDown; });
	winchDown.WhileTrue(m_mechanism.winchDown().ToPtr());


}

void RobotContainer::ConfigureAutonomousChooser() {

	//Starting position option
	
	c_autoChosen.AddOption("Back of Field (place in opposite color)", 1);
	c_autoChosen.AddOption("Just Drive", 2);
	c_autoChosen.AddOption("Opposite Color", 3);
	c_autoChosen.AddOption("Same Color", 4);
	c_autoChosen.AddOption("Same Color Back", 5);

	frc::SmartDashboard::PutData("Auto Position", &c_autoChosen);
	//create c_position dropdown menu

	//Position set option
	//Alliancee override option

}



void RobotContainer::ConfigureDashboard() {

	cs::UsbCamera DriveCamera = frc::CameraServer::StartAutomaticCapture(0);
	DriveCamera.SetResolution(480, 320);
	cs::UsbCamera DriveCamera2 = frc::CameraServer::StartAutomaticCapture(1);
	DriveCamera2.SetResolution(480, 320);


}

frc2::Command* RobotContainer::GetAutonomousCommand() {
	switch(c_autoChosen.GetSelected()){
		case 1: return RobotContainer::a_main.get();
		case 2: return RobotContainer::a_drive.get();
		case 3: return RobotContainer::a_red.get();
		case 4: return RobotContainer::a_blue.get();
		case 5: return RobotContainer::a_mainSameSide.get();
	}
}