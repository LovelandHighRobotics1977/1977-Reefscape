#ifndef _CORAL_MECHANISM_H
#define _CORAL_MECHANISM_H

#include "headers/Headers.hpp"

class CoralElevator : public frc2::SubsystemBase {
	public:
		CoralElevator();

		void setCoralElevator(double speed);
		int canGoUp();

	private:
		ctre::phoenix6::hardware::TalonFX m_coralElevatorMotor;
	    ctre::phoenix6::configs::TalonFXConfiguration coralElevatorMotorConfig{};
};

class CoralArm : public frc2::SubsystemBase {
	public:
		CoralArm();

		void setCoralArm(double speed);

	private:
		ctre::phoenix6::hardware::TalonFX m_coralArmMotor;
	    ctre::phoenix6::configs::TalonFXConfiguration coralArmMotorConfig{};
};

#endif