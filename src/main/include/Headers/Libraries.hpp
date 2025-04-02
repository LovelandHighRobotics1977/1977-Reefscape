#pragma once

// Be wary all who enter, for beyond lies the wall of include statements

// Standard Library
#include <string>
#include <cmath>
#include <math.h>

// Robot Program Framework
#include <frc/TimedRobot.h>

// CTRE Phoenix Hardware APIs
#include <ctre/phoenix6/configs/Configs.hpp>
#include <ctre/phoenix6/configs/Configurator.hpp>
#include <ctre/phoenix6/CANcoder.hpp>
#include <ctre/phoenix6/TalonFX.hpp>

// NavX AHRS Api
#include "studica/AHRS.h" 

// FRC bus interface library
#include <frc/I2C.h>

// Hardware Interface Libraries
#include <frc/PowerDistribution.h>
#include <frc/RobotController.h>
#include <frc/DigitalInput.h>
#include <frc/RobotBase.h>
#include <frc/Encoder.h>

// Operator Input Libraries
#include <frc/MathUtil.h>
#include <frc/XboxController.h>
#include <frc/Joystick.h>
#include <frc/filter/SlewRateLimiter.h>

// Dashboard Libraries
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/Field2d.h>
#include <frc/smartdashboard/SendableChooser.h>

// Vision Libraries
#include <cameraserver/CameraServer.h>

// Kinematics Libraries
#include <frc/kinematics/SwerveModulePosition.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <frc/kinematics/ChassisSpeeds.h>

// Trajectory Libraries
#include <frc/trajectory/TrapezoidProfile.h>

// Geometry Libraries
#include <frc/geometry/Rotation2d.h>
#include <frc/geometry/Translation2d.h>
#include <frc/geometry/Translation3d.h>
#include <frc/geometry/Pose2d.h>

// FRC2 Command Libraries
#include <frc2/command/Command.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/WaitUntilCommand.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/StartEndCommand.h>
#include <frc2/command/SwerveControllerCommand.h>
#include <frc2/command/RepeatCommand.h>

// FRC2 Trigger Libraries
#include <frc2/command/button/Trigger.h>

// FRC2 Subsystem Libraries
#include <frc2/command/SubsystemBase.h>

// Units Libraries
#include <units/velocity.h>
#include <units/acceleration.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/time.h>
#include <units/length.h>
#include <units/angle.h>
#include <units/voltage.h>
#include <units/math.h>
#include <units/dimensionless.h>

// Timing and Misc Libraries
#include <frc/Timer.h>

// NetworkTables Libraries
#include <networktables/NetworkTableInstance.h>
