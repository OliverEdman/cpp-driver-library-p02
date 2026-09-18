/**
 * @file Implementation for the smart temperature sensor using ML linear regression adaptive model.
 */

#include "driver/tempsensor/smart.h"

namespace driver::tempsensor
{
// -----------------------------------------------------------------------------
Smart::Smart(driver::adc::Interface& adc) noexcept 
    : myAdc{adc}
    , myModel{nullptr}
{
}

// -----------------------------------------------------------------------------
float Smart::readCelsius() noexcept
{
    if (!isInitialized())
    {
        return 0.0f;
    }

    // Get value from sensor via read();
    const auto rawAdcValue = myAdc.read();

    // Use ML model to predict RawAdcValue and save in predictedTemp
    const double predictedTemp = myModel->predict(static_cast<double>(rawAdcValue));

    // Convert result from double to float and return value.
    return static_cast<float>(predictedTemp);

}
// -----------------------------------------------------------------------------
bool Smart::isInitialized() const noexcept
{
    return myAdc.isInitialized() && (myModel != nullptr);
}

// -----------------------------------------------------------------------------
bool Smart::train(const ml::lin_reg::Matrix1d& trainIn, 
                  const ml::lin_reg::Matrix1d& trainOut,
                  std::size_t epochCount, 
                  double learningRate,
                  double precisionThreshold) noexcept
{
    
    // Allocate and initialize the ML model dynamically with the training data in memory.
    myModel = std::make_unique<ml::lin_reg::Adaptive>(trainIn, trainOut);

    // Start the training algorithm and return if we have reached the target preccision.
    return myModel->train(epochCount, learningRate, precisionThreshold);
}

} // namespace driver::tempsensor