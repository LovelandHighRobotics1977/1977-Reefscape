#include "subsystems/Mechanism/Coral.hpp"

// fix later
#include <functional>
#include <frc2/command/Commands.h>
#include <frc/Encoder.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <units/angle.h>
#include <units/angular_velocity.h>


Climber::Climber(): m_climberMotor{Mechanism::Coral::Climber}{
    climberMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    climberMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    climberMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));
    m_climberMotor.GetConfigurator().Apply(climberMotorConfig);
}

Elevator::Elevator() {
    motorPID.SetTolerance(0);

    m_elevatorEncoder.SetDistancePerPulse(4.0 / 256.0);
    m_elevatorEncoder.SetDistancePerPulse(4.0 / 256);

    elevatorLeftMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    elevatorLeftMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    elevatorLeftMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));

    elevatorRightMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    elevatorRightMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::Clockwise_Positive);
    elevatorRightMotorConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));
    
    elevatorEncoderConfig.MagnetSensor.WithAbsoluteSensorDiscontinuityPoint(units::angle::turn_t(1)); // implicit typing turns the 2 into an angle value
    elevatorEncoderConfig.MagnetSensor.WithSensorDirection(ctre::phoenix6::signals::SensorDirectionValue::Clockwise_Positive);
    
   /* m_elevatorEncoder.GetConfigurator().Apply(elevatorEncoderConfig);
    elevatorLeftMotorConfig.Feedback.WithRemoteCANcoder(m_elevatorEncoder);
    elevatorRightMotorConfig.Feedback.WithRemoteCANcoder(m_elevatorEncoder); */

    
    
    m_elevatorLeft.GetConfigurator().Apply(elevatorLeftMotorConfig);
    m_elevatorRight.GetConfigurator().Apply(elevatorRightMotorConfig);
    

}

void Climber::setClimber(double speed){
    m_climberMotor.Set(speed);
}

coralArm::coralArm(){
    coralArmAngleConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    coralArmAngleConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::Clockwise_Positive);
    coralArmAngleConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));

    coralArmIntakeConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    coralArmIntakeConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    coralArmIntakeConfig.CurrentLimits.WithSupplyCurrentLimit(static_cast<units::current::ampere_t>(20));

    m_coralArmAngle.GetConfigurator().Apply(coralArmAngleConfig);
    m_coralArmIntake.GetConfigurator().Apply(coralArmIntakeConfig);
}

void coralArm::setCoralAngle(double speed){
    m_coralArmAngle.Set(speed);
}

void coralArm::setCoralIntake(double speed){
    m_coralArmIntake.Set(speed);
}




void Elevator::setElevatorTarget(double goal){
    
    //m_elevatorLeft.SetPosition(m_elevatorEncoder.GetAbsolutePosition().GetValue());
    //m_elevatorRight.SetPosition(m_elevatorEncoder.GetAbsolutePosition().GetValue());
   

    //m_elevatorEncoder.kP = Drivetrain::Module::Motor::Drive::PID::P;
    //ctre::phoenix6::controls::PositionVoltage m_position{0_tr};
   
    //m_elevatorLeft.SetControl(m_position.WithPosition(goal));
    //m_elevatorRight.SetControl(m_position.WithPosition(goal));
   
    //m_elevatorRight.Set(Elevator::motorPID.Calculate(elevatorPos, goal));
    //m_elevatorLeft.Set(Elevator::motorPID.Calculate(elevatorPos, goal));
    /*
    m_elevatorRight.SetVoltage(
        static_cast<units::volt_t>(m_feedforward.Calculate(goal)) +
        units::volt_t(motorPID.Calculate (
            m_elevatorEncoder.GetRate())));
    */
    m_elevatorRight.Set(m_feedforward.Calculate(m_elevatorEncoder.GetDistance(), goal));
    //Code to use if we can get any current options to work. Blueprint to hard code it 

    // double elevatorPos = m_elevatorEncoder.GetPosition().GetValueAsDouble();
    /*if(m_elevatorEncoder.GetPosition().GetValue() != goal){
        if (m_elevatorEncoder.GetPosition().GetValue() > goal) {
            disEncoder = m_elevatorEncoder.GetPosition().GetValueAsDouble() - goal;
            isAbove=true;
        } else {
            disEncoder = goal - m_elevatorEncoder.GetPosition().GetValueAsDouble();
            isAbove=false;
        }
        //find the amount of distance that the elevator moters move together in .2 seconds at .3 speed
        //in terms of the encoders position 
        double distanceOverTime = disEncoder/0;
        if(isAbove==true){
            frc2::ParallelRaceGroup(
                
                    
                
            );
        } else {

        }
    } */
}

    





