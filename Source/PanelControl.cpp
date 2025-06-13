/*
  ==============================================================================

    PanelControl.cpp
    Created: 12 Mar 2025 10:42:28am
    Author:  sanghoonyou

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PanelControl.h"
#include "MySize.h"
#include "MyHelper.h"

//==============================================================================
PanelControl::PanelControl(const juce::String& inTitle,
                           EulerDelayAudioProcessor& inAudioprocessor)
:PanelBase(inTitle, inAudioprocessor),
 mPresetComboBox(mAudioprocessor.getPresetManager()),
 mButtonTempo(mAudioprocessor.getmApvts(), MyParamId::Control::Tempo.getParamID(),MyHelper::CmdIdButtons::Tempo),
 mButtonLink(mAudioprocessor.getmApvts(), MyParamId::Control::Link.getParamID(), MyHelper::CmdIdButtons::Link),
 mButtonPingPong(mAudioprocessor.getmApvts(), MyParamId::Control::PingPong.getParamID(), MyHelper::CmdIdButtons::PingPong)
{
    mLabelPreset.setText("Preset", juce::NotificationType::dontSendNotification);
    mLabelPreset.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mLabelPreset);
    addAndMakeVisible(mPresetComboBox);
    
    mLabelTempo.setText("Tempo", juce::NotificationType::dontSendNotification);
    mLabelTempo.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mLabelTempo);
    addAndMakeVisible(mButtonTempo);
    
    mLabelLink.setText("Link", juce::NotificationType::dontSendNotification);
    mLabelLink.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mLabelLink);
    addAndMakeVisible(mButtonLink);
    
    mLabelPingPong.setText("PingPong", juce::NotificationType::dontSendNotification);
    mLabelPingPong.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mLabelPingPong);
    addAndMakeVisible(mButtonPingPong);
    
}

PanelControl::~PanelControl()
{

}

void PanelControl::resized()
{
    mLabelPreset.setSize(MySize::PresetComboBox::Width, MySize::Label::Height);
    mPresetComboBox.setSize(MySize::PresetComboBox::Width, MySize::PresetComboBox::Height);
    mLabelTempo.setSize(MySize::PresetComboBox::Width, MySize::Label::Height);
    mButtonTempo.setSize(MySize::ParamToggleButton::Width, MySize::ParamToggleButton::Height);
    mLabelLink.setSize(MySize::PresetComboBox::Width, MySize::Label::Height);
    mButtonLink.setSize(MySize::ParamToggleButton::Width, MySize::ParamToggleButton::Height);
    mLabelPingPong.setSize(MySize::PresetComboBox::Width, MySize::Label::Height);
    mButtonPingPong.setSize(MySize::ParamToggleButton::Width, MySize::ParamToggleButton::Height);
    
    juce::Rectangle<int> boundlocal = getLocalBounds();
    
    const int xLabelPreset = boundlocal.getX() + MySize::Padding::Width;
    const int yLabelPreset = boundlocal.getY() + MySize::Padding::Top::Height;
    mLabelPreset.setTopLeftPosition(xLabelPreset, yLabelPreset);
    mPresetComboBox.setTopLeftPosition(mLabelPreset.getX(), mLabelPreset.getBottom());
    
    const int yLabelTempo = mPresetComboBox.getBottom() + MySize::Padding::Mid::Height;
    mLabelTempo.setTopLeftPosition(mLabelPreset.getX(), yLabelTempo);
    const int xButtonTempo = boundlocal.getCentreX() - (mButtonTempo.getWidth()/2);
    mButtonTempo.setTopLeftPosition(xButtonTempo, mLabelTempo.getBottom());
    
    
    mLabelLink.setTopLeftPosition(mLabelTempo.getX(), mButtonTempo.getBottom() + MySize::Padding::Mid::Height);
    const int xButtonLink = boundlocal.getCentreX() - (mButtonLink.getWidth()/2);
    mButtonLink.setTopLeftPosition(xButtonLink, mLabelLink.getBottom());
    
    const int yLabelPingPong = mButtonLink.getBottom() + MySize::Padding::Mid::Height;
    mLabelPingPong.setTopLeftPosition(mLabelPreset.getX(), yLabelPingPong);
    const int xButtonPingPong = boundlocal.getCentreX() - mButtonPingPong.getWidth()/2;
    mButtonPingPong.setTopLeftPosition(xButtonPingPong, mLabelPingPong.getBottom());
}

juce::Button& PanelControl::getButtonTempo() noexcept
{
    return  mButtonTempo;
}

juce::Button& PanelControl::getButtonPingPong() noexcept
{
    return mButtonPingPong;
}
