#include "Subsystems/Drivetrain/Commands.hpp"


frc2::SequentialCommandGroup SwerveCommand::FollowPath(DriveSubsystem *drive, frc::Pose2d startPose, std::vector<frc::Translation2d> waypoints, frc::Pose2d endPose) {
	
	frc::TrajectoryConfig config(AutonomousMode::Parameter::Linear::Velocity, AutonomousMode::Parameter::Linear::Acceleration);
	config.SetKinematics(drive->DriveKinematics);

	frc::ProfiledPIDController<units::radians> RotationController{AutonomousMode::Controller::Proportional::Rotate,0,0,AutonomousMode::Controller::Constraint::Rotate};
	RotationController.EnableContinuousInput(units::radian_t{-M_PI}, units::radian_t{M_PI});

	auto Trajectory = frc::TrajectoryGenerator::GenerateTrajectory(
		startPose,
		waypoints,
		endPose,
		config
	);

	return frc2::SequentialCommandGroup(
		frc2::InstantCommand( [Trajectory] { Field2d::GetInstance()->m_field.GetObject("Trajectory")->SetTrajectory(Trajectory); } ),
		frc2::SwerveControllerCommand<4>(
			Trajectory,
			[drive]() { return drive->GetPose(); },
			drive->DriveKinematics,
			frc::PIDController{AutonomousMode::Controller::Proportional::Forward, 0, 0},
			frc::PIDController{AutonomousMode::Controller::Proportional::Strafe, 0, 0},
			RotationController,
			[drive](auto moduleStates) { drive->SetModuleStates(moduleStates); },
			{drive}
		)
	);
}

frc2::InstantCommand SwerveCommand::ResetOdometry(DriveSubsystem *drive, frc::Pose2d pose) {
	return frc2::InstantCommand([drive, pose] { drive->ZeroOdometry(pose); });
}

AutoAlignLeft::AutoAlignLeft(DriveSubsystem *drive) {
	frc2::SequentialCommandGroup{
		frc2::InstantCommand([drive] { drive->Drive({});}),
		frc2::ParallelRaceGroup(
			frc2::RunCommand([drive] { drive->driveFromTagDuringAuto();}),
			frc2::WaitCommand(2_s)
		),
		frc2::ParallelRaceGroup(
			frc2::RunCommand([drive] { drive->Drive({0_fps, 2_fps, 0_deg_per_s, 0});}, {drive}),
			frc2::WaitCommand(1_s)
		)

	};
}

AutoAlignRight::AutoAlignRight(DriveSubsystem *drive) {
	frc2::SequentialCommandGroup{
		frc2::InstantCommand([drive] { drive->Drive({});}),
		frc2::ParallelRaceGroup(
			frc2::RunCommand([drive] { drive->driveFromTagDuringAuto();}),
			frc2::WaitCommand(2_s)
		),
		frc2::ParallelRaceGroup(
			frc2::RunCommand([drive] { drive->Drive({0_fps, -2_fps, 0_deg_per_s, 0});}, {drive}),
			frc2::WaitCommand(1_s)
		)

	};
}

