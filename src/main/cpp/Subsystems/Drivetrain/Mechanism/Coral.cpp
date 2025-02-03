#include "subsystems/Mechanism/Coral.hpp"

CoralIntake::CoralIntake() : m_coralIntakeMotor{Mechanism::Coral::Intake}{
    coralIntakeMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Coast);
    coralIntakeMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    coralIntakeMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));
    m_coralIntakeMotor.GetConfigurator().Apply(coralIntakeMotorConfig);
}

void CoralIntake::setCoralIntake(double speed){
    m_coralIntakeMotor.Set(speed);
}
