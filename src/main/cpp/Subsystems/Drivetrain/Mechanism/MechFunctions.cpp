
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


frc2::SequentialCommandGroup MechFunctions::coralArmDown(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_coralArmAngle.setCoralAngle(-0.3); }),
			frc2::WaitCommand(0.2_s)
		),
		frc2::InstantCommand([this] { m_coralArmAngle.setCoralAngle(0); })
	);
}


frc2::SequentialCommandGroup MechFunctions::coralArmUp(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_coralArmAngle.setCoralAngle(0.3); }),
			frc2::WaitCommand(0.2_s)
		),
		frc2::InstantCommand([this] { m_coralArmAngle.setCoralAngle(0); })
	);
}

frc2::SequentialCommandGroup MechFunctions::coralIntake(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_coralArmIntake.setCoralIntake(0.3); }),
			frc2::WaitCommand(0.2_s)
		),
		frc2::InstantCommand([this] { m_coralArmIntake.setCoralIntake(0); })
	);
}

frc2::SequentialCommandGroup MechFunctions::coralOutake(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_coralArmIntake.setCoralIntake(-0.3); }),
			frc2::WaitCommand(0.2_s)
		),
		frc2::InstantCommand([this] { m_coralArmIntake.setCoralIntake(0); })
	);
}


/*frc2::StartEndCommand MechFunctions::elevatorLow(){
	return frc2::StartEndCommand(	
		[this] { m_elevator.setElevatorTarget(-1.0); } , 
		[this] { m_elevator.setElevatorTarget(0.0); } , 
		{&m_elevator}
	);
}

frc2::StartEndCommand MechFunctions::elevatorMid(){
	return frc2::StartEndCommand(	
		[this] { m_elevator.setElevatorTarget(1.0); } , 
		[this] { m_elevator.setElevatorTarget(0.0); } , 
		{&m_elevator}
	);
}
frc2::SequentialCommandGroup MechFunctions::elevatorLow(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_elevatorRight.SetElevatorMove(-0.3); }),
			frc2::WaitCommand(1_s)
		),
		frc2::InstantCommand([this] { m_elevatorRight.SetElevatorMove(0); })
	);
}


frc2::SequentialCommandGroup MechFunctions::elevatorHigh(){
	return frc2::SequentialCommandGroup(
		frc2::InstantCommand{[this] {m_elevator.setElevatorTarget(0.151367);}}
	);
}

frc2::SequentialCommandGroup MechFunctions::elevatorMove(){
	
	double time=m_elevatorRight.setElevatorTarget(0.251367);
	if (isAbove==true){
	    return frc2::SequentialCommandGroup(
	        frc2::ParallelRaceGroup(
			    frc2::RunCommand([this] { m_elevatorRight.SetElevatorMove(-0.3); }),
			    frc2::WaitCommand(time*1_s)
		    ),
		    frc2::InstantCommand([this] { m_elevatorRight.SetElevatorMove(0); })
	    );
    } else {
		return frc2::SequentialCommandGroup(
	        frc2::ParallelRaceGroup(
			    frc2::RunCommand([this] { m_elevatorRight.SetElevatorMove(0.3); }),
			    frc2::WaitCommand(time*1_s)
		    ),
		    frc2::InstantCommand([this] { m_elevatorRight.SetElevatorMove(0); })
		);
	}
}*/





