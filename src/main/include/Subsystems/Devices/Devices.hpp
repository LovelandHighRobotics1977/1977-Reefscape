#pragma once

// seems useless, delete later
class Field2d {
	private:
		inline static Field2d* instance{nullptr};
		Field2d() = default;
		~Field2d() = default;
		
	public:
		Field2d(const Field2d&) = delete;
		Field2d& operator=(const Field2d&) = delete;

		static Field2d* GetInstance(){
			if ( !instance ){
				instance = new Field2d();
			}
			return instance;
		}

		frc::Field2d m_field;
};

// creates the Gyro board in code and allows to reset the gyro
class Gyro {
	private:
		inline static Gyro* instance{nullptr};
		Gyro() = default;
		~Gyro() = default;
	
	public:
	Gyro(const Gyro&) = delete;
	Gyro& operator=(const Gyro&) = delete;

	static Gyro* GetInstance(){
		if ( !instance ){
			instance = new Gyro();
		}
		return instance;
	}

	//AHRS ahrs{frc::I2C::Port::kMXP};
	studica::AHRS ahrs{studica::AHRS::NavXComType::kMXP_SPI};

};

// sets current limits
class PDH {
	private:
		inline static PDH* instance{nullptr};
		PDH() = default;
		~PDH() = default;
	
	public:
	PDH(const PDH&) = delete;
	PDH& operator=(const PDH&) = delete;

	static PDH* GetInstance(){
		if ( !instance ){
			instance = new PDH();
		}
		return instance;
	}

	frc::PowerDistribution m_PDH{1, frc::PowerDistribution::ModuleType::kRev};

	double CanWarnings(){
		return m_PDH.GetFaults().CanWarning;
	}
	double Brownouts(){
		return m_PDH.GetFaults().Brownout;
	}
	double GetCurrent(int channel){
		return m_PDH.GetCurrent(channel);
	}
};