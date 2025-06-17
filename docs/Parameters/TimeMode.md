## 5. Tempo vs Millisecond Mode


This delay plugin allows users to set delay time in two different ways:

- **Millisecond Mode**: The user manually enters time in milliseconds.
- **Tempo Sync Mode**: Time is automatically calculated based on the DAW’s BPM and selected note value.

<br>
<br>

🔹 Step 1. Tempo Parameter Definition

~~~cpp
layout.add(std::make_unique<AudioParameterBool>(
    MyParamId::Control::Tempo, "Tempo", false));
~~~

- This toggle parameter allows the user to switch between ms mode and tempo-sync mode.
- Default value: ```false``` (millisecond mode).

<br>
<br>


🔹 Step 2. Conditional Time Calculation (inside ```update()```)

~~~cpp
const bool tempo = mParamTemopo->get();

for (int i = 0; i < 2; ++i)
{
    const int ch = mValuePingPong ? 0 : i;

    const double timeSec = tempo
        ? getTimeByNote(inBpm, mParamNote[ch]->getIndex())
        : mParamTime[ch]->get() * 0.001;

    mValueTime[i].setTarget(timeSec * mSampleRate);
}
~~~

- If ```tempo == true```: delay time is calculated from BPM and note index.
- If ```tempo == false```: raw ms input is converted to seconds.
- The final result is converted to samples and passed to ```setTarget()``` for smoothing.

<br>
<br>

🔹 Step 3. ```getTimeByNote()``` Calculation Logic

~~~cpp
double MyParameters::getTimeByNote(const double inBpm, const int inNote) const noexcept
{
    static constexpr double scalars[] = {
        0.25 * 2.0 / 3.0,  // SixteenthTriplet
        0.125 * 1.5,       // ThirtySecondDotted
        0.25,              // Sixteenth
        0.5 * 2.0 / 3.0,   // EighthTriplet
        0.25 * 1.5,        // SixteenthDotted
        0.5,               // Eighth
        1.0 * 2.0 / 3.0,   // QuarterTriplet
        0.5 * 1.5,         // EighthDotted
        1.0,               // Quarter
        2.0 * 2.0 / 3.0,   // HalfTriplet
        1.0 * 1.5,         // QuarterDotted
        2.0,               // Half
        4.0 * 2.0 / 3.0,   // WholeTriplet
        2.0 * 1.5          // HalfDotted
    };

    const double secondPerBeat = 60.0 / inBpm;
    return secondPerBeat * scalars[inNote];
}
~~~

- A fixed ```constexpr``` array is used to convert note index into time scaling factor.
- No conditionals → extremely efficient in real-time.
- Supports standard, dotted, and triplet notes.

<br>
<br>

🔹 Step 4. Execution Timing

~~~cpp
void EulerDelayAudioProcessor::processBlock(...)
{
    updateBpm(bpm);              // Get BPM from host
    mParameters.update(bpm);     // Perform time calculation
}
~~~

- ```update()``` is called once per audio buffer.
- It caches sample-based delay time, which is then smoothed during the sample loop.

<br>
<br>

🔹 Step 5. Smoothing in the Sample Loop

~~~cpp
void MyParameters::smoothen() noexcept
{
    mValueTime[0].smoothen();
    mValueTime[1].smoothen();
}
~~~

- Smooth transitions between delay times using ```LinearSmoothedValue```.
- No recalculation inside the audio sample loop → safe for real-time DSP.
