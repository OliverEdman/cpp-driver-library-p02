#pragma once

#include "driver/timer/interface.h"
#include "driver/gptimer.h" // ESP-IDF GPTimer
#include "esp_log.h"

namespace driver::timer
{

class Esp32s3 final : public Interface
{
public:
    Esp32s3();
    ~Esp32s3() noexcept override;

    // Interface-implementationer
    bool isInitialized() const noexcept override;
    std::uint32_t timeout_ms() const noexcept override;
    void setPeriod(std::uint32_t period_ms) noexcept override;
    void start() noexcept override;
    void stop() noexcept override;
    bool isRunning() const noexcept override;
    void toggle() noexcept override;
    bool isTimeout() noexcept override;


private:
    // Hjälpmetod för att sätta upp hårdvaran
    void timer_init(); 
    
    
    gptimer_handle_t m_timer_handle{nullptr};

    // Tillståndsvariabler
    bool m_is_initialized{false};
    bool m_is_running{false};
    std::uint32_t m_period_ms{0};
    
    
  
    volatile bool m_is_timeout_triggered{false};

    static bool IRAM_ATTR timer_callback(gptimer_handle_t timer,const gptimer_alarm_event_data_t *edata,void *user_ctx);
   
    static constexpr const char* TAG = "TimerEsp32s3";
    
};

} // namespace driver::timer
