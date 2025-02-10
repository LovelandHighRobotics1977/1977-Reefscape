#ifndef _CORAL_MECHANISM_H
#define _CORAL_MECHANISM_H

#include "headers/Headers.hpp"

class CoralIntake : public frc2::SubsystemBase {
	public:
		CoralIntake();

		void setCoralIntake(double speed);

	private:

		ctre::phoenix6::hardware::TalonFX m_coralIntakeMotor;
	    ctre::phoenix6::configs::TalonFXConfiguration coralIntakeMotorConfig{};
};

#endif