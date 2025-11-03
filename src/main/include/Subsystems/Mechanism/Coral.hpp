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

		double setElevatorTarget(double goal);
		void SetElevatorMove(double speed);
		
	private:
		double disEncoder = 0;
		double distanceOverTime=0;
		//bool Above;
		ctre::phoenix6::hardware::TalonFX m_elevatorLeft{Mechanism::Coral::elevatorLeft};
		ctre::phoenix6::hardware::TalonFX m_elevatorRight{Mechanism::Coral::elevatorRight};
		ctre::phoenix6::hardware::core::CoreCANcoder m_elevatorCancoder{16, "rio" };

		ctre::phoenix6::configs::TalonFXConfiguration elevatorLeftMotorConfig{};
		ctre::phoenix6::configs::TalonFXConfiguration elevatorRightMotorConfig{};
		ctre::phoenix6::configs::CANcoderConfiguration elevatorEncoderConfig{};


		frc::PIDController motorPID{0.0 , 0.0, 0.0};

		//frc::SimpleMotorFeedforward<units::radians> feedforward(kP, kV, kA);
		frc::PIDController m_feedforward{0.1, 0.0, 0.0, 1_ms};

};

class coralArm : private frc2::SubsystemBase {
	public:
		coralArm();

		void setCoralAngle(double speed);
		void setCoralIntake(double speed);
	private:
		ctre::phoenix6::hardware::TalonFX m_coralArmAngle{Mechanism::Coral::coralArmAngle};
		ctre::phoenix6::hardware::TalonFXS m_coralArmIntake{Mechanism::Coral::coralArmIntake, "rio"};
		
		ctre::phoenix6::configs::TalonFXConfiguration coralArmAngleConfig{};
		ctre::phoenix6::configs::TalonFXSConfiguration coralArmIntakeConfig{};

};


#endif