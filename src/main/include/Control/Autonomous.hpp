#pragma once

#include "headers/Headers.hpp"

#include "subsystems/Drivetrain/DriveSubsystem.hpp"

#include "subsystems/Mechanism/MechFunctions.hpp"


 // sets up the different possible auto routines, only add *mechanism if it's used
namespace AutoFctns{
    frc2::CommandPtr backRoutine(DriveSubsystem *drive, MechFunctions *mechFunctions);
    frc2::CommandPtr backRoutineSameSide(DriveSubsystem *drive, MechFunctions *mechFunctions);
    frc2::CommandPtr sameSideRoutine(DriveSubsystem *drive, MechFunctions *mechFunctions);
    frc2::CommandPtr oppositeSideRoutine(DriveSubsystem *drive, MechFunctions *mechFunctions);
    frc2::CommandPtr justDrive(DriveSubsystem *drive);
}





