#pragma once

#include "headers/Headers.hpp"

// sets up the algae intake
class AlgaeIntake : public frc2::SubsystemBase {
	public:
	
		AlgaeIntake();

		void setAlgaeIntake(double speed);

	private:
		ctre::phoenix6::hardware::TalonFX m_algaeIntakeMotor;
	    ctre::phoenix6::configs::TalonFXConfiguration algaeIntakeMotorConfig{}; 
};

// sets up the arm to move algae
class AlgaeWinch : public frc2::SubsystemBase {
	public:

		AlgaeWinch();
		void winchArmMove(double speed);

	private:
		ctre::phoenix6::hardware::TalonFX m_winch;
	    ctre::phoenix6::configs::TalonFXConfiguration winchMotorConfig{};
};

// sets up the algae puncher
class AlgaePuncher : public frc2::SubsystemBase {
	public:
		AlgaePuncher();

		void algaePuncherPunch(double speed);

	private:
		ctre::phoenix6::hardware::TalonFX m_puncher;
	    ctre::phoenix6::configs::TalonFXConfiguration puncherMotorConfig{};
};
