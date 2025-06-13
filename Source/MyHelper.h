/*
  ==============================================================================

    MyHelper.h
    Created: 5 Mar 2025 1:53:24pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace MyHelper
{
    enum CmdIdButtons
    {
        Tempo,  // 0
        Link,   // 1
        PingPong // 2
    };
    
    inline void protectEars(juce::AudioBuffer<float>& inBuffer)
    {
        bool warning = true;
        for (int channel = 0; channel < inBuffer.getNumChannels(); ++channel)
        {
            const float* channelData = inBuffer.getReadPointer(channel);
            for (int i = 0; i < inBuffer.getNumSamples(); ++i)
            {
                bool shouldSilence = false;
                const float sample = channelData[i];
                if (std::isnan(sample))
                {
                    DBG("!!! SILENCING: nan detected in audio buffer !!!");
                    shouldSilence = true;
                }
                else if (std::isinf(sample))
                {
                    DBG("!!! SILENCING: inf detected in audio buffer !!!");
                    shouldSilence = true;
                }
                else if (sample < -2.0f || sample > 2.0f) // screaming feedback (> 6dB)
                {
                    DBG("!!! SILENCING: sample out of range (> 6dB) !!!");
                    shouldSilence = true;
                }
                else if (sample < -1.0f || sample > 1.0f)
                {
                    if (warning == true)
                    {
                        DBG("!!! WARNING: sample out of range (> 0dB) !!!");
                        warning = false;
                    }
                }
                
                if (shouldSilence)
                {
                    inBuffer.clear();
                    return;
                }
            }
        }
    }
}
