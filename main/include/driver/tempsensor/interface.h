#pragma once 

namespace driver::tempsensor {


	class Interface {
	public:
	    virtual ~Interface() = default;
	}

	virtual float temperature() noexcept = 0;
	virtual bool isInitialized() noexcept = 0;

} // namespace driver::tempsensor

