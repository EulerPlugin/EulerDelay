## 1. Pan & Ping-Pong Module

### 🔷 Overview
The following DSP flow is handled in real-time inside the `processBlock()` function:

~~~cpp
mModulePingPong.process(dryL, dryR, feedbackL, feedbackR,
                        outPingPongL, outPingPongR,
                        mParameters.getValuePingPong(),
                        mParameters.getValueWidth());
~~~
This indicates that the Ping-Pong module is part of the core per-sample audio processing path.

<br>
<img width="280" alt="Panning_Principle" src="https://github.com/user-attachments/assets/c83d4df3-f9ac-4114-93a2-e8d87d62d5e7" />

<br>
<br>

- Stereo input (x[n] left, x[n] right) is summed to mono.
- The mono signal is split into panL and panR using a **cosine/sine-based equal-power panning law.**

<br>

### 🎧 Why Use Equal-Power Panning Law?
<img width="406" alt="image" src="https://github.com/user-attachments/assets/01217271-bda1-4ff8-8b66-0c6218ff79f0" />

Human perception of loudness is based not on raw amplitude, but on **power**, which is proportional to the square of amplitude.  
If we pan a mono signal using linear volume scaling between the left and right channels, we experience the so-called **"hole-in-the-middle"** effect — the center position sounds quieter.

To avoid this, we use the **equal-power panning law**, where:

- `L(θ) = cos(θ)`  
- `R(θ) = sin(θ)`

As shown in the graph above, these functions ensure:

- `L² + R² = 1` at all times  
- Resulting in **constant total power** across all pan positions  
- Which provides a **consistent perceived loudness** as the signal moves across the stereo field

This method is widely used in audio production because it ensures natural-sounding panning without loudness dips or boosts.

<br>

~~~cpp
void MyPanning::process(const float inSampleL, const float inSampleR,
                        float& outSampleL, float& outSampleR,
                        const bool inPanning, const float inWidth) noexcept
{
    if (inPanning)
    {
        if (inWidth != mWidth)
        {
            mWidth = inWidth;
            const float x = (MathConstants<float>::pi * 0.25f) * (inWidth + 1.0f);
            mPanL = std::cos(x);
            mPanR = std::sin(x);
        }

        const float mono = 0.5f * (inSampleL + inSampleR);
        outSampleL = mono * mPanL;
        outSampleR = mono * mPanR;
    }
    else
    {
        outSampleL = inSampleL;
        outSampleR = inSampleR;
    }
}
~~~
<br>

### 🔁 Ping-Pong Logic

The ping-pong effect swaps feedback paths between the channels to create a bouncing stereo effect.

~~~cpp
void ModulePingPong::process(const float inSampleL, const float inSampleR,
                             const float inFeedbackL, const float inFeedbackR,
                             float& outSampleL, float& outSampleR,
                             const bool inPingPong, const float inWidth) noexcept
 {
    float outPanL = 0.0f;
    float outPanR = 0.0f;
    
    mPanning.process(inSampleL, inSampleR, outPanL, outPanR, inPingPong, inWidth);
    
    outSampleL = inPingPong ? (outPanL + inFeedbackR) : (outPanL + inFeedbackL);
    outSampleR = inPingPong ? (outPanR + inFeedbackL) : (outPanR + inFeedbackR);
 }
~~~
This logic dynamically redirects the feedback paths depending on the ping-pong state.

| Ping-Pong | Left Output            | Right Output            |
|-----------|------------------------|-------------------------|
| `true`    | `panL + feedbackR`     | `panR + feedbackL`      |
| `false`   | `panL + feedbackL`     | `panR + feedbackR`      |

<br>
