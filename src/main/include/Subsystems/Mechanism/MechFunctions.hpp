#pragma once

#include "subsystems/Mechanism/Coral.hpp"

class MechFunctions : public frc2::SubsystemBase {
	public:
		MechFunctions();
		
		frc2::StartEndCommand hangUp();
		frc2::StartEndCommand hangDown();
		
		frc2::StartEndCommand coralArmUp();
		frc2::StartEndCommand coralArmDown();
		frc2::StartEndCommand coralIntake();
		frc2::StartEndCommand coralOutake();

		frc2::StartEndCommand elevatorLow();
		frc2::StartEndCommand elevatorMid();
		frc2::StartEndCommand elevatorHigh();
		frc2::StartEndCommand elevatorDownSlow();

	private:
		Climber m_climberMotor;
		Elevator m_elevator;
		coralArm m_coralArmAngle;
		coralArm m_coralArmIntake;

};

