#ifndef _ALGAE_MECHANISM_H
#define _ALGAE_MECHANISM_H

#include "headers/Headers.hpp"

class AlgaeIntake : public frc2::SubsystemBase {
	public:

		AlgaeIntake();

		void setAlgaeIntake(double speed);

        

	private:

		ctre::phoenix6::hardware::TalonFX m_algaeIntakeMotor;
	    ctre::phoenix6::configs::TalonFXConfiguration algaeIntakeMotorConfig{};

       
};

class AlgaeWinch : public frc2::SubsystemBase {
	public:
		AlgaeWinch();

		void winchArmMove(double speed);


	private:
		ctre::phoenix6::hardware::TalonFX m_winch;
	    ctre::phoenix6::configs::TalonFXConfiguration winchMotorConfig{};

};

class AlgaePuncher : public frc2::SubsystemBase {
	public:
		AlgaePuncher();

		void algaePuncherPunch(double speed);

	private:
		ctre::phoenix6::hardware::TalonFX m_puncher;
	    ctre::phoenix6::configs::TalonFXConfiguration puncherMotorConfig{};
};

#endif