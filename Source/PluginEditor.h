/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PanelDelay.h"
#include "PanelOutput.h"
#include "PanelFeedback.h"
#include "PanelControl.h"
#include "MyLookAndFeel.h"
#include "PanelPingPong.h"

//==============================================================================
/**
*/
class EulerDelayAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        private juce::Button::Listener
{
public:
    EulerDelayAudioProcessorEditor (EulerDelayAudioProcessor&);
    ~EulerDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    EulerDelayAudioProcessor& audioProcessor;
    
    PanelControl mPanelControl;
    PanelDelay mPanelDelay;
    PanelFeedback mPanelFeedback;
    PanelOutput mPanelOutput;
    PanelPingPong mPanelPingPong;
    
    MyLookAndFeel mLookAndFeel;
    
    juce::Button& mButtonPingPong;
    void buttonClicked(juce::Button* inButton) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EulerDelayAudioProcessorEditor)
};
