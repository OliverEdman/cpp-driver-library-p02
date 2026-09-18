/**
 * @file Smart temperature sensor driver using adaptive machine learning.
 */
#pragma once

#include <memory>

#include "driver/adc/interface.h"
#include "driver/tempsensor/interface.h"
#include "ml/lin_reg/adaptive.h"
#include "ml/types.h"

namespace driver::tempsensor
{
/**
 * @brief Smart temperature sensor driver using an adaptive machine learning model.
 *
 *        This class is non-copyable and non-movable.
 */
class Smart final : public Interface
{
public:
    /**
     * @brief Constructor.
     *
     * @param[in] adc Reference to the ADC driver interface.
     */
    explicit Smart(driver::adc::Interface& adc) noexcept;

    /**
     * @brief Destructor.
     */
    ~Smart() noexcept override = default;

    /**
     * @brief Read the current temperature from the sensor using the ML model.
     *
     * @return The temperature value in degrees Celsius.
     */
    [[nodiscard]] float readCelsius() noexcept override;

    /**
     * @brief Checks if the temperature sensor driver is successfully initialized.
     *
     * @return true if initialized and ready, false otherwise.
     */
    [[nodiscard]] bool isInitialized() const noexcept override;

    /**
     * @brief Train the adaptive linear regression ml model.
     *
     * @param[in] trainIn Training inputs (ADC raw values).
     * @param[in] trainOut Training outputs (temperatures in Celsius).
     * @param[in] epochCount Number of epochs to train.
     * @param[in] learningRate Initial learning rate.
     * @param[in] precisionThreshold Precision threshold to stop early.
     *
     * @return True if training was performed successfully, false otherwise.
     */
    bool train(const ml::lin_reg::Matrix1d& trainIn, const ml::lin_reg::Matrix1d& trainOut,
               std::size_t epochCount = 1000U, double learningRate = 0.01,
               double precisionThreshold = 0.999) noexcept;

    Smart()                        = delete; // No default constructor.
    Smart(const Smart&)            = delete; // No copy constructor.
    Smart(Smart&&)                 = delete; // No move constructor.
    Smart& operator=(const Smart&) = delete; // No copy assignment.
    Smart& operator=(Smart&&)      = delete; // No move assignment.

private:
    /** Reference to the ADC driver. */
    driver::adc::Interface& myAdc;

    /** Pointer to the adaptive linear regression model. */
    std::unique_ptr<ml::lin_reg::Adaptive> myModel;
};
} // namespace driver::tempsensor