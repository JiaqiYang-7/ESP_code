#include "mbed.h"
// Define Potentiometer class
class Potentiometer {
protected:
    AnalogIn inputSignal;
    float VDD;

public:
    Potentiometer(PinName pin, float v) : inputSignal(pin), VDD(v) {}

    float sample() {
        return inputSignal.read() * VDD;
    }
};

// Define SamplingPotentiometer class inheriting Potentiometer
class SamplingPotentiometer : public Potentiometer {
private:
    Ticker sampler;
    float samplingFrequency, samplingPeriod;
    float sampledValue;

    // Callback function that is called periodically by Ticker
    void samplePotentiometerCallback();

public:
    SamplingPotentiometer{(PinName p, float v, float fs)
        : Potentiometer(p, v), samplingFrequency(fs) {
        samplingPeriod = 1.0f / samplingFrequency;
        sampler.attach(callback(this, &SamplingPotentiometer::samplePotentiometerCallback), samplingPeriod);
    }}

    float getSampledValue();
};