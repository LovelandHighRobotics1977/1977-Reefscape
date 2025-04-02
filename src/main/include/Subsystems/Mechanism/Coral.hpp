#pragma once

#include "headers/Headers.hpp"

// sets up the coral intake
class CoralIntake : public frc2::SubsystemBase {
	public:
		CoralIntake();

		void setCoralIntake(double speed);

	private:

		ctre::phoenix6::hardware::TalonFX m_coralIntakeMotor;
	    ctre::phoenix6::configs::TalonFXConfiguration coralIntakeMotorConfig{};
};
