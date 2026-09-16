#ifndef FREERTOS_MOCK_H_
#define FREERTOS_MOCK_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef void* QueueHandle_t;
typedef uint32_t TickType_t;
typedef uint32_t EventBits_t;
typedef void* EventGroupHandle_t;

#define pdFALSE 0
#define pdTRUE 1
#define pdMS_TO_TICKS(ms) (static_cast<TickType_t>(ms))

static inline void vTaskDelay(TickType_t ticks)
{
    (void)ticks;
}

static inline TickType_t xTaskGetTickCount(void)
{
    return 0U;
}

static inline EventGroupHandle_t xEventGroupCreate(void)
{
    static int event_group;
    return &event_group;
}

static inline void vEventGroupDelete(EventGroupHandle_t event_group)
{
    (void)event_group;
}

static inline EventBits_t xEventGroupClearBits(EventGroupHandle_t event_group,
                                               EventBits_t bits_to_clear)
{
    (void)event_group;
    (void)bits_to_clear;
    return 0U;
}

static inline EventBits_t xEventGroupSetBits(EventGroupHandle_t event_group,
                                             EventBits_t bits_to_set)
{
    (void)event_group;
    return bits_to_set;
}

static inline EventBits_t xEventGroupWaitBits(EventGroupHandle_t event_group,
                                              EventBits_t bits_to_wait_for,
                                              int clear_on_exit,
                                              int wait_for_all_bits,
                                              TickType_t ticks_to_wait)
{
    (void)event_group;
    (void)clear_on_exit;
    (void)wait_for_all_bits;
    (void)ticks_to_wait;
    return bits_to_wait_for;
}

#ifdef __cplusplus
}
#endif

#endif /** FREERTOS_MOCK_H_ */
