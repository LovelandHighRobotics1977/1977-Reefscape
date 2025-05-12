#include "subsystems/Mechanism/Coral.hpp"


Climber::Climber(): m_climberMotor{Mechanism::Coral::Climber}{
    climberMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    climberMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    climberMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));
    m_climberMotor.GetConfigurator().Apply(climberMotorConfig);
}

Elevator::Elevator() {
    elevatorLeftMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    elevatorLeftMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    elevatorLeftMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));
    
    elevatorRightMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    elevatorRightMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::Clockwise_Positive);
    elevatorRightMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));
    
    elevatorEncoderConfig.MagnetSensor.WithAbsoluteSensorDiscontinuityPoint(units::angle::turn_t(1)); // implicit typing turns the 2 into an angle value
    elevatorEncoderConfig.MagnetSensor.WithSensorDirection(ctre::phoenix6::signals::SensorDirectionValue::Clockwise_Positive);
    
    m_elevatorEncoder.GetConfigurator().Apply(elevatorEncoderConfig);

    elevatorLeftMotorConfig.Feedback.WithRemoteCANcoder(m_elevatorEncoder);
    elevatorRightMotorConfig.Feedback.WithRemoteCANcoder(m_elevatorEncoder);
    
    m_elevatorLeft.GetConfigurator().Apply(elevatorLeftMotorConfig);
    m_elevatorRight.GetConfigurator().Apply(elevatorRightMotorConfig);
    

}

void Climber::setClimber(double speed){
    m_climberMotor.Set(speed);
}


void Elevator::setElevatorTarget(units::angle::turn_t goal){
    
    m_elevatorLeft.SetPosition(m_elevatorEncoder.GetAbsolutePosition().GetValue());
    m_elevatorRight.SetPosition(m_elevatorEncoder.GetAbsolutePosition().GetValue());

    
    ctre::phoenix6::controls::PositionDutyCycle Cycle(goal);
    m_elevatorLeft.SetControl(Cycle.WithPosition(goal));
    m_elevatorRight.SetControl(Cycle.WithPosition(goal));
    

   /* m_elevatorLeft.Set(goal);
    m_elevatorRight.Set(goal);*/
}

    





