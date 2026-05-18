#pragma once

#include <memory>
#include <cstdint>

namespace driver {
    namespace gpio {
	    class Interface;
	    enum class Direction : std::uint8_t; // matchar Anthons enum klass namn
    }

    namespace adc { class Interface; }
    namespace serial { class Interface; }
    namespace timer { class Interface; }
    namespace tempsensor { class Interface; }
}


namespace driver::factory {

/**
 * @brief Abstract Factory interface for creating drivers.
 * */
	
class Interface {

protected: 

	/**
	 * @brief Protected constructor to allow inheritance but prevent creating objects directly.
	 * */
	Interface() noexcept = default;

public:
    /** 
     * @brief Virtual Destructor.
     */
    
    virtual ~Interface() noexcept = default;

    /**
     * @brief Create a GPIO driver instance.
     * * @param[in] pin the GPIO pin number.
     * @param[in] direction The data direction (Input, InputPullup, Output).
     * @return A smart pointer to the created GPIO interface
     */

    virtual std::unique_ptr<gpio::Interface> gpio(std::uint8_t pin, gpio::Direction direction) noexcept = 0;

    /**
     * @brief Create an ADC driver instance.
     * * @return A smart pointer to the created ADC interface.
     */

    virtual std::unique_ptr<adc::Interface> adc() noexcept = 0;

    /**
     * @brief Create a Serial (UART) driver instance.
     * * @return A smart pointer to the created Serial interface.
     *
     * */


    virtual std::unique_ptr<serial::Interface> serial() noexcept = 0;

    /** 
     * @brief Create a Timer driver instance.
     * * @return A smart pointer to the createdd Timer interface.
     */


    virtual std::unique_ptr<timer::Interface> timer() noexcept = 0;

    /**
     * @brief Create a Temperature driver instance.
     * * @param[in] pin the Pin number where the TMP36 sensor is connected.
     * @param [in] adc A refrence to the adc instance used for reading voltage (Dependency Injection).
     * @return A smart pointer to the created Temperature sensor interface.
     * */


    virtual std::unique_ptr<tempsensor::Interface> tempsensor(std::uint8_t pin, adc::Interface& adc) noexcept = 0;



	// NO COPY MOVE 
    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;
    Interface(Interface&&) = delete;
    Interface& operator=(Interface&&) = delete;

};

} // namespace driver::factory



