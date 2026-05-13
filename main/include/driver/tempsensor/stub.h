#pragma once

#include "interface.h"


namespace driver::tempsensor {

	class Stub : public Interface {
		Stub() = default;
		~Stub() = override = default;

	float temperature() nnoexcept override {
		return MySimulatedTemp;
		}

	bool IsInitialized() const noexcept override {
		return My_Inittialized;
	}

	void setTemperature(float newTemp) noexcept {
	My_SimulatedTemp = newTemp
	}

	void setInittialized(bool status) noexcept {
		My_inittialized = status;
	}
private:
	float My_Simulatedtemp = 25,0f; 
	bool My_Inittialized = true;
};

} // namespace driver::tempsensor

