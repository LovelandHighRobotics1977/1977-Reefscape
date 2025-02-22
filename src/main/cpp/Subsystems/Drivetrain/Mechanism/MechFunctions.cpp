#include "subsystems/Mechanism/MechFunctions.hpp"

MechFunctions::MechFunctions(){}

frc2::StartEndCommand MechFunctions::coralElevatorUp(){
	return frc2::StartEndCommand(
		[this] { m_coralElevatorMotor.setCoralElevator(0.1); } , 
		[this] { m_coralElevatorMotor.setCoralElevator(0); } , 
		{&m_coralElevatorMotor}
	);
}

frc2::StartEndCommand MechFunctions::coralElevatorDown(){
	return frc2::StartEndCommand(
		[this] { m_coralElevatorMotor.setCoralElevator(-0.1); } , 
		[this] { m_coralElevatorMotor.setCoralElevator(0); } , 
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

frc2::SequentialCommandGroup MechFunctions::algaePunchDown(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_algaePunchMotor.setAlgaePunch(0.1); }),
			frc2::WaitCommand(0.1_s)
		),
		frc2::InstantCommand([this] { m_algaePunchMotor.setAlgaePunch(0); })
	);
}
