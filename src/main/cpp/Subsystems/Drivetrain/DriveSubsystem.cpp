// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include "Subsystems/Drivetrain/AutoAim.hpp"
#include "Subsystems/Drivetrain/DriveSubsystem.hpp"
#include "Headers/Headers.hpp"


DriveSubsystem::DriveSubsystem()
   :m_frontLeft{Drivetrain::Module::Front::Left::Drive,
				Drivetrain::Module::Front::Left::Angle,
				Drivetrain::Module::Front::Left::Encoder,
				Drivetrain::Module::Front::Left::MagnetOffset,},

	m_frontRight{Drivetrain::Module::Front::Right::Drive,
				 Drivetrain::Module::Front::Right::Angle,
				 Drivetrain::Module::Front::Right::Encoder,
				 Drivetrain::Module::Front::Right::MagnetOffset,},

	m_rearLeft{Drivetrain::Module::Rear::Left::Drive,
			   Drivetrain::Module::Rear::Left::Angle,
			   Drivetrain::Module::Rear::Left::Encoder,
			   Drivetrain::Module::Rear::Left::MagnetOffset,},

	m_rearRight{Drivetrain::Module::Rear::Right::Drive,
				Drivetrain::Module::Rear::Right::Angle,
				Drivetrain::Module::Rear::Right::Encoder,
				Drivetrain::Module::Rear::Right::MagnetOffset,},

	m_odometry{DriveKinematics,
				DriveSubsystem::GetHeading(),
				{m_frontLeft.GetPosition(), m_frontRight.GetPosition(),
				m_rearLeft.GetPosition(), m_rearRight.GetPosition()},
				frc::Pose2d{}} {}

/* delete later if works fine
void DriveSubsystem::Periodic() {
	OdometryData data;

	data.angle = DriveSubsystem::GetHeading();

	data.positions[0] = m_frontLeft.GetPosition();
	data.positions[1] = m_frontRight.GetPosition();
	data.positions[2] = m_rearLeft.GetPosition();
	data.positions[3] = m_rearRight.GetPosition();

	m_odometry.Update(data.angle, data.positions);

	Field2d::GetInstance()->m_field.SetRobotPose(m_odometry.GetPose());
}
*/

void DriveSubsystem::Drive(DriveData data) { // sets the drive values
	if(data.targetAprilTag){ // if a variable called targetAprilTag is true, the robot will rotate to be facing the april tag
		fieldRelativeSpeeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(frc::ChassisSpeeds{data.forward, -data.strafe, -2.5_deg_per_s * nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0)}, DriveSubsystem::GetHeading());
	}else{ // standard speed and rotation
		fieldRelativeSpeeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(frc::ChassisSpeeds{data.forward, -data.strafe, data.rotate}, DriveSubsystem::GetHeading()); //uses a built in function, which determines the direction
		robotRelativeSpeeds = frc::ChassisSpeeds{data.forward, -data.strafe, data.rotate}; // for robot relative, doesn't use a function to determine direction
	}

	auto chosenSpeeds = data.fieldRelative ? fieldRelativeSpeeds : robotRelativeSpeeds; // sets the speed based on field or robot relative

	auto states = DriveKinematics.ToSwerveModuleStates(chosenSpeeds, data.centerOfRotation); // uses a built in function to move at given speeds

	DriveKinematics.DesaturateWheelSpeeds(&states, TeleoperatedMode::Parameter::Linear::Velocity); // lowers speeds to a max speed if they are over the max

	auto [fl, fr, rl, rr] = states; // Add Later
	
	m_frontLeft.SetDesiredState(fl);
	m_frontRight.SetDesiredState(fr);
	m_rearLeft.SetDesiredState(rl);
	m_rearRight.SetDesiredState(rr);

}

