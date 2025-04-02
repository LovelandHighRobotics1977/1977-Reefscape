#pragma once


namespace AutonomousMode {
    namespace Parameter {
		namespace Linear {
			static const auto Velocity = Drivetrain::Movement::Maximum::Linear::Velocity / 5; // sets max linear velocity to 1/5th normal value
		}
	}
}

namespace Mechanism { // sets all of the mechanism motor IDs based on phoenix CAN IDs
	namespace Algae{
		static constexpr int Intake = 14;
		namespace Angle{
			static constexpr int Winch = 15;
			static constexpr int LimitUp = 1; // sets a limit switch for slot #1
		}
		namespace Puncher{
			static constexpr int Puncher = 17;
		}
	}
	namespace Coral{
		static constexpr int Intake = 16;
	}
}

namespace TeleoperatedMode {
	namespace Parameter {
		namespace Linear {
			// Max horizontal velocity of ~16 feet per second
			static const auto Velocity = Drivetrain::Movement::Maximum::Linear::Velocity;
		}
	}
	namespace Controller {
		namespace Ports {
			static constexpr int Driver = 0;
			static constexpr int Operator = 1;
		}
	}
}

