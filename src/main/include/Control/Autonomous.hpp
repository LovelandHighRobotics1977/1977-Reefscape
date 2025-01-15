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
    static int autonomous_positionSet;
    static int autonomous_targetSet;
    static int autonomous_colorSet;
    enum target{
        //red
        tag10,
        tag11,
        tag9,
        tag8,
        tag7,
        tag6,
        //blue
        tag17,
        tag18,
        tag19,
        tag20,
        tag21,
        tag22
    };
    enum position{
        left,
        right,
        center
    };
    enum color{
        red,
        blue
    };
}
//Add either a namespace or class for below
void mySetAutoRoutine(int position, std::string& target, bool color);





#endif  // _COMMANDS_AUTONOMOUS_H