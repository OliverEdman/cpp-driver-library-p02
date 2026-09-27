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

    // Get value from sensor via read()
    const auto rawAdcValue = myAdc.read();

    // Use ML model to predict temperature
    const float predictedTemp = myModel->predict(static_cast<float>(rawAdcValue));

    return predictedTemp;
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
                  float learningRate,
                  float precisionThreshold)
{

    myModel = std::make_unique<ml::lin_reg::Adaptive>(trainIn, trainOut);

    // Start training algorithm and return true if target precision was reached.
    return myModel->train(epochCount, learningRate, precisionThreshold);
}

} // namespace driver::tempsensor