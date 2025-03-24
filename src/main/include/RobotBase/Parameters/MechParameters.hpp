#ifndef _MECH_PARAMETERS_H
#define _MECH_PARAMETERS_H

#include "RobotBase/specifications/RobotSpecifications.hpp"
namespace Mechanism {
	namespace Algae{
		static constexpr int Puncher = 14;
	}
	namespace Coral{
		static constexpr int Arm = 15;
		static constexpr int Elevator = 16;
		static constexpr int LimitDown = 0;
		static constexpr int LimitUp = 1;
	}
	
}

#endif