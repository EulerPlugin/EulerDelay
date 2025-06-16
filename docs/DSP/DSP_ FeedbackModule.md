## 3. Feedback Module

### 🔷 Overview
The Feedback Module manages the reinjection of the delayed signal back into the processing chain, allowing for echo and decay effects.
Each channel (L/R) maintains its own feedback line using a simple buffer (MyFeedback), which holds one sample between iterations.

This module connects directly into the signal path, between the delay output and the ping-pong input, as shown in the block diagram.

<br>

~~~cpp
// in processBlock()
float feedbackL = 0.0f;
float feedbackR = 0.0f;

// 1. Retrieve stored feedback from previous cycle
mModuleFeedback.processPop(feedbackL, feedbackR);

// ...
// delay processing happens here
// ...

// 2. Store new delayed sample for next cycle (with feedback gain)
mModuleFeedback.processPush(wetL, wetR,
                            mParameters.getValueAmount(),
                            ..., ...);
~~~
This ensures that for every incoming sample, one feedback value is used and one is stored, creating a continuous sample-by-sample feedback loop.
