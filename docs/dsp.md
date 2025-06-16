![DelyDSP_BlockDiagram2](https://github.com/user-attachments/assets/85eaec03-887c-41e4-83b3-f7d02a1667db)
The above block diagram illustrates the overall DSP architecture of this delay plugin. Each module is implemented as an independent class to ensure modularity and maintainability.

<br>


**1. Pan & Ping-Pong Module -> 2. Delay Engine -> 3. Feedback Module -> 4. Filter Section**

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
