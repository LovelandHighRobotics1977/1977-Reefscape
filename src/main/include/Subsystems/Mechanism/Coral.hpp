#ifndef _CORAL_MECHANISM_H
#define _CORAL_MECHANISM_H

#include "headers/Headers.hpp"
#include <frc/controller/SimpleMotorFeedforward.h>


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

		void setElevatorTarget(double goal);
		
	private:
		double disEncoder = 0;
		bool isAbove = false;
		ctre::phoenix6::hardware::TalonFX m_elevatorLeft{Mechanism::Coral::elevatorLeft};
		ctre::phoenix6::hardware::TalonFX m_elevatorRight{Mechanism::Coral::elevatorRight};
		frc::Encoder m_elevatorEncoder{0,1};

		ctre::phoenix6::configs::TalonFXConfiguration elevatorLeftMotorConfig{};
		ctre::phoenix6::configs::TalonFXConfiguration elevatorRightMotorConfig{};
		ctre::phoenix6::configs::CANcoderConfiguration elevatorEncoderConfig{};

		frc::PIDController motorPID{0.0 , 0.0, 0.0};

		//frc::SimpleMotorFeedforward<units::radians> feedforward(kP, kV, kA);
		frc::PIDController m_feedforward{0.1, 0.0, 0.0};

};


#endif