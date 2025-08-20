#pragma once

#include "subsystems/Mechanism/Coral.hpp"

class MechFunctions : public frc2::SubsystemBase {
	public:
		MechFunctions();
		
		frc2::SequentialCommandGroup hangUp();
		frc2::SequentialCommandGroup hangDown();
		
		frc2::SequentialCommandGroup coralArmUp();
		frc2::SequentialCommandGroup coralArmDown();
		frc2::SequentialCommandGroup coralIntake();
		frc2::SequentialCommandGroup coralOutake();

		frc2::SequentialCommandGroup elevatorLow();
		frc2::StartEndCommand elevatorMid();
		frc2::StartEndCommand elevatorHigh();

	private:
		Climber m_climberMotor;
		Elevator m_elevator;
		coralArm m_coralArmAngle;
		coralArm m_coralArmIntake;

};

