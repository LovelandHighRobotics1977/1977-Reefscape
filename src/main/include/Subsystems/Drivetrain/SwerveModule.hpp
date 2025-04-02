#pragma once

#include "headers/Headers.hpp"

class SwerveModule {
 public:
	SwerveModule(int driveMotorID, int angleMotorID, int angleEncoderID, units::turn_t magnetOffset); // obtains 3 ID's, which are the IDs of 1 drive, 1 encoder, 1 angle, and sets their preset values

	frc::SwerveModuleState GetState(); // Add Later

	frc::SwerveModulePosition GetPosition(); // Add Later

	void SetDesiredState(const frc::SwerveModuleState& state); // Add Later

 private:
	// create the motors and their configurations
	// defines the drive motor values
	ctre::phoenix6::hardware::TalonFX m_driveMotor; 
	ctre::phoenix6::configs::TalonFXConfiguration driveMotorConfig{};
	ctre::phoenix6::configs::Slot0Configs driveMotorPID{};
	swerveMotorOutput driveOutput;

	// defines the angle motor values
	ctre::phoenix6::hardware::TalonFX m_angleMotor;
	ctre::phoenix6::configs::TalonFXConfiguration angleMotorConfig{};
	ctre::phoenix6::configs::Slot0Configs angleMotorPID{};
	swerveMotorOutput angleOutput;

	// defines the encoder values
	ctre::phoenix6::hardware::CANcoder m_angleEncoder;
	ctre::phoenix6::configs::MagnetSensorConfigs angleEncoderConfig{};

	frc::SwerveModuleState state; // Add Later
};
