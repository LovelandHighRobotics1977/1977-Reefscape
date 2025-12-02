#include "subsystems/Mechanism/MechFunctions.hpp"

MechFunctions::MechFunctions(){}

frc2::StartEndCommand MechFunctions::hangUp(){
	return frc2::StartEndCommand(
		[this] {m_climberMotor.setClimber(-0.3);},
		[this] {m_climberMotor.setClimber(0.0);}
	);
}

frc2::StartEndCommand MechFunctions::hangDown(){
	return frc2::StartEndCommand(
		[this] {m_climberMotor.setClimber(0.3);},
		[this] {m_climberMotor.setClimber(0.0);}
	);
}


frc2::StartEndCommand MechFunctions::coralArmDown(){
	return frc2::StartEndCommand(
		[this] {m_coralArmAngle.setCoralAngle(-0.1);},
		[this] {m_coralArmAngle.setCoralAngle(0.0);}
	);
}

frc2::StartEndCommand MechFunctions::coralArmUp(){
	return frc2::StartEndCommand(
		[this] {m_coralArmAngle.setCoralAngle(0.1);},
		[this] {m_coralArmAngle.setCoralAngle(0.0);}
	);
}

frc2::StartEndCommand MechFunctions::coralIntake(){
	return frc2::StartEndCommand(
		[this] {m_coralArmIntake.setCoralIntake(0.3);},
		[this] {m_coralArmIntake.setCoralIntake(0.0);}
	);
}

frc2::StartEndCommand MechFunctions::coralOutake(){
	return frc2::StartEndCommand(
		[this] {m_coralArmIntake.setCoralIntake(-0.3);},
		[this] {m_coralArmIntake.setCoralIntake(0.0);}
	);
}


frc2::StartEndCommand MechFunctions::elevatorLow(){
	return frc2::StartEndCommand(
		[this] { m_elevator.setElevatorTarget(-0.3);} ,
		[this] { m_elevator.setElevatorTarget(0.0); }
	);
}

frc2::StartEndCommand MechFunctions::elevatorMid(){
	return frc2::StartEndCommand(
		[this] { m_elevator.setElevatorTarget(0.1); } , 
		[this] { m_elevator.setElevatorTarget(0.0); } , 
		{&m_elevator}
		
	);
}

frc2::StartEndCommand MechFunctions::elevatorHigh(){
	return frc2::StartEndCommand(
		[this] { m_elevator.setElevatorTarget(0.3); } , 
		[this] { m_elevator.setElevatorTarget(0.0); } , 
		{&m_elevator}
	);
}

frc2::StartEndCommand MechFunctions::elevatorDownSlow(){
	return frc2::StartEndCommand(
		[this] { m_elevator.setElevatorTarget(-0.1); } , 
		[this] { m_elevator.setElevatorTarget(0.0); } , 
		{&m_elevator}
	);
}



