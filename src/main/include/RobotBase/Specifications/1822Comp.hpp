#pragma once

#include "Headers/Libraries.hpp"
#include "Headers/Util.hpp"

/**
 * Drivetrain specifications belonging to the Generic bot using Falcon 500s
*/
namespace Drivetrain {
	namespace Measurements {
		// robot frame size
		namespace Frame {
			static constexpr auto width = 30_in;
			static constexpr auto length = 30_in;
		}
		// gyroscope position based on center offset
		namespace Gyroscope {
			static constexpr auto xPosition = 10_in;
			static constexpr auto yPosition = 5_in;
		}
		// wheel size
		namespace Wheel {
			static constexpr auto radius = 2_in;
			static constexpr auto offset = 2.625_in;
			static constexpr auto circumference = (2 * radius) * M_PI;
		}
		// obtains amount needed to spin in a circle?
		namespace Circle {
			static const auto Radius = units::inch_t{std::hypot(((Frame::length/2)-Wheel::offset).value(), ((Frame::length/2)-Wheel::offset).value())};
			static const auto Circumference = units::foot_t{(2 * Radius) * M_PI};
		}
	}
	namespace Module {
		namespace Motor {
			// sets up drive motor values
			namespace Drive {
				static constexpr double max_rpm = 6000;
				static constexpr double gear_ratio = 6.75;
				static constexpr double encoder_cpr = 2048;
				static constexpr double output_rps = ( ( max_rpm / 60 ) / gear_ratio);
				static const auto distance_per_pulse = ((Measurements::Wheel::circumference) / (gear_ratio * encoder_cpr));
				static const auto distance_per_rotation = units::meter_t{distance_per_pulse * encoder_cpr};
				namespace PID {
					static constexpr double S = 0;
					static constexpr double V = 0;
					static constexpr double A = 0;
					static constexpr double P = 0;
					static constexpr double I = 0;
					static constexpr double D = 0;
				}
			}
			// sets up angle motor values
			namespace Angle {
				static constexpr double max_rpm = 6000;
				static constexpr double gear_ratio = 150/7;
				static constexpr double encoder_cpr = 4096;
				static constexpr double output_rps = ( ( max_rpm / 60 ) / gear_ratio);
				static constexpr auto distance_per_pulse = units::radian_t{((2 * M_PI) / (encoder_cpr))};
				static const auto distance_per_rotation = units::degree_t{distance_per_pulse * encoder_cpr};
				namespace PID {
					static constexpr double S = 0;
					static constexpr double V = 0;
					static constexpr double A = 0;
					static constexpr double P = 8;
					static constexpr double I = 0;
					static constexpr double D = 0;
				}
			}
		}
		// sets up the different ID's for each drive motor
		namespace Front { 
			namespace Left {
				static constexpr int Drive = 8; 
				static constexpr int Angle = 9; 
				static constexpr int Encoder = 10; 
				static constexpr units::turn_t MagnetOffset = 0.537354_tr;
				static const frc::Translation2d Location = {
					( + (((Measurements::Frame::length)/2) - Measurements::Wheel::offset)) - Measurements::Gyroscope::xPosition,
					( + (((Measurements::Frame::width)/2) - Measurements::Wheel::offset)) - Measurements::Gyroscope::yPosition
				};
			}
			namespace Right {
				static constexpr int Drive = 11; //11
				static constexpr int Angle = 12; 
				static constexpr int Encoder = 13; //10
				static constexpr units::turn_t MagnetOffset = 0.413086_tr; //0.434082
				static const frc::Translation2d Location = {
					( + (((Measurements::Frame::length)/2) - Measurements::Wheel::offset)) - Measurements::Gyroscope::xPosition,
					( - (((Measurements::Frame::width)/2) + Measurements::Wheel::offset)) - Measurements::Gyroscope::yPosition
				};
			}
		}
		namespace Rear {
			namespace Left {
				static constexpr int Drive = 2; //11
				static constexpr int Angle = 3; //12
				static constexpr int Encoder = 4; //13 
				static constexpr units::turn_t MagnetOffset = 0.434082_tr; //0.413086
				static const frc::Translation2d Location = {
					( - (((Measurements::Frame::length)/2) + Measurements::Wheel::offset)) - Measurements::Gyroscope::xPosition,
					( + (((Measurements::Frame::width)/2) - Measurements::Wheel::offset)) - Measurements::Gyroscope::yPosition
				};
			}
			namespace Right {
				static constexpr int Drive = 5;  //2, 
				static constexpr int Angle = 6; //3
				static constexpr int Encoder = 7; //4
				static constexpr units::turn_t MagnetOffset = 0.299805_tr; //0.434082
				static const frc::Translation2d Location = {
					( - (((Measurements::Frame::length)/2) + Measurements::Wheel::offset)) - Measurements::Gyroscope::xPosition,
					( - (((Measurements::Frame::width)/2) + Measurements::Wheel::offset)) - Measurements::Gyroscope::yPosition
				};
			}
		}
	} 
	namespace Movement {
		// sets maxinum movement speeds
		namespace Maximum {
			namespace Linear {
				// ~ 16 feet per second
				static const auto Velocity = ( units::foot_t{ Measurements::Wheel::circumference } * Module::Motor::Drive::output_rps ) / 1_s;
				static const auto Acceleration = Velocity / 1_s;
			}
			namespace Angular {
				// ~ 773 degrees per second
				static const auto Velocity = units::degrees_per_second_t{( 360 * ( Linear::Velocity.value() / Measurements::Circle::Circumference.value() ) )};
				static const auto Acceleration = Velocity / 1_s;
			}
		}
		// sets up different rotation values
		namespace Rotate {
			namespace Preset {
				static const units::degrees_per_second_t None = 0_deg_per_s;  						//  0 degrees per second
				static const units::degrees_per_second_t Slow =  Maximum::Angular::Velocity / 3;	//  260 degrees per second
				static const units::degrees_per_second_t Medium = Maximum::Angular::Velocity / 2;	//  370 degrees per second
				static const units::degrees_per_second_t Fast = Maximum::Angular::Velocity;  		//  770 degrees per second
			}
			namespace Around {
				static constexpr frc::Translation2d Center = { - Measurements::Gyroscope::xPosition , - Measurements::Gyroscope::yPosition };   						//  position of the center of the robot
			}
		}
	}
}

