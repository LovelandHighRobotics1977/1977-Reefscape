#ifndef _MECH_FUNCTIONS_H
#define _MECH_fUNCTIONS_H

#include "subsystems/Mechanism/Algae.hpp"
#include "subsystems/Mechanism/Coral.hpp"

class MechFunctions : public frc2::SubsystemBase {
	public:
		MechFunctions();

		frc2::StartEndCommand algaeRev();
		frc2::StartEndCommand algaeRevReverse();
		frc2::StartEndCommand coralRev();
		frc2::StartEndCommand coralRevReverse();
		frc2::SequentialCommandGroup winchUp();
		frc2::SequentialCommandGroup winchDown();

		frc2::SequentialCommandGroup algaePunch();
		frc2::SequentialCommandGroup algaePunchDrop();


		//void alignArm(bool align);



	private:

        AlgaeIntake m_algaeIntakeMotor;
		CoralIntake m_coralIntakeMotor;
		AlgaeWinch m_winch;
		AlgaePuncher m_puncher;

};

#endif