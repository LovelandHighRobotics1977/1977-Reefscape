#include "Control/Autonomous.hpp"
//In the future, pose estimation will be used to determine the location and accuracy for auto


/* example auto routine

sets the auto routine name and devices to be used.  In this case, it is named smapleAuto, and will
use the drivetrain and note mechanism:
frc2::CommandPtr AutoRoutine::sampleAuto(DriveSubsystem *drive, NoteMechanism *noteMechanism) {

	This tells the auto routine to complete all of the actions in order
    return frc2::SequentialCommandGroup(

		This will reset the gyro
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),

            frc2::SequentialCommandGroup(

				This will have the bot immediately stop:
				frc2::InstantCommand([drive] { drive->Drive({});}),

				This will have the bot shoot a note, which takes around 0.5 seconds:
				noteMechanism->ShootNote()

				//This will set a function to be called
				frc2::ParallelRaceGroup(

					In this case, the function is to drive, which is determined by (forwards/backwards, left/right, rotation, and orientation base):
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),

					This line will have the robot pick up a note while driving:
                    frc2::RunCommand([noteMechanism] { noteMechanism->PickupNote();}, {noteMechanism}),

					//This line will have the robot wait for the amount of time specified.  Normally, 1 second is enough:
                    frc2::WaitCommand(1_s)
                ),

				frc2::ParallelRaceGroup(

					//this command will reset the gyro
					//Be sure to stop the robot before hand, using the instant command
					drive->ZeroOdometry({0_m, 0_m, 0_deg}),

                    frc2::WaitCommand(1_s)

                ) Last line doesn't need a comma
			)
	).ToPtr();
}
*/
void AutoFctns::setAutoRoutineValues(int position, int targetR, int targetB, std::optional<frc::DriverStation::Alliance> color){

}


frc2::CommandPtr AutoFctns::autonomousRoutine(DriveSubsystem *drive) {
	//AutoFctns::setAutoRoutineValues(AutoInfo::positionSet, AutoInfo::targetSetA, AutoInfo::colorSet);
	return frc2::SequentialCommandGroup(

		//This will reset the gyro
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
		frc2::SequentialCommandGroup(
				//6.01 meters need to be traversed
				//This will have the bot immediately stop:
				frc2::InstantCommand([drive] { drive->Drive({});}),
//once done building, drive forward 2 ft, then do this.
				/*
				frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({2_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				*/
				frc2::ParallelRaceGroup(
					//AutoFctns::setAutoRoutineValues(AutoInfo::positionSet, AutoInfo::targetSet, AutoInfo::colorSet),

					//In this case, the function is to drive, which is determined by (forwards/backwards, left/right, rotation, and orientation base):
                    frc2::RunCommand([drive] { drive->Drive({-1_fps, -5.5_fps, -20_deg_per_s, 0});}, {drive}), //podiyibr is right

					//This line will have the robot wait for the amount of time specified.  Normally, 1 second is enough:
                    frc2::WaitCommand(4_s)
                ),
				frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),

                    frc2::WaitCommand(1_s)
                )
		)
	).ToPtr();
}

/*
Determine how to find distance from limelight, in addition to angle if possible
Use a combination of the three provided values to obtain movement in x and y, rotation
Use an until statement to drive at the set values until the target april tag is seen, then use a command to drive
itowards the limelight and autoalign a scoring mechanism.
*/