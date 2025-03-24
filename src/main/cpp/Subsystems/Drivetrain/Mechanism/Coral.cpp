#include "subsystems/Mechanism/Coral.hpp"
units::angle::turn_t elevatorMin = 0_tr;
units::angle::turn_t elevatorMax = 100_tr;


CoralElevator::CoralElevator(): m_coralElevatorMotor{Mechanism::Coral::Elevator}{
    coralElevatorMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    coralElevatorMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    coralElevatorMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));
    m_coralElevatorMotor.GetConfigurator().Apply(coralElevatorMotorConfig);
}

CoralArm::CoralArm(): m_coralArmMotor{Mechanism::Coral::Arm}{
    coralArmMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    coralArmMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    coralArmMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));
    m_coralArmMotor.GetConfigurator().Apply(coralArmMotorConfig);
}

void CoralArm::setCoralArm(double speed){    
    m_coralArmMotor.Set(speed);   
}


void CoralElevator::setCoralElevator(double speed){    
    m_coralElevatorMotor.Set(speed);   
}

int CoralElevator::canGoUp(){
    frc::SmartDashboard::PutNumber("Also Arm Position", m_coralElevatorMotor.GetPosition().GetValueAsDouble());
    if((m_coralElevatorMotor.GetPosition().GetValue()) < elevatorMax) {
        return 1;
    } else {
        return 0;
    }
}

