// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotBase/RobotContainer.hpp"
#include "headers/Headers.hpp"
#include "Subsystems/Drivetrain/AutoAim.hpp"

RobotContainer::RobotContainer() {
	ConfigureDashboard(); // sets up all USB cameras
	ConfigureButtonBindings(); // sets up the button bindings for commands
	ConfigureDefaultCommands(); // sets default commands to be ran
	ConfigureAutonomousChooser(); // sets up the auto routine selector
}

void RobotContainer::ConfigureDefaultCommands() {
	m_driver.SetDefaultCommand(frc2::RunCommand( [this] { m_driver.update(); } , {&m_driver} )); // sets a devault command for the driver class, which recieves updates to drive controller
	m_operator.SetDefaultCommand(frc2::RunCommand( [this] { m_operator.update(); } , {&m_operator} )); // sets a default command for the operator class, which recieves updates to xbox controller
	m_drive.SetDefaultCommand(frc2::RunCommand( // sets a default command for the drivetrain, which runs based on controller input
		[this] { m_drive.Drive({ 
			m_driver.forward * Drivetrain::Movement::Maximum::Linear::Velocity, 
			m_driver.strafe * Drivetrain::Movement::Maximum::Linear::Velocity, 
			m_driver.rotate * Drivetrain::Movement::Maximum::Angular::Velocity, 
			1,
			Drivetrain::Movement::Rotate::Around::Center,
			//m_driver.coast_mode_toggle
		});},
		{&m_drive}
	));
}

void RobotContainer::ConfigureButtonBindings() { // sets up the different button bindings
	frc2::Trigger resetGyro([this] { return m_driver.gyro_reset; }); // links to the variable in the controller file
	resetGyro.OnTrue(frc2::InstantCommand( [] {Gyro::GetInstance()->ahrs.Reset();} ).ToPtr()); // runs the command when button pressed
	
	frc2::Trigger leftCoral([this] { return m_driver.leftCoral; });
	leftCoral.OnTrue(m_drive.AutoAlignLeft(&m_drive).ToPtr());

	frc2::Trigger rightCoral([this] { return m_driver.rightCoral; });
	rightCoral.OnTrue(m_drive.AutoAlignRight(&m_drive).ToPtr());
	
	frc2::Trigger shootCoral([this] { return m_operator.shootCoral; });
	shootCoral.WhileTrue(m_mechanism.coralRev().ToPtr()); // runs the command while button pressed

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

	// sets up the different auto routines, with their text and ID # in the dashboard
	c_autoChosen.AddOption("Back of Field (place in opposite color)", 1); // AddOption allows for them to be chosen between
	c_autoChosen.AddOption("Just Drive", 2);
	c_autoChosen.AddOption("Opposite Color", 3);
	c_autoChosen.AddOption("Same Color", 4);
	c_autoChosen.AddOption("Same Color Back", 5);

	frc::SmartDashboard::PutData("Auto Position", &c_autoChosen); // creates the options in the dashboard

}



void RobotContainer::ConfigureDashboard() {

	cs::UsbCamera DriveCamera = frc::CameraServer::StartAutomaticCapture(0); // sests up a USB camera and starts it
	DriveCamera.SetResolution(480, 320); // sets a specific resolution.  Framerate can also be configured.  Must be done for bandwidth limits
	cs::UsbCamera DriveCamera2 = frc::CameraServer::StartAutomaticCapture(1);
	DriveCamera2.SetResolution(480, 320);


}

frc2::Command* RobotContainer::GetAutonomousCommand() {
	switch(c_autoChosen.GetSelected()){ // chooses the number of auto that was selected based on Auto Chooser
		case 1: return RobotContainer::a_main.get();
		case 2: return RobotContainer::a_drive.get();
		case 3: return RobotContainer::a_red.get();
		case 4: return RobotContainer::a_blue.get();
		case 5: return RobotContainer::a_mainSameSide.get();
		default: return RobotContainer::a_drive.get();
	}
}