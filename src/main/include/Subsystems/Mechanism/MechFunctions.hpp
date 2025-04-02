#pragma once

#include "subsystems/Mechanism/Algae.hpp"
#include "subsystems/Mechanism/Coral.hpp"

class MechFunctions : public frc2::SubsystemBase {
	public:
		MechFunctions(); // Add Later

		frc2::StartEndCommand algaeRev(); // creates a command that will have an in process state, and an end state
		frc2::StartEndCommand algaeRevReverse();
		frc2::StartEndCommand coralRev();
		frc2::StartEndCommand coralRevReverse();
		frc2::StartEndCommand winchUp();
		frc2::StartEndCommand winchDown();

		frc2::SequentialCommandGroup algaePunch(); // creates a command that will run until a set condition triggers, usually a timer
		frc2::SequentialCommandGroup algaePunchDrop();

	private:

        AlgaeIntake m_algaeIntakeMotor; //sets the motor references
		CoralIntake m_coralIntakeMotor;
		AlgaeWinch m_winch;
		AlgaePuncher m_puncher;

};

