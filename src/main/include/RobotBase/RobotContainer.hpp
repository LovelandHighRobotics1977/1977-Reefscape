#pragma once

#include "Headers/Headers.hpp"
#include "Control/Autonomous.hpp"
#include "subsystems/Mechanism/MechFunctions.hpp"

class RobotContainer {
	public:
		RobotContainer();

		void ConfigureAutonomousChooser(); // used to create the selector for auto commands
		frc2::Command* GetAutonomousCommand(); // used to obtain the auto command to run
		
	private:

	// Configuration functions
		void ConfigureButtonBindings(); // sets the button bindings
		void ConfigureDashboard(); // sets up all cameras to be displayed
		void ConfigureDefaultCommands(); // sets up default commands to be ran (primarily drive)

	// Controllers
		Driver m_driver{TeleoperatedMode::Controller::Ports::Driver}; // sets up a reference to the Driver class in controllers and sets drive port of 0
		Operator m_operator{TeleoperatedMode::Controller::Ports::Operator}; // sets up a reference to the operator class in controllers and sets controller port of 1

	// Subsystems
		DriveSubsystem m_drive; // sets up a reference to the drivesubsystem class, which allows commands from this file to be ran
		MechFunctions m_mechanism; // sets up a reference to the mechanism class

		


	// Network Tables

		nt::NetworkTableInstance m_networkTable = nt::NetworkTableInstance::GetDefault();

	// Cameras
		
	//Auto routine
		frc2::CommandPtr a_main = AutoFctns::backRoutine(&m_drive, &m_mechanism);
		frc2::CommandPtr a_mainSameSide = AutoFctns::backRoutineSameSide(&m_drive, &m_mechanism);
		frc2::CommandPtr a_red = AutoFctns::oppositeSideRoutine(&m_drive, &m_mechanism);
		frc2::CommandPtr a_blue = AutoFctns::sameSideRoutine(&m_drive, &m_mechanism);
		frc2::CommandPtr a_drive = AutoFctns::justDrive(&m_drive);
		frc::SendableChooser<int> c_autoChosen;
};

