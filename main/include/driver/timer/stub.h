#pragma once
#include "driver/timer/Interface.h"
#include <cstdio>
#include <cstdint>

namespace driver::timer {

    /**
     * @class Stub
     * @brief Test implementation of the Timer interface.
     * 
     * This class simulates timer behavior without hardware,
     */
    class Stub final : public Interface {
    public:
        /**
         * @brief Constructor initializing the stub variables.
         */
        Stub() noexcept
            : stub_isRunning(false),
              stub_isTimeout(false),
              stub_period(0) 
        {

        }

    private: 
        bool stub_isRunning;      
        bool stub_isTimeout;     
        std::uint32_t stub_period; 

    public:

        /** 
         * @brief Checks if the timer is initialized.
         * @return Always returns true. 
         */
        bool isInitialized() const noexcept override {
            return true;
        }

        /** 
         * @brief Gets the current timeout period.
         * @return The period as a 32-bit unsigned integer. 
         */
        std::uint32_t timeout_ms() const noexcept override {
            return stub_period;
        }

        /** 
         * @brief Sets the timer timeout period.
         * @param period_ms Duration in milliseconds (32 bit).
         */
        void setPeriod(std::uint32_t period_ms) noexcept override {
            stub_period = period_ms;
            std::printf("Period set to %u ms\n", period_ms);
        }

        /** @brief Starts the simulated timer counter. */
        void start() noexcept override {
            stub_isRunning = true;
            std::printf("Timer has Started!\n");
        }

        /** @brief Stop timer counter. */
        void stop() noexcept override {
            stub_isRunning = false;
            std::printf("Timer has Stopped!\n");
        }

        /** 
         * @brief Checks if the timer is currently running.
         * @return True if running, false otherwise.
         */
        bool isRunning() const noexcept override {
            if (stub_isRunning) {
                std::printf("Timer is now Running\n");
            } else {
                std::printf("Timer is now Stopped\n");
            }
            return stub_isRunning;
        }

        /** @brief Toggles the timer state between started and stopped. */
        void toggle() noexcept override {
            stub_isRunning = !stub_isRunning;
            if (stub_isRunning) {
                std::printf("Timer is now Running\n");
            } else {
                std::printf("Timer is now Stopped\n");
            }
        }
        /** 
         * @brief Manually resets the simulated timeout.
         */
        void reset() noexcept {
            stub_isTimeout = false;
            std::printf("Timer timeout reset!\n");
        }

        /** 
         * @brief Checks if a timeout has occurred.
         */
        bool isTimeout() const noexcept {
            return stub_isTimeout;
        }

        /**
         * @brief Manually triggers a timeout event if the timer is running.
         */
        void simulateTimeout() noexcept {
            if (stub_isRunning) {
                stub_isTimeout = true;
                std::printf("Timeout triggered manually!\n");
            } else {
                std::printf("Cannot trigger timeout, timer is stopped.\n");
            }
        }
    }; 
} // namespace driver::timer
