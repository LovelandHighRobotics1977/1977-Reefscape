#ifndef _MECH_PARAMETERS_H
#define _MECH_PARAMETERS_H

#include "RobotBase/specifications/RobotSpecifications.hpp"
namespace Mechanism {
	namespace Algae{
		static constexpr int Intake = 14;
		namespace Angle{
			static constexpr int Winch = 15;
			static constexpr int LimitUp = 1;
		}
		namespace Puncher{
			static constexpr int Puncher = 17;
		}
	}
	namespace Coral{
		static constexpr int Intake = 16;
	}
	
}

#endif