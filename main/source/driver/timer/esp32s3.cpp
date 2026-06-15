//! @note Missing file header.

//! @note Include <cstdint>

#include "esp_attr.h" // IRAM_ATTR
#include "driver/timer/esp32s3.h"

namespace driver::timer 
{
//! @note Very nice work adding these constants here.
//!       Please place them in an anonymous namespace for static (internal) linkage.
//!       Then they will only be accesible withing this file.
constexpr std::uint32_t TimerResolutionHz{1'000'000U};
constexpr std::uint32_t MsToUs{1000U};

// -----------------------------------------------------------------------------
Esp32s3::Esp32s3() noexcept
    : handle{nullptr}
    , timeout_flag{false}
    , my_initialized{false} 
{    
    //! @note Initialize with {} instead of = {}.
    //!       Also used camelCase => timerConfig.
    gptimer_config_t timer_config = {};

    timer_config.clk_src = GPTIMER_CLK_SRC_DEFAULT;
    timer_config.direction = GPTIMER_COUNT_UP;
    timer_config.resolution_hz = TimerResolutionHz; // 1 tick = 1us

    // Initialize timer hardware
    //! @note Yoda (ESP_OK == gptimer_new_timer(&timer_config, &handle)).
    if (gptimer_new_timer(&timer_config, &handle) == ESP_OK) 
    {
        //! @note Remove =.
        gptimer_event_callbacks_t cbs = {};
        cbs.on_alarm = timer_callback;
        gptimer_register_event_callbacks(handle, &cbs, this);
        gptimer_enable(handle);
        my_initialized = true; 
    }
}

// -----------------------------------------------------------------------------
Esp32s3::~Esp32s3() noexcept 
{
    //! @note Great addition with the nullptr, but use Yoda notation, please. :)
    if (handle != nullptr) 
    {
        gptimer_stop(handle);
        gptimer_disable(handle);
        gptimer_del_timer(handle);
    }
}

// -----------------------------------------------------------------------------
void Esp32s3::setPeriod(std::uint32_t period_ms) noexcept 
{
    //! @note Yoda notation and parenthesis (0U == period_ms).
    if (!my_initialized || period_ms == 0U) { return; } 

    //! @note Initialize with {} and name the variable alarmConfig.
    gptimer_alarm_config_t alarm_config = {};
    alarm_config.alarm_count = period_ms * MsToUs; // Convert ms to us
    alarm_config.flags.auto_reload_on_alarm = true;
    gptimer_set_alarm_action(handle, &alarm_config);
}

// -----------------------------------------------------------------------------
void Esp32s3::start() noexcept 
{
    if (my_initialized) { gptimer_start(handle); }
}

// -----------------------------------------------------------------------------
void Esp32s3::stop() noexcept 
{
    if (my_initialized) { gptimer_stop(handle); }
}

// -----------------------------------------------------------------------------
bool Esp32s3::isTimeout() noexcept 
{
    // Check if ISR hasn set the flag, then reset it.
    if (timeout_flag) 
    {
        timeout_flag = false; 
        return true;
    }
    return false;
}

// -----------------------------------------------------------------------------
bool Esp32s3::isInitialized() const noexcept { return my_initialized; }

// -----------------------------------------------------------------------------
bool IRAM_ATTR Esp32s3::timer_callback(gptimer_handle_t timer, 
                                       const gptimer_alarm_event_data_t *edata, void *user_data) 
{
    // Cast void pointer back to our object instance.
    auto* instance = static_cast<Esp32s3*>(user_data);

    //! @note Good work with the casting. However, I would ensure that instance is not nullptr.
    //!       This is good praxis, since a pointer to anything can be passed to this method.
    instance->timeout_flag = true;
    return false;
}
} // namespace driver::timer
