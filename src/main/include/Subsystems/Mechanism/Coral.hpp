#ifndef _CORAL_MECHANISM_H
#define _CORAL_MECHANISM_H

#include "headers/Headers.hpp"


class Climber : public frc2::SubsystemBase {
	public:
		Climber();

		void setClimber(double speed);

	private:
		ctre::phoenix6::hardware::TalonFX m_climberMotor;
	    ctre::phoenix6::configs::TalonFXConfiguration climberMotorConfig{};
};

class Elevator : public frc2::SubsystemBase {
	public:
		Elevator();

		void setElevatorTarget(units::angle::turn_t goal);
		
	private:
		ctre::phoenix6::hardware::TalonFX m_elevatorLeft{Mechanism::Coral::elevatorLeft};
		ctre::phoenix6::hardware::TalonFX m_elevatorRight{Mechanism::Coral::elevatorRight};
		ctre::phoenix6::hardware::CANcoder m_elevatorEncoder{Mechanism::Coral::elevatorCancoder};

		ctre::phoenix6::configs::TalonFXConfiguration elevatorLeftMotorConfig{};
		ctre::phoenix6::configs::TalonFXConfiguration elevatorRightMotorConfig{};
		ctre::phoenix6::configs::CANcoderConfiguration elevatorEncoderConfig{};

};


#endif