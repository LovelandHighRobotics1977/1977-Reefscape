#ifndef _Mech_Functions_H
#define _Mech_Functions_H
#include "subsystems/Mechanism/Coral.hpp"
//bool isAbove=false;	
class MechFunctions : public frc2::SubsystemBase {
	public:
		MechFunctions();
		
		frc2::SequentialCommandGroup hangUp();
		frc2::SequentialCommandGroup hangDown();
		
		frc2::SequentialCommandGroup coralArmUp();
		frc2::SequentialCommandGroup coralArmDown();
		frc2::SequentialCommandGroup coralIntake();
		frc2::SequentialCommandGroup coralOutake();

		frc2::SequentialCommandGroup elevatorLow();
		frc2::StartEndCommand elevatorMid();
		frc2::SequentialCommandGroup elevatorHigh();
		frc2::SequentialCommandGroup elevatorMove();
	
		
	private:
		Climber m_climberMotor;
		coralArm m_coralArmAngle;
		coralArm m_coralArmIntake;
		Elevator m_elevatorRight;
		Elevator m_elevatorLeft;
		Elevator m_elevator;
        
};
#endif