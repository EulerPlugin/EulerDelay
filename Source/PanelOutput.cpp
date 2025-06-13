/*
  ==============================================================================

    PanelOutput.cpp
    Created: 25 Feb 2025 4:31:43pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PanelOutput.h"
#include "MySize.h"

//==============================================================================
PanelOutput::PanelOutput(const juce::String& inTitle,
                         EulerDelayAudioProcessor& inAudioprocessor)
:PanelBase(inTitle, inAudioprocessor),
 mKnobMix(mAudioprocessor.getmApvts(), MyParamId::Output::Mix.getParamID()),
 mKnobGain(mAudioprocessor.getmApvts(), MyParamId::Output::Gain.getParamID(),true)
{
    mLabelMix.setText("Mix", juce::NotificationType::dontSendNotification);
    mLabelMix.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mLabelMix);
    addAndMakeVisible(mKnobMix);
    
    mLabelGain.setText("Gain", juce::NotificationType::dontSendNotification);
    mLabelGain.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mLabelGain);
    addAndMakeVisible(mKnobGain);
}

PanelOutput::~PanelOutput()
{

}


void PanelOutput::resized()
{
    mLabelMix.setSize(MySize::RotaryKnob::Width, MySize::Label::Height);
    mKnobMix.setSize(MySize::RotaryKnob::Width, MySize::RotaryKnob::Height);
    
    mLabelGain.setSize(MySize::RotaryKnob::Width, MySize::Label::Height);
    mKnobGain.setSize(MySize::RotaryKnob::Width, MySize::RotaryKnob::Height);
    
    const juce::Rectangle<int> boundlocal = getLocalBounds();
    
    const int xLabelMix = boundlocal.getX() + MySize::Padding::Width;
    const int yLabelMix = boundlocal.getY() + MySize::Padding::Top::Height;
    mLabelMix.setTopLeftPosition(xLabelMix, yLabelMix);
    mKnobMix.setTopLeftPosition(mLabelMix.getX(), mLabelMix.getBottom());
    
    const int yLabelGain = mKnobMix.getBottom() + MySize::Padding::Mid::Height;
    mLabelGain.setTopLeftPosition(mLabelMix.getX(), yLabelGain);
    mKnobGain.setTopLeftPosition(mLabelGain.getX(), mLabelGain.getBottom());
    
}
