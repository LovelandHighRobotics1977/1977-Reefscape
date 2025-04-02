#include "subsystems/Mechanism/MechFunctions.hpp"

// sets up all of the different functions for the mechanism

MechFunctions::MechFunctions(){} // Add Later

frc2::StartEndCommand MechFunctions::algaeRev(){ // Turns on algae intake
	return frc2::StartEndCommand( 
		[this] { m_algaeIntakeMotor.setAlgaeIntake(0.2); } ,  // Turns on the motor at 20% speed
		[this] { m_algaeIntakeMotor.setAlgaeIntake(0); } ,  // Turns off the motor
		{&m_algaeIntakeMotor} // Tells the function the required motor
	);
}

frc2::StartEndCommand MechFunctions::algaeRevReverse(){ // Reverses Algae Intake
	return frc2::StartEndCommand(
		[this] { m_algaeIntakeMotor.setAlgaeIntake(-0.2); } , 
		[this] { m_algaeIntakeMotor.setAlgaeIntake(0); } , 
		{&m_algaeIntakeMotor}
	);
}

frc2::StartEndCommand MechFunctions::coralRev(){ // Turns on the Coral Motor
	return frc2::StartEndCommand(
		[this] { m_coralIntakeMotor.setCoralIntake(-0.1); } , 
		[this] { m_coralIntakeMotor.setCoralIntake(0); } , 
		{&m_coralIntakeMotor}
	);
}

frc2::StartEndCommand MechFunctions::coralRevReverse(){ // Reverses the Coral Motor
	return frc2::StartEndCommand(
		[this] { m_coralIntakeMotor.setCoralIntake(0.1); } , 
		[this] { m_coralIntakeMotor.setCoralIntake(0); } , 
		{&m_coralIntakeMotor}
	);
}

frc2::StartEndCommand MechFunctions::winchUp(){ // Raises the algae arm
	return frc2::StartEndCommand(
		[this] { m_winch.winchArmMove(.54); } , 
		[this] { m_winch.winchArmMove(0); } , 
		{&m_winch}
	);
}

frc2::StartEndCommand MechFunctions::winchDown(){ // lowers the algae arm
	return frc2::StartEndCommand(
		[this] { m_winch.winchArmMove(-.54); } , 
		[this] { m_winch.winchArmMove(0); } , 
		{&m_winch}
	);
}

frc2::SequentialCommandGroup MechFunctions::algaePunch(){ // raises the puncher
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup( 
			frc2::RunCommand([this] { m_puncher.algaePuncherPunch(.3); }),
			frc2::WaitCommand(0.3_s) // runs this command for 0.3 seconds
		),
		frc2::InstantCommand([this] { m_puncher.algaePuncherPunch(0); })
	);
}

frc2::SequentialCommandGroup MechFunctions::algaePunchDrop(){ // lowers the puncher
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_puncher.algaePuncherPunch(-0.3); }),
			frc2::WaitCommand(0.3_s)
		),
		frc2::InstantCommand([this] { m_puncher.algaePuncherPunch(0); })
	);
}


