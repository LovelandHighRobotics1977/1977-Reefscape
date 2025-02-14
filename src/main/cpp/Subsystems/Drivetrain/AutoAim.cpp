#include "Subsystems/Drivetrain/AutoAim.hpp"
#include "Headers/Headers.hpp"

double sideMove;
double distance;
double rotation;
const double distanceTarget = 0.02;
const double sideMoveTarget = 0.02;
const double rotationTarget = 0.8;
const double errorVal = 0.1;
double cTarget;
// storage variables
double fowardSpeed;
double sideSpeed;
double rotationSpeed;

void AimFunctions::determineValues() {
    sideMove =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[0];
	distance =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[1];
	rotation =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[5];
	cTarget = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tid", -1);
	
	if ((cTarget>=7 && cTarget<=11 )|| (cTarget>=17 && cTarget<=22)){
		if(sideMove<=sideMoveTarget+errorVal){
			sideSpeed = .3;
		}else if (sideMove>=sideMoveTarget-errorVal) {
			sideSpeed = -.3;
		}
		if(distance<=distanceTarget+errorVal){
			fowardSpeed = .3;
        }
		if(rotation<=rotationTarget+errorVal){
			rotationSpeed = .1;
		} else if (rotation>=rotationTarget-errorVal) {
			rotationSpeed = -.1;
		}
    }
}

double AimFunctions::getForwardSpeed() {
    return fowardSpeed;
}

double AimFunctions::getSideSpeed() {
    return sideSpeed;
}

double AimFunctions::getRotationSpeed() {
    return rotationSpeed;
}