## 3. Feedback Module

![image](https://github.com/user-attachments/assets/f03c105e-96b1-4f75-b28e-73890c391600)

###  Overview
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

<br>

The ModuleFeedback class manages left and right feedback lines independently:
~~~cpp
void ModuleFeedback::processPop(float& outSampleL, float& outSampleR) const noexcept
{
    outSampleL = mFeedbackL.popSample();
    outSampleR = mFeedbackR.popSample();
}

void ModuleFeedback::processPush(const float inSampleL,
                                 const float inSampleR,
                                 const float inFeedbackAmount,
                                 const float inLowCut,
                                 const float inHighCut) noexcept
{
    const float outfeedbackL = inSampleL * inFeedbackAmount;
    const float outfeedbackR = inSampleR * inFeedbackAmount;

    // Filtering omitted
    mFeedbackL.pushSample(outfeedbackL);
    mFeedbackR.pushSample(outfeedbackR);
}
~~~

<br>

Each mFeedbackL and mFeedbackR instance is of type MyFeedback, a simple one-sample memory buffer:
~~~cpp
class MyFeedback
{
public:
    void pushSample(const float inSample, const float inAmount) noexcept
    {
        mSampleFeedback = inSample * inAmount;
    }

    float popSample() const noexcept
    {
        return mSampleFeedback;
    }

    void reset() noexcept
    {
        mSampleFeedback = 0.0f;
    }

private:
    float mSampleFeedback = 0.0f;
};
~~~
This mechanism enables a minimal, real-time-safe feedback loop with per-channel independence.
