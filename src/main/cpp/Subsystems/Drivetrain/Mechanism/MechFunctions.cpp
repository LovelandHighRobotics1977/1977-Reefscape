#include "subsystems/Mechanism/MechFunctions.hpp"




MechFunctions::MechFunctions(){}

frc2::FunctionalCommand MechFunctions::coralElevatorUp(){
	return frc2::FunctionalCommand(
		[this] { m_coralElevatorMotor.setCoralElevator(0.5); } ,
		[this] { m_coralElevatorMotor.setCoralElevator(0.5); } ,
		[this] (bool interrupted) { m_coralElevatorMotor.setCoralElevator(0); } ,
		[this] {return m_elevatorUpSwitch.Get(); } , //For 1977, add !, for 1822, remove !
		{&m_coralElevatorMotor}
	);
}

frc2::FunctionalCommand MechFunctions::coralElevatorDown(){
	return frc2::FunctionalCommand(
		[this] { m_coralElevatorMotor.setCoralElevator(-0.5); } ,
		[this] { m_coralElevatorMotor.setCoralElevator(-0.5); } ,
		[this] (bool interrupted) { m_coralElevatorMotor.setCoralElevator(0); } ,
		[this] {return !m_elevatorDownSwitch.Get(); } , //For 1977, add !, for 1822, remove !
		{&m_coralElevatorMotor}
	);
}


frc2::StartEndCommand MechFunctions::algaePunchUp(){
	return frc2::StartEndCommand(
		[this] { m_algaePunchMotor.setAlgaePunch(-0.1); } , 
		[this] { m_algaePunchMotor.setAlgaePunch(0); } , 
		{&m_algaePunchMotor}
	);
}

frc2::StartEndCommand MechFunctions::algaePunchDown(){
	return frc2::StartEndCommand(
		[this] { m_algaePunchMotor.setAlgaePunch(0.1); } , 
		[this] { m_algaePunchMotor.setAlgaePunch(0); } , 
		{&m_algaePunchMotor}
	);
}

frc2::SequentialCommandGroup MechFunctions::coralArmUp(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_coralArmMotor.setCoralArm(-0.6); }),
			frc2::WaitCommand(0.35_s)
		),
		frc2::InstantCommand([this] { m_coralArmMotor.setCoralArm(0); })
	);
}

frc2::SequentialCommandGroup MechFunctions::coralArmDown(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_coralArmMotor.setCoralArm(0.6); }),
			frc2::WaitCommand(0.35_s)
		),
		frc2::InstantCommand([this] { m_coralArmMotor.setCoralArm(0); })
	);
}

frc2::StartEndCommand MechFunctions::coralArmPassiveUp(){
	return frc2::StartEndCommand(
		[this] { m_coralArmMotor.setCoralArm(-0.15); } , 
		[this] { m_coralArmMotor.setCoralArm(0); } , 
		{&m_coralArmMotor}
	);
}

frc2::StartEndCommand MechFunctions::coralArmPassiveDown(){
	return frc2::StartEndCommand(
		[this] { m_coralArmMotor.setCoralArm(0.15); } , 
		[this] { m_coralArmMotor.setCoralArm(0); } , 
		{&m_coralArmMotor}
	);
}

