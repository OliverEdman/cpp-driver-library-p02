#include "driver/timer/esp32s3.h"
#include "esp_attr.h"

namespace driver::timer {



Esp32s3::Esp32s3() {
    timer_init();
}

Esp32s3::~Esp32s3() noexcept {
    if (my_timer_handle) {
        gptimer_stop(my_timer_handle);
        gptimer_disable(my_timer_handle);
        gptimer_del_timer(my_timer_handle);
    }
}

void Esp32s3::timer_init() {

	gptimer_config_t timer_config = {};
	
	timer_config.clk_src = GPTIMER_CLK_SRC_DEFAULT;
	timer_config.direction = GPTIMER_COUNT_UP;
	timer_config.resolution_hz = 1000000;

	ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &my_timer_handle));
        

    if (gptimer_new_timer(&timer_config, &my_timer_handle) == ESP_OK) {
        gptimer_event_callbacks_t cbs = {
            .on_alarm = timer_callback,
        };


        gptimer_register_event_callbacks(my_timer_handle, &cbs, this);
        gptimer_enable(my_timer_handle);
        my_is_initialized = true;
    }
}

bool Esp32s3::isInitialized() const noexcept {
    return my_is_initialized;
}

std::uint32_t Esp32s3::timeout_ms() const noexcept {
    return my_period_ms;
}

void Esp32s3::setPeriod(std::uint32_t period_ms) noexcept {
    my_period_ms = period_ms;
    
    gptimer_alarm_config_t alarm_config = {
        .alarm_count = static_cast<uint64_t>(period_ms) * 1000, // Convert ms to microseconds
        .reload_count = 0,
        .flags = { .auto_reload_on_alarm = true }
    };

    gptimer_set_alarm_action(my_timer_handle, &alarm_config);
}

void Esp32s3::start() noexcept {
    if (my_timer_handle && !my_is_running) {
        if (gptimer_start(my_timer_handle) == ESP_OK) {
            my_is_running = true;
        }
    }
}

void Esp32s3::stop() noexcept {
    if (my_timer_handle && my_is_running) {
        if (gptimer_stop(my_timer_handle) == ESP_OK) {
            my_is_running = false;
        }
    }
}

bool Esp32s3::isRunning() const noexcept {
    return my_is_running;
}

void Esp32s3::toggle() noexcept {
    if (my_is_running) {
        stop();
    } else {
        start();
    }
}

bool Esp32s3::isTimeout() noexcept {
    if (my_is_timeout_triggered) {
        my_is_timeout_triggered = false;
        return true;
    }
    return false;
}

// Static ISR Callback
bool IRAM_ATTR Esp32s3::timer_callback(gptimer_handle_t timer, 
                                      const gptimer_alarm_event_data_t *edata, 
                                      void *user_ctx) {
    auto* instance = static_cast<Esp32s3*>(user_ctx);
    instance->my_is_timeout_triggered = true;
    return true; 
}

} // namespace driver::timer


