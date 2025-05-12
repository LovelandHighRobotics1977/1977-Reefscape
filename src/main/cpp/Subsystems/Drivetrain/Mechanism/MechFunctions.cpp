#include "subsystems/Mechanism/MechFunctions.hpp"

MechFunctions::MechFunctions(){}

frc2::SequentialCommandGroup MechFunctions::hangUp(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_climberMotor.setClimber(-0.3); }),
			frc2::WaitCommand(0.35_s)
		),
		frc2::InstantCommand([this] { m_climberMotor.setClimber(0); })
	);
}

frc2::SequentialCommandGroup MechFunctions::hangDown(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_climberMotor.setClimber(0.3); }),
			frc2::WaitCommand(0.2_s)
		),
		frc2::InstantCommand([this] { m_climberMotor.setClimber(0); })
	);
}



frc2::SequentialCommandGroup MechFunctions::elevatorLow(){
	return frc2::SequentialCommandGroup(
		frc2::InstantCommand {[this] { m_elevator.setElevatorTarget(0.5_tr); }}
	);
}

frc2::StartEndCommand MechFunctions::elevatorMid(){
	return frc2::StartEndCommand(
		[this] { m_elevator.setElevatorTarget(1.0_tr); } , 
		[this] { m_elevator.setElevatorTarget(0.0_tr); } , 
		{&m_elevator}
		
	);
}

frc2::StartEndCommand MechFunctions::elevatorHigh(){
	return frc2::StartEndCommand(
		[this] { m_elevator.setElevatorTarget(0.0_tr); } , 
		[this] { m_elevator.setElevatorTarget(0.0_tr); } , 
		{&m_elevator}
	);
}



