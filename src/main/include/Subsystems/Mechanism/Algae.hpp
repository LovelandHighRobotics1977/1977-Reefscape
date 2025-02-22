#ifndef _ALGAE_MECHANISM_H
#define _ALGAE_MECHANISM_H

#include "headers/Headers.hpp"

class AlgaePunch : public frc2::SubsystemBase {
	public:
	
		AlgaePunch();

		void setAlgaePunch(double speed);

        

	private:

		ctre::phoenix6::hardware::TalonFX m_algaePunchMotor;
	    ctre::phoenix6::configs::TalonFXConfiguration algaePunchMotorConfig{};

       
};

#endif