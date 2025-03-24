#pragma once

#include "subsystems/Mechanism/Algae.hpp"
#include "subsystems/Mechanism/Coral.hpp"

class MechFunctions : public frc2::SubsystemBase {
	public:
		MechFunctions();

		frc2::StartEndCommand algaePunchUp();
		frc2::StartEndCommand algaePunchDown();
		frc2::FunctionalCommand coralElevatorUp();
		frc2::FunctionalCommand coralElevatorDown();
		frc2::SequentialCommandGroup coralArmUp();
		frc2::SequentialCommandGroup coralArmDown();
		frc2::StartEndCommand coralArmPassiveUp();
		frc2::StartEndCommand coralArmPassiveDown();


	private:

        AlgaePunch m_algaePunchMotor;
		CoralElevator m_coralElevatorMotor;
		CoralArm m_coralArmMotor;

		frc::DigitalInput m_elevatorDownSwitch{Mechanism::Coral::LimitDown};
		frc::DigitalInput m_elevatorUpSwitch{Mechanism::Coral::LimitUp};
};

