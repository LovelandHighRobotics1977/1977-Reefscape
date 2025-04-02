#include "subsystems/Mechanism/Algae.hpp"

// sets up the motor parameters
AlgaeIntake::AlgaeIntake() : m_algaeIntakeMotor{Mechanism::Algae::Intake}{
    algaeIntakeMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Coast); // sets base state
    algaeIntakeMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive); // sets the motor direction
    algaeIntakeMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20)); // sets current limit
    m_algaeIntakeMotor.GetConfigurator().Apply(algaeIntakeMotorConfig); // applies the configuration
}

AlgaeWinch::AlgaeWinch() : m_winch{Mechanism::Algae::Angle::Winch}{
    winchMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    winchMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    m_winch.GetConfigurator().Apply(winchMotorConfig);
}

AlgaePuncher::AlgaePuncher() : m_puncher{Mechanism::Algae::Puncher::Puncher}{
    puncherMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    puncherMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    puncherMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));
    m_puncher.GetConfigurator().Apply(puncherMotorConfig);
}

void AlgaeIntake::setAlgaeIntake(double speed){
    m_algaeIntakeMotor.Set(speed); // makes the motor spin at speed % when ran
}

void AlgaeWinch::winchArmMove(double speed){
    m_winch.Set(speed);
}

void AlgaePuncher::algaePuncherPunch(double speed){
    m_puncher.Set(speed);
}