#include "subsystems/Mechanism/MechFunctions.hpp"

MechFunctions::MechFunctions(){}

frc2::StartEndCommand MechFunctions::algaeRev(){
	return frc2::StartEndCommand(
		[this] { m_algaeIntakeMotor.setAlgaeIntake(0.5); } , 
		[this] { m_algaeIntakeMotor.setAlgaeIntake(0); } , 
		{&m_algaeIntakeMotor}
	);
}

frc2::StartEndCommand MechFunctions::algaeRevReverse(){
	return frc2::StartEndCommand(
		[this] { m_algaeIntakeMotor.setAlgaeIntake(-0.5); } , 
		[this] { m_algaeIntakeMotor.setAlgaeIntake(0); } , 
		{&m_algaeIntakeMotor}
	);
}

frc2::StartEndCommand MechFunctions::coralRev(){
	return frc2::StartEndCommand(
		[this] { m_coralIntakeMotor.setCoralIntake(-0.5); } , 
		[this] { m_coralIntakeMotor.setCoralIntake(0); } , 
		{&m_coralIntakeMotor}
	);
}

frc2::StartEndCommand MechFunctions::winchUp(){
	return frc2::StartEndCommand(
		[this] { m_winch.winchArmMove(-0.5); } , 
		[this] { m_winch.winchArmMove(0); } , 
		{&m_winch}
	);
}

frc2::StartEndCommand MechFunctions::winchDown(){
	return frc2::StartEndCommand(
		[this] { m_winch.winchArmMove(0.5); } , 
		[this] { m_winch.winchArmMove(0); } , 
		{&m_winch}
	);
}

frc2::SequentialCommandGroup MechFunctions::algaePunch(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_puncher.algaePuncherPunch(.75); }),
			frc2::WaitCommand(0.1_s)
		),
		frc2::InstantCommand([this] { m_puncher.algaePuncherPunch(0); })
	);
}

frc2::SequentialCommandGroup MechFunctions::algaePunchDrop(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_puncher.algaePuncherPunch(-0.75); }),
			frc2::WaitCommand(0.1_s)
		),
		frc2::InstantCommand([this] { m_puncher.algaePuncherPunch(0); })
	);
}

/*
void alignArm(bool align){

}
*/