void DriveSubsystem::SetModuleStates(wpi::array<frc::SwerveModuleState, 4> desiredStates) { // Add Later

	DriveKinematics.DesaturateWheelSpeeds(&desiredStates, AutonomousMode::Parameter::Linear::Velocity);

	m_frontLeft.SetDesiredState(desiredStates[0]);
	m_frontRight.SetDesiredState(desiredStates[1]);
	m_rearLeft.SetDesiredState(desiredStates[2]);
	m_rearRight.SetDesiredState(desiredStates[3]);
}

frc::Rotation2d DriveSubsystem::GetHeading(){ // used to determine which way the robot is facing

	return units::degree_t{Gyro::GetInstance()->ahrs.GetYaw()}; // tells the robot the direction it is currently facing
}

frc2::SequentialCommandGroup DriveSubsystem::ZeroOdometry(frc::Pose2d pose) { // provides a new direction to be forwards
	return frc2::SequentialCommandGroup( // runs both commands at once
		frc2::InstantCommand( [this] {Gyro::GetInstance()->ahrs.Reset();} ), // resets the gyro direction
		frc2::InstantCommand( [this, pose] { DriveSubsystem::ResetOdometry(pose); } ) // runs the reset odometry function, seen below
	);
}

frc::Pose2d DriveSubsystem::GetPose() { // Obtains the "cooridnates" of the robot
	return m_odometry.GetPose(); // Obtains the "cooridnates" of the robot
}

void DriveSubsystem::ResetOdometry(frc::Pose2d pose) { // Add Later
	OdometryData data;

	data.angle = DriveSubsystem::GetHeading(); // determines directiong currently facing

	data.positions[0] = m_frontLeft.GetPosition(); // Add Later
	data.positions[1] = m_frontRight.GetPosition();
	data.positions[2] = m_rearLeft.GetPosition();
	data.positions[3] = m_rearRight.GetPosition();

	m_odometry.ResetPosition(data.angle, data.positions, pose);
}

void DriveSubsystem::driveFromTagDuringAuto(){
	AimFunctions::determineValues(); // get the values needed to be driven
	DriveSubsystem::Drive({
		AimFunctions::getForwardSpeed() *  1_fps, // the * 1_fps converts the double into a usable type for speed
		AimFunctions::getSideSpeed() * 1_fps,
		AimFunctions::getRotationSpeed() * 1_deg_per_s, // the * 1_deg_per_s converts the double into a usable rotation. Radians are also acceptable
		0
	});	
}

frc2::SequentialCommandGroup DriveSubsystem::AutoAlignLeft(DriveSubsystem *drive) { // aligns the robot to the left coral
	return(
		frc2::SequentialCommandGroup{
			frc2::InstantCommand([drive] { drive->Drive({});}), // stops the motion
			frc2::ParallelRaceGroup(
				frc2::RunCommand([drive] { drive->driveFromTagDuringAuto();}),
				frc2::WaitCommand(2_s) // tells how long to run the command
			),
			frc2::ParallelRaceGroup(
				frc2::RunCommand([drive] { drive->Drive({0_fps, 0.9_fps, 0_deg_per_s, 0});}, {drive}), // corrects sideways value
				frc2::WaitCommand(1_s)
			),
			frc2::InstantCommand([drive] { drive->Drive({});}) // ensures motion stops

		}
	);
}

frc2::SequentialCommandGroup DriveSubsystem::AutoAlignRight(DriveSubsystem *drive) { // aligns the robot to the right coral
	return(
		frc2::SequentialCommandGroup{
			frc2::InstantCommand([drive] { drive->Drive({});}),
			frc2::ParallelRaceGroup(
				frc2::RunCommand([drive] { drive->driveFromTagDuringAuto();}),
				frc2::WaitCommand(2_s)
			),
			frc2::ParallelRaceGroup(
				frc2::RunCommand([drive] { drive->Drive({0_fps, -0.9_fps, 0_deg_per_s, 0});}, {drive}),
				frc2::WaitCommand(1_s)
			),
			frc2::InstantCommand([drive] { drive->Drive({});})
		}
	);
}






