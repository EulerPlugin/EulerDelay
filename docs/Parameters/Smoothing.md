### 3. Parameter Smoothing Structure

<br>

🎯 Purpose

In real-time DSP, abrupt parameter changes can cause audio artifacts such as clicks or pops.
To prevent this, juce::LinearSmoothedValue is Used to interpolate parameter trasitions over time.

<br>

🔹 Structure Overview

- Smoothed Parameters:

  Gain, Mix, Time (L/R), Feedback Amount, PingPong Width, LowCut, HighCut

- Smoothing Tool:

  juce::LinearSmoothedValue 

- Lifecycle:

  1. prepare() : Initialize sample rate and smoothing time (50ms)

  2. update() : Set new targets via setTargetValue() (includes unit conversion)

  3. smoothen() : Retrieve interpolated values using getNextValue() per sample.

  4. reset() : Instantly sync current and target values (e.g., for preset load)

<br>

🔹 Example: Gain Parameter

~~~cpp
// Declaration
LinearSmoothedValue<float> mValueGain;

// Initialization
mValueGain.reset(sampleRate, 0.05); //50ms smoothing

// Update (per buffer)
float gainLinear = Decibels::decibelsToGain(mParamGain -> get());
mValueGain.setTargetValue(gainLinear);

// Per-sample smoothing
float smoothedGain = mValueGain.getNextValue();

// Reset
mValueGain.setCurrentAndTargetValue(mValueGain.getTargetValue());
~~~

<br>

🔹 Unit Conversion & Target Assignment in update()

Myparameters::update(double bpm) is called once per audio block, outside the processing loop.
All parameters are converted and assigned via setTargetValue() in a single batch:

- dB -> Linear : juce::Decibels::decibelsToGain()
- ms -> sec -> sampled : ms * 0.001f * sampleRate
- % -> normalized : value * 0.01f
- Hz : used directly

<br>

🔹 Optimization : update() vs smoothen()

~~~cpp
// Called once per block
mParameters.update(bpm);

// Called per sample
for (int i = 0;i < buffer.getNumSamples(); ++i)
{
  mParameters.smoothen();
  ...
}
~~~
