#ifndef _ROBOT_CONTAINER_H
#define _ROBOT_CONTAINER_H

#include "Headers/Headers.hpp"
#include "Control/Autonomous.hpp"
#include "subsystems/Mechanism/MechFunctions.hpp"

class RobotContainer {
	public:
		RobotContainer();

		void setAutoValues();
		void ConfigureAutonomousChooser();
		frc2::Command* GetAutonomousCommand();
		
	private:

	// Configuration functions
		void ConfigureButtonBindings();
		void ConfigureDashboard();
		void ConfigureDefaultCommands();

	// Controllers
		Driver m_driver{TeleoperatedMode::Controller::Ports::Driver};
		Operator m_operator{TeleoperatedMode::Controller::Ports::Operator};

	// Subsystems
		DriveSubsystem m_drive;
		MechFunctions m_mechanism;

		


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

#endif  // _ROBOT_CONTAINER_H