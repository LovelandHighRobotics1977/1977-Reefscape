#ifndef _COMMANDS_SWERVE_H
#define _COMMANDS_SWERVE_H

#include "subsystems/Drivetrain/DriveSubsystem.hpp"

#include "headers/Headers.hpp"

namespace SwerveCommand {
    frc2::SequentialCommandGroup FollowPath(DriveSubsystem *drive, frc::Pose2d startPose, std::vector<frc::Translation2d> waypoints, frc::Pose2d endPose);
    frc2::InstantCommand ResetOdometry(DriveSubsystem *drive, frc::Pose2d pose);

    
    
}



#endif  // _COMMANDS_SWERVE_H