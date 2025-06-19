### Block Diagram
<br>

<img width="1075" alt="블록다이어그램_필터까지" src="https://github.com/user-attachments/assets/50a4a271-cf2f-4edd-a683-417169e7ecc6" />

The above block diagram illustrates the overall DSP architecture of this delay plugin. Each module is implemented as an independent class to ensure modularity and maintainability.

<br>


#### 🔁 1. Pan & Ping-Pong Module -> 🕒 2. Delay Engine -> 🔄 3. Feedback Module -> ♦️4. Filter Section

<br>

~~~cpp
 for(int i=0;i<buffer.getNumSamples();++i)
    {
       const float dryL = bufferInputL[i];
       const float dryR = bufferInputR[i];

       float feedbackL = 0.0f;
       float feedbackR = 0.0f;
       mModuleFeedback.processPop(feedbackL, feedbackR);
       
       
       float outPingPongL = 0.0f;
       float outPingPongR = 0.0f;
       mModulePingPong.process(dryL, dryR, feedbackL, feedbackR,
                               outPingPongL, outPingPongR,
                               mParameters.getValuePingPong(),
                               mParameters.getValueWidth());

       float wetL = 0.0f;
       float wetR = 0.0f;
       mModuleDelay.process(outPingPongL, outPingPongR,
                            wetL , wetR ,
                            mParameters.getValueTime(0),
                            mParameters.getValueTime(1));

       const float outL = mModuleOutput.process(dryL, wetL,
                                                mParameters.getValueMix(),
                                                mParameters.getValueGain());
                                                
       const float outR = mModuleOutput.process(dryR, wetR,
                                                mParameters.getValueMix(),
                                                mParameters.getValueGain());
       
       bufferOutputL[i] = outL;
       bufferOutputR[i] = outR;

       mModuleFeedback.processPush(wetL, wetR,
                                   mParameters.getValueAmount(),
                                   mParameters.getValueLowCut(),
                                   mParameters.getValueHighCut());
    }
~~~
The above processBlock() loop implements the exact DSP flow depicted in the block diagram.

<br>

~~~cpp
Input
 ↓
[Feedback Pop] ←───────┐
 ↓                     │
[Ping-Pong + Panning]  │
 ↓                     │
[Delay]                │
 ↓                     │
[Output Mix]           │
 ↓                     │
Output                [Feedback Push]
~~~
