// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Drivetrain/DriveSubsystem.hpp"
#include "Headers/Headers.hpp"
double sideMove;
double distance;
double rotation;
double distanceTarget;
double rotationTarget;
double sideMoveTarget;
double errorVal;
double cTarget;
// storage variables
double sideAmount;
double distanceAmount;
double RotationAmount;
units::velocity::feet_per_second_t fowardSpeed;
units::velocity::feet_per_second_t sideSpeed;
units::angular_velocity::degrees_per_second_t rotationSpeed;

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

void DriveSubsystem::Drive(DriveData data) {
	if(data.targetAprilTag){
		fieldRelativeSpeeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(frc::ChassisSpeeds{data.forward, -data.strafe, -2.5_deg_per_s * nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0)}, DriveSubsystem::GetHeading());
	}else{
		fieldRelativeSpeeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(frc::ChassisSpeeds{data.forward, -data.strafe, data.rotate}, DriveSubsystem::GetHeading());
		robotRelativeSpeeds = frc::ChassisSpeeds{data.forward, -data.strafe, data.rotate};
	}

	auto chosenSpeeds = data.fieldRelative ? fieldRelativeSpeeds : robotRelativeSpeeds;

	auto states = DriveKinematics.ToSwerveModuleStates(chosenSpeeds, data.centerOfRotation);

	DriveKinematics.DesaturateWheelSpeeds(&states, TeleoperatedMode::Parameter::Linear::Velocity);

	auto [fl, fr, rl, rr] = states;
	
	m_frontLeft.SetDesiredState(fl);
	m_frontRight.SetDesiredState(fr);
	m_rearLeft.SetDesiredState(rl);
	m_rearRight.SetDesiredState(rr);

}

void DriveSubsystem::SetModuleStates(wpi::array<frc::SwerveModuleState, 4> desiredStates) {

	DriveKinematics.DesaturateWheelSpeeds(&desiredStates, AutonomousMode::Parameter::Linear::Velocity);

	m_frontLeft.SetDesiredState(desiredStates[0]);
	m_frontRight.SetDesiredState(desiredStates[1]);
	m_rearLeft.SetDesiredState(desiredStates[2]);
	m_rearRight.SetDesiredState(desiredStates[3]);
}

frc::Rotation2d DriveSubsystem::GetHeading(){
	switch(frc::DriverStation::GetAlliance().value()){
		case frc::DriverStation::kRed:
			return units::degree_t{Gyro::GetInstance()->ahrs.GetYaw()};
			break;

		case frc::DriverStation::kBlue:
			return units::degree_t{180 - Gyro::GetInstance()->ahrs.GetYaw()};
			break;

		default:
			return units::degree_t{180 - Gyro::GetInstance()->ahrs.GetYaw()};
			break;
	}
}

frc2::SequentialCommandGroup DriveSubsystem::ZeroOdometry(frc::Pose2d pose) {
	return frc2::SequentialCommandGroup(
		frc2::InstantCommand( [this] {Gyro::GetInstance()->ahrs.Reset();} ),
		frc2::InstantCommand( [this, pose] { DriveSubsystem::ResetOdometry(pose); } )
	);
}

frc::Pose2d DriveSubsystem::GetPose() {
	return m_odometry.GetPose();
}

void DriveSubsystem::ResetOdometry(frc::Pose2d pose) {
	OdometryData data;

	data.angle = DriveSubsystem::GetHeading();

	data.positions[0] = m_frontLeft.GetPosition();
	data.positions[1] = m_frontRight.GetPosition();
	data.positions[2] = m_rearLeft.GetPosition();
	data.positions[3] = m_rearRight.GetPosition();

	m_odometry.ResetPosition(data.angle, data.positions, pose);
}

frc2::StartEndCommand DriveSubsystem::coralAim(DriveSubsystem *drive) {
	sideMove =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[0];
	distance =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[1];
	rotation =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[5];
	distanceTarget = 0.02;
	sideMoveTarget = 0.02;
	rotationTarget = 0.8;
	errorVal=0.1;
	cTarget = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tid", -1);
	
	if ((cTarget>=7 && cTarget<=11 )|| (cTarget>=17 && cTarget<=22)){
		if(sideMove<=sideMoveTarget+errorVal){
			sideAmount=sideMoveTarget-sideMove;
			sideSpeed = 3_fps;
			return frc2::StartEndCommand(
				[drive] { drive->Drive({0_fps, 3_fps, 0_deg_per_s, 0});}, {drive},
				[drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}
			);
		}else if (sideMove>=sideMoveTarget-errorVal) {
			sideAmount=sideMove-sideMoveTarget;
			sideSpeed = -3_fps;
			return frc2::StartEndCommand(
				[drive] { drive->Drive({0_fps, -3_fps, 0_deg_per_s, 0});}, {drive},
				[drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}
			);
		}
		else if(distance<=distanceTarget+errorVal){
			distanceAmount=distanceTarget-distance;
			fowardSpeed = 3_fps;
			return frc2::StartEndCommand(
				[drive] { drive->Drive({3_fps, 0_fps, 0_deg_per_s, 0});}, {drive},
				[drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}
			);
		}
		
		/*else if (distance>=distanceTarget-errorVal) {
		//	distanceAmount=distance-distanceTarget;
		//	fowardSpeed = -3_fps;
		//}
		else if(rotation<=rotationTarget+errorVal){
			RotationAmount=rotationTarget-rotation;
			rotationSpeed = 5_deg_per_s;
		} else if (rotation>=rotationTarget-errorVal) {
			RotationAmount=rotation-rotationTarget;
			rotationSpeed = -5_deg_per_s;
		}
		*/
		/*
		frc2::RunCommand([drive] { drive->Drive({0_fps, (1_fps * finalMoveMult), 0_deg_per_sec, 0});}, {drive});
		frc2::WaitCommand(1_s);
		frc2::RunCommand([drive] { drive->Drive({0_fps, 0, 0_deg_per_sec, 0});}, {drive});
		*/
	}

	
}