// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain/SwerveModule.hpp"
#include "headers/Headers.hpp"

// sets all of the different required preset motor values
SwerveModule::SwerveModule(const int driveMotorID,     const int angleMotorID,       const int angleEncoderID, units::turn_t magnetOffset)
					  : m_driveMotor{driveMotorID}, m_angleMotor{angleMotorID}, m_angleEncoder{angleEncoderID} {

	driveMotorPID.kS = Drivetrain::Module::Motor::Drive::PID::S; // sets the drive motor's PID values
	driveMotorPID.kV = Drivetrain::Module::Motor::Drive::PID::V;
	driveMotorPID.kA = Drivetrain::Module::Motor::Drive::PID::A;
	driveMotorPID.kP = Drivetrain::Module::Motor::Drive::PID::P;
	driveMotorPID.kI = Drivetrain::Module::Motor::Drive::PID::I;
	driveMotorPID.kD = Drivetrain::Module::Motor::Drive::PID::D;
	driveMotorConfig.WithSlot0(driveMotorPID); // Add Later
	driveMotorConfig.MotorOutput.Inverted = true; // determines if the motor should be inverted
	driveMotorConfig.MotorOutput.NeutralMode = ctre::phoenix6::signals::NeutralModeValue::Brake; // sets devault brake mode  which prevents sliding
	driveMotorConfig.Feedback.WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RotorSensor); // Add Later
	m_driveMotor.GetConfigurator().Apply(driveMotorConfig); // applies drive motor configuration

	angleMotorPID.kS = Drivetrain::Module::Motor::Angle::PID::S; // sets the angle motor's PID values
	angleMotorPID.kV = Drivetrain::Module::Motor::Angle::PID::V;
	angleMotorPID.kA = Drivetrain::Module::Motor::Angle::PID::A;
	angleMotorPID.kP = Drivetrain::Module::Motor::Angle::PID::P;
	angleMotorPID.kI = Drivetrain::Module::Motor::Angle::PID::I;
	angleMotorPID.kD = Drivetrain::Module::Motor::Angle::PID::D;
	angleMotorConfig.WithSlot0(angleMotorPID); // Add Later
	angleMotorConfig.MotorOutput.NeutralMode = ctre::phoenix6::signals::NeutralModeValue::Brake; // sets motor default state to brake.  Prevents sliding
	angleMotorConfig.Feedback.WithRemoteCANcoder(m_angleEncoder); // sets the encoder
	angleMotorConfig.Feedback.SensorToMechanismRatio = 1; // Add Later
	angleMotorConfig.MotorOutput.Inverted = false; // determines if the motor should be inverted
	angleMotorConfig.ClosedLoopGeneral.ContinuousWrap = true; // Add Later
	m_angleMotor.GetConfigurator().Apply(angleMotorConfig); // applies the angle motor's configurations

	angleEncoderConfig.MagnetOffset = 1_tr-magnetOffset; //sets the magnet offset for the motors based on encoder value
	angleEncoderConfig.AbsoluteSensorDiscontinuityPoint = 1_tr; //the value at which the sensor resets.  Similar to an overload value
	angleEncoderConfig.SensorDirection = ctre::phoenix6::signals::InvertedValue::Clockwise_Positive; // sets the direction the motors will move in.  Must be reversed if motors are flipped (I think)
	m_angleEncoder.GetConfigurator().Apply(angleEncoderConfig); // applies encoder configurations
}

frc::SwerveModuleState SwerveModule::GetState() { // obtains what the motor is currently doing?
	return {
		(m_driveMotor.GetVelocity().GetValue().value() * Drivetrain::Module::Motor::Drive::distance_per_rotation)/1_s, // obtains the current speed
		units::degree_t{m_angleEncoder.GetAbsolutePosition().GetValue()} // obtains the motor's position
	};
}

frc::SwerveModulePosition SwerveModule::GetPosition() { // obtains the current position?
	return {
		m_driveMotor.GetPosition().GetValue().value() * Drivetrain::Module::Motor::Drive::distance_per_rotation, // Add Later
		units::degree_t{m_angleEncoder.GetAbsolutePosition().GetValue()} // obtains the current position
	};
}

void SwerveModule::SetDesiredState(const frc::SwerveModuleState& referenceState) { // tells the motor what it should currently be doing

	// Optimize the reference state to avoid spinning further than 90 degrees
	state = frc::SwerveModuleState::Optimize(referenceState, units::degree_t{m_angleEncoder.GetAbsolutePosition().GetValue()});  // ensures a wheel doesn't over rotate 
	// Set the motor outputs.
	m_angleMotor.SetControl(ctre::phoenix6::controls::PositionDutyCycle{units::turn_t{state.angle.Degrees()}}); // sets the angle motor's positoin?
	m_driveMotor.Set((state.speed / Drivetrain::Movement::Maximum::Linear::Velocity).value()); // makes the drive motor drive
}
