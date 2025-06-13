/*
  ==============================================================================

    MyRotaryKnob.cpp
    Created: 23 Feb 2025 5:35:50pm
    Author:  sanghoonyou

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyRotaryKnob.h"
#include "MySize.h"

//==============================================================================
MyRotaryKnob::MyRotaryKnob(juce::AudioProcessorValueTreeState& inApvts,
                           const juce::String& inParamId,
                           const bool inDrawFromMiddle)
:juce::Slider(inParamId),
 mAttachment(inApvts,inParamId,*this)
{
    //Style
    setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false,
                    MySize::RotaryKnob::Width, MySize::RotaryKnob::TextBox::Height);
    setRotaryParameters(juce::degreesToRadians(225.0f),
                        juce::degreesToRadians(495.0f),
                        true);
                        
    getProperties().set("drawFromMiddle", inDrawFromMiddle);
}

MyRotaryKnob::~MyRotaryKnob()
{

}
