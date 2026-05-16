#pragma once

#include <memory>
#include <cstdint>

namespace driver {
    namespace gpio { class Interface; }
    namespace adc { class Interface; }
    namespace serial { class Interface; }
    namespace timer { class Interface; }
    namespace tempsensor { class Interface; }
}


namespace driver::factory {
	
class Interface {
public:
    
    virtual ~Interface() noexcept = default;
    virtual std::unique_ptr<gpio::Interface> gpio(std::uint8_t pin) noexcept = 0;
    virtual std::unique_ptr<adc::Interface> adc() noexcept = 0;
    virtual std::unique_ptr<serial::Interface> serial() noexcept = 0;
    virtual std::unique_ptr<timer::Interface> timer() noexcept = 0;
    virtual std::unique_ptr<tempsensor::Interface> tempsensor(std::uint8_t pin, adc::Interface& adc) noexcept = 0;

	// NO COPY MOVE 
    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;
    Interface(Interface&&) = delete;
    interface& operator=(interface&&) = delete;



};

} // namespace driver::factory



