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
		frc2::CommandPtr a_main = AutoFctns::autonomousRoutine(&m_drive, &m_mechanism);
		frc::SendableChooser<int> c_position;
		frc::SendableChooser<int> c_target;
		frc::SendableChooser<int> c_allianceOverride;
};

#endif  // _ROBOT_CONTAINER_H