![DelyDSP_BlockDiagram2](https://github.com/user-attachments/assets/85eaec03-887c-41e4-83b3-f7d02a1667db)
The above block diagram illustrates the overall DSP architecture of this delay plugin. Each module is implemented as an independent class to ensure modularity and maintainability.

<br>


**🔁 1. Pan & Ping-Pong Module -> 🕒 2. Delay Engine -> 🔄 3. Feedback Module -> ♦️4. Filter Section**

<br>


----------

**1. Pan & Ping-Pong Module**

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
