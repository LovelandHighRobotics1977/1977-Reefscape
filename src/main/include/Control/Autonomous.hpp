#ifndef _COMMANDS_AUTONOMOUS_H
#define _COMMANDS_AUTONOMOUS_H

#include "headers/Headers.hpp"

#include "subsystems/Drivetrain/DriveSubsystem.hpp"

#include "subsystems/Drivetrain/Commands.hpp"

/*
Run : Shoot once and skedaddle ( In center : goes under the stage )
Basic : Shoot once, pickup and shoot, and skedaddle ( ONLY WORKS ON CENTER )
Advanced : Score as much as possible while still exiting ( ONLY WORKS ON CENTER ) ( UNRELIABLE )
Delay : Shoot, Wait 3 seconds, Do most advanced auto
Maximum : Score as much as possible ( CANNOT EXIT ) ( ONLY WORKS ON CENTER )
*/
namespace AutoInfo{
    //position, target, and color are manually set
    //use enum to set the different potential values aside from color, which will be input with an override
    static int positionSet;
    static int targetSetR;
    static int targetSetB;
    static std::optional<frc::DriverStation::Alliance> colorSet;
    
}
//Add either a namespace or class for below
namespace AutoFctns{
    void setAutoRoutineValues(int position, int targetR, int targetB, std::optional<frc::DriverStation::Alliance> color);

    frc2::CommandPtr autonomousRoutine(DriveSubsystem *drive);
}





#endif  // _COMMANDS_AUTONOMOUS_H