#ifndef _ROBOT_CONTAINER_H
#define _ROBOT_CONTAINER_H

#include "Headers/Headers.hpp"
#include "Control/Autonomous.hpp"

class RobotContainer {
	public:
		RobotContainer();

		frc2::Command* GetAutonomousCommand();
		void ConfigureAutonomousChooser();

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


	// Network Tables

		nt::NetworkTableInstance m_networkTable = nt::NetworkTableInstance::GetDefault();

	// Cameras
		
	//Auto routine
};

#endif  // _ROBOT_CONTAINER_H