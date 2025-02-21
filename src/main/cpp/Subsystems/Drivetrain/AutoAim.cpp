#include "Subsystems/Drivetrain/AutoAim.hpp"
#include "Headers/Headers.hpp"

double sideMove;
double distance;
double rotation;
const double distanceTarget = 0;
double sideMoveTarget = 0.15;
const double rotationTarget = 7.0;
const double errorVal = 0.01;
const double sideErrorVal = 0.03;
const double rotationErrorVal = 5.0;
double cTarget;
// storage variables
double forwardSpeed;
double sideSpeed;
double rotationSpeed;

void AimFunctions::determineValues(bool left) {
    sideMove =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[0];
	distance =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[1];
	rotation =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[5];
	cTarget = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tid", -1);
	if(left){
		sideMoveTarget = 0.19;
	}else{
		sideMoveTarget = -0.19;
	}

	if ((cTarget>=7 && cTarget<=11 )|| (cTarget>=17 && cTarget<=22)){
		if(sideMove<=sideMoveTarget-sideErrorVal){
			sideSpeed = .05;
		}else if (sideMove>=sideMoveTarget+sideErrorVal) {
			sideSpeed = -.05;
		}else{
			sideSpeed = 0;
		}

		if(distance<=distanceTarget+errorVal){
			forwardSpeed = .1;
        }else{
			forwardSpeed = 0;
		}
		/*
		if(rotation<=rotationTarget+rotationErrorVal){
			rotationSpeed = .01;
		} else if (rotation>=rotationTarget-rotationErrorVal) {
			rotationSpeed = -.01;
		}
		*/
		
	}else{
		rotationSpeed = 0;
		sideSpeed = 0;
		forwardSpeed = 0;
	}
}

double AimFunctions::getForwardSpeed() {
    return forwardSpeed;
}

double AimFunctions::getSideSpeed() {
    return sideSpeed;
}

double AimFunctions::getRotationSpeed() {
    return rotationSpeed;
}