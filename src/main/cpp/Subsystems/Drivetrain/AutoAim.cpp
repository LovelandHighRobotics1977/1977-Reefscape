#include "Headers/Headers.hpp"

double sideMove;
double distance;
double rotation;
const double distanceTarget = 0;
double sideMoveTarget = 0;
const double rotationTarget = 0;
const double errorVal = 0.01;
const double sideErrorVal = 0.05;
const double rotationErrorVal = 1;
double cTarget;
// storage variables
double forwardSpeed;
double sideSpeed;
double rotationSpeed;
/*
Obtain values like normal, do tag check, then launch side to side and forward movement
Rotation will be done at the same time as the above
Then, the robot will drive left or right depending on the button pressed
*/
void AimFunctions::determineValues() {
    sideMove =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[0];
	distance =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[2];
	rotation =  nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("targetpose_cameraspace",{})[5];
	cTarget = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tid", -1);


	if ((cTarget>=6 && cTarget<=11 )|| (cTarget>=17 && cTarget<=22)){

		if(sideMove<=sideMoveTarget-sideErrorVal){
			sideSpeed = 1.5;
		}else if (sideMove>=sideMoveTarget+sideErrorVal) {
			sideSpeed = -1.5;
		}else{
			sideSpeed =0;
		}

		if(distance>=distanceTarget+errorVal){
			forwardSpeed = 3;
        }else{
			forwardSpeed = 0;
		}
		
		
		if(rotation<=rotationTarget+rotationErrorVal){
			rotationSpeed = 0;
		} else if (rotation>=rotationTarget-rotationErrorVal) {
			rotationSpeed = 0;
		} else {
			rotationSpeed = 0;
		}
		
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

