#ifndef SERIAL_MOCK_H_
#define SERIAL_MOCK_H_

#include "arch/env/test/esp32/types.h"

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

// Dummy definitions.
#define UART_DATA_8_BITS 0U
#define UART_PARITY_DISABLE 1U
#define UART_STOP_BITS_1 2U
#define UART_HW_FLOWCTRL_DISABLE 3U
#define UART_SCLK_DEFAULT 4U
#define UART_PIN_NO_CHANGE (-1)
#define UART_NUM_0 0

    typedef int uart_port_t;

    typedef struct
    {
        uint8_t dummy;
    } uart_flags_t;

    typedef struct
    {
        int baud_rate;
        int data_bits;
        int parity;
        int stop_bits;
        int flow_ctrl;
        int rx_flow_ctrl_thresh;
        int rx_glitch_filt_thresh;
        int source_clk;
        uart_flags_t flags;
    } uart_config_t;

    typedef struct
    {
        int tx_buffer_size;
        int rx_buffer_size;
    } usb_serial_jtag_driver_config_t;

#define USB_SERIAL_JTAG_DRIVER_CONFIG_DEFAULT() \
    usb_serial_jtag_driver_config_t {}

    static inline bool uart_is_driver_installed(uart_port_t uart_num)
    {
        (void)uart_num;
        return false;
    }

    static inline esp_err_t uart_param_config(uart_port_t uart_num,
                                              const uart_config_t* uart_config)
    {
        (void)uart_num;
        (void)uart_config;
        return ESP_OK;
    }

    static inline esp_err_t uart_set_pin(uart_port_t uart_num, int tx_io_num, int rx_io_num,
                                         int rts_io_num, int cts_io_num)
    {
        (void)uart_num;
        (void)tx_io_num;
        (void)rx_io_num;
        (void)rts_io_num;
        (void)cts_io_num;
        return ESP_OK;
    }

    static inline esp_err_t uart_driver_install(uart_port_t uart_num, int rx_buffer_size,
                                                int tx_buffer_size, int queue_size,
                                                void** uart_queue, int intr_alloc_flags)
    {
        (void)uart_num;
        (void)rx_buffer_size;
        (void)tx_buffer_size;
        (void)queue_size;
        (void)intr_alloc_flags;
        if (uart_queue != nullptr) { *uart_queue = nullptr; }
        return ESP_OK;
    }

    static inline esp_err_t uart_driver_delete(uart_port_t uart_num)
    {
        (void)uart_num;
        return ESP_OK;
    }

    static inline esp_err_t uart_enable_pattern_det_baud_intr(uart_port_t uart_num,
                                                              char pattern_chr, uint8_t chr_num,
                                                              int chr_tout, int post_idle,
                                                              int pre_idle)
    {
        (void)uart_num;
        (void)pattern_chr;
        (void)chr_num;
        (void)chr_tout;
        (void)post_idle;
        (void)pre_idle;
        return ESP_OK;
    }

    static inline esp_err_t uart_disable_pattern_det_intr(uart_port_t uart_num)
    {
        (void)uart_num;
        return ESP_OK;
    }

    static inline esp_err_t uart_pattern_queue_reset(uart_port_t uart_num, int queue_length)
    {
        (void)uart_num;
        (void)queue_length;
        return ESP_OK;
    }

    static inline int uart_pattern_pop_pos(uart_port_t uart_num)
    {
        (void)uart_num;
        return -1;
    }

    static inline int uart_pattern_get_pos(uart_port_t uart_num)
    {
        (void)uart_num;
        return -1;
    }

    static inline int uart_write_bytes(uart_port_t uart_num, const void* src, size_t size)
    {
        (void)uart_num;
        (void)src;
        return static_cast<int>(size);
    }

    static inline int uart_read_bytes(uart_port_t uart_num, void* buf, uint32_t length,
                                      uint32_t ticks_to_wait)
    {
        (void)uart_num;
        (void)buf;
        (void)length;
        (void)ticks_to_wait;
        return 0;
    }

    static inline esp_err_t
    usb_serial_jtag_driver_install(const usb_serial_jtag_driver_config_t* config)
    {
        (void)config;
        return ESP_OK;
    }

    static inline esp_err_t usb_serial_jtag_driver_uninstall(void) { return ESP_OK; }

    static inline int usb_serial_jtag_write_bytes(const void* src, size_t size,
                                                  uint32_t ticks_to_wait)
    {
        (void)src;
        (void)ticks_to_wait;
        return static_cast<int>(size);
    }

    static inline int usb_serial_jtag_read_bytes(void* buf, uint32_t length, uint32_t ticks_to_wait)
    {
        (void)buf;
        (void)length;
        (void)ticks_to_wait;
        return 0;
    }

#ifdef __cplusplus
}
#endif

#endif /** SERIAL_MOCK_H_ */
