#include "subsystems/Mechanism/Algae.hpp"

AlgaePunch::AlgaePunch() : m_algaePunchMotor{Mechanism::Algae::Puncher}{
    algaePunchMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    algaePunchMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    algaePunchMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));
    m_algaePunchMotor.GetConfigurator().Apply(algaePunchMotorConfig);
}

void AlgaePunch::setAlgaePunch(double speed){
    m_algaePunchMotor.Set(speed);
}