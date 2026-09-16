#ifndef TIMER_MOCK_H_
#define TIMER_MOCK_H_

#include "arch/env/test/esp32/types.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef void* gptimer_handle_t;

#define GPTIMER_CLK_SRC_DEFAULT 0
#define GPTIMER_COUNT_UP 1

typedef struct
{
    int clk_src;
    int direction;
    uint32_t resolution_hz;
} gptimer_config_t;

typedef struct
{
    uint64_t count_value;
    uint64_t alarm_value;
} gptimer_alarm_event_data_t;

typedef bool (*gptimer_alarm_cb_t)(gptimer_handle_t timer,
                                   const gptimer_alarm_event_data_t* edata,
                                   void* user_data);

typedef struct
{
    gptimer_alarm_cb_t on_alarm;
} gptimer_event_callbacks_t;

typedef struct
{
    bool auto_reload_on_alarm;
} gptimer_alarm_config_flags_t;

typedef struct
{
    uint64_t alarm_count;
    uint64_t reload_count;
    gptimer_alarm_config_flags_t flags;
} gptimer_alarm_config_t;

static inline esp_err_t gptimer_new_timer(const gptimer_config_t* config,
                                          gptimer_handle_t* ret_timer)
{
    static int timer;
    (void)config;
    if (ret_timer == nullptr) { return ESP_ERR_INVALID_ARG; }
    *ret_timer = &timer;
    return ESP_OK;
}

static inline esp_err_t gptimer_register_event_callbacks(gptimer_handle_t timer,
                                                         const gptimer_event_callbacks_t* cbs,
                                                         void* user_data)
{
    (void)timer;
    (void)cbs;
    (void)user_data;
    return ESP_OK;
}

static inline esp_err_t gptimer_enable(gptimer_handle_t timer)
{
    (void)timer;
    return ESP_OK;
}

static inline esp_err_t gptimer_disable(gptimer_handle_t timer)
{
    (void)timer;
    return ESP_OK;
}

static inline esp_err_t gptimer_del_timer(gptimer_handle_t timer)
{
    (void)timer;
    return ESP_OK;
}

static inline esp_err_t gptimer_set_alarm_action(gptimer_handle_t timer,
                                                 const gptimer_alarm_config_t* config)
{
    (void)timer;
    (void)config;
    return ESP_OK;
}

static inline esp_err_t gptimer_start(gptimer_handle_t timer)
{
    (void)timer;
    return ESP_OK;
}

static inline esp_err_t gptimer_stop(gptimer_handle_t timer)
{
    (void)timer;
    return ESP_OK;
}

#ifdef __cplusplus
}
#endif

#endif /** TIMER_MOCK_H_ */
