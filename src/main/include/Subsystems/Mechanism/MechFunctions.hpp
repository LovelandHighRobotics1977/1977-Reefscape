#ifndef _MECH_FUNCTIONS_H
#define _MECH_fUNCTIONS_H

#include "subsystems/Mechanism/Algae.hpp"
#include "subsystems/Mechanism/Coral.hpp"

class MechFunctions : public frc2::SubsystemBase {
	public:
		MechFunctions();

		frc2::StartEndCommand algaePunchUp();
		frc2::SequentialCommandGroup algaePunchDown();
		frc2::StartEndCommand coralElevatorUp();
		frc2::StartEndCommand coralElevatorDown();


	private:

        AlgaePunch m_algaePunchMotor;
		CoralElevator m_coralElevatorMotor;
		CoralArm m_coralArmMotor;
};

#endif
