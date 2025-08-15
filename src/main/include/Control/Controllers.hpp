#ifndef _CONTROLLERS_H
#define _CONTROLLERS_H

#include "Headers/Libraries.hpp"

#include "RobotBase/Specifications/RobotSpecifications.hpp"
#include "Subsystems/Drivetrain/AutoAim.hpp"

class Driver : public frc2::SubsystemBase {
	public:

		Driver(const int port):m_Joystick{port}{};

		bool field_relative;

		bool gyro_reset;

		bool trigger_one;
		bool trigger_two;

		bool coast_mode_toggle;

		bool targetNearestAprilTag;

		double throttle;

		double forward;
		double strafe;  
		double rotate;

		bool leftCoral;
		bool rightCoral;


		/**
		 * Update the controller variables 
		 * @attention Each control scheme is defined in this function
		 * @note Automaically chooses the control scheme based on the joystick name
		*/
		void update(){

			// Control Scheme Definitions
			if(m_Joystick.GetName() == std::string{"X52 H.O.T.A.S."}){
				//field_relative = !m_Joystick.GetRawButton(6); // 6 is not working
				field_relative = !m_Joystick.GetRawButton(15);

				gyro_reset = m_Joystick.GetRawButton(2);
				//4 is left, 3 is right
				leftCoral = m_Joystick.GetRawButton(4);
				rightCoral = m_Joystick.GetRawButton(3);

				//trigger_one = m_Joystick.GetRawButton(1);
				//trigger_two = m_Joystick.GetRawButton(15);

				coast_mode_toggle = m_Joystick.GetRawButton(5);

				throttle = (-m_Joystick.GetZ() + 1) / 2;
				if(!targetNearestAprilTag){
					forward = m_Joystick.GetY();
					strafe = m_Joystick.GetX();
					rotate = m_Joystick.GetRawAxis(5);
				}


				targetNearestAprilTag = m_Joystick.GetRawButton(4);
			}

			if(m_Joystick.GetName() == std::string{"Extreme 3D pro"}){
				field_relative = !m_Joystick.GetRawButton(2);

				gyro_reset = m_Joystick.GetRawButton(3);

				trigger_one = m_Joystick.GetRawButton(1);

				coast_mode_toggle = m_Joystick.GetRawButton(5);

				throttle = (-m_Joystick.GetThrottle() + 1) / 2;

				forward = m_Joystick.GetY();
				strafe = m_Joystick.GetX();
				rotate = m_Joystick.GetTwist();

				rightCoral = m_Joystick.GetRawButton(6);
				leftCoral = m_Joystick.GetRawButton(4);

			}


			
			
			// Controller values and optimizations
			forward = (-m_forwardLimiter.Calculate(frc::ApplyDeadband(forward, forward_deadzone)) * throttle);
			strafe = (-m_strafeLimiter.Calculate(frc::ApplyDeadband(strafe, strafe_deadzone)) * throttle);
			
			if(trigger_one && !trigger_two){
				rotate = 0.75 * (-m_rotateLimiter.Calculate(frc::ApplyDeadband(rotate, rotate_deadzone)) * sqrt(throttle));
			}else if(trigger_one && trigger_two){
				rotate = (-m_rotateLimiter.Calculate(frc::ApplyDeadband(rotate, rotate_deadzone)) * sqrt(throttle));
			}else{
				rotate = 0.4 * (-m_rotateLimiter.Calculate(frc::ApplyDeadband(rotate, rotate_deadzone)) * sqrt(throttle));
			}
			
		}

		private:
			frc::Joystick m_Joystick;

			frc::SlewRateLimiter<units::dimensionless::scalar> m_forwardLimiter{3 / 1_ms};
			frc::SlewRateLimiter<units::dimensionless::scalar> m_strafeLimiter{3 / 1_ms};
			frc::SlewRateLimiter<units::dimensionless::scalar> m_rotateLimiter{3 / 1_ms};

			double forward_deadzone = 0.1;
			double strafe_deadzone  = 0.25;
			double rotate_deadzone  = 0.1;
	};

class Operator : public frc2::SubsystemBase {
	public:

		Operator(const int port):m_XboxController{port}{};

		bool elevatorUp;
		bool elevatorDown;
		bool punchUp;
		bool punchDown;
		bool armUp;
		bool armDown;
		bool climberUp;
		bool climberDown;
		bool elevatorLow;
		bool elevatorMid;
		bool elevatorHigh;
		void update(){
		

			elevatorLow = m_XboxController.GetAButton();
			elevatorMid = m_XboxController.GetXButton();
			elevatorHigh = m_XboxController.GetYButton();

			climberUp = m_XboxController.GetRawButton(7);
			climberDown = m_XboxController.GetRawButton(8);


		}

		
	private:
		frc::XboxController m_XboxController;
};

#endif // _CONTROLLERS_H