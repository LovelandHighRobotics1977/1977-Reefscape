#include "subsystems/Mechanism/Coral.hpp"

// sets the motor configurations
CoralIntake::CoralIntake() : m_coralIntakeMotor{Mechanism::Coral::Intake}{
    coralIntakeMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Coast); // base motor state
    coralIntakeMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive); // motor direction
    coralIntakeMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20)); // supply limit
    m_coralIntakeMotor.GetConfigurator().Apply(coralIntakeMotorConfig); // applies configurations
}

void CoralIntake::setCoralIntake(double speed){
    m_coralIntakeMotor.Set(speed); // sets speed to speed %
}
