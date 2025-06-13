/*
  ==============================================================================

    MyParameters.h
    Created: 18 Jan 2025 2:33:05pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "MySmoother.h"

//==============================================================================
/*
*/

struct FactoryPreset
{
    juce::String mName;
    float mTime[2];
    float mFeedback;
    float mMix;
    float mGain;
};

namespace MyParamId
{
    const juce::ParameterID Test("Test",1);
    
    namespace Control
    {
        const juce::ParameterID Tempo("Tempo",1);
        const juce::ParameterID Link("Link",1);
        const juce::ParameterID PingPong("PingPong", 1);
    }

    namespace Output
    {
        const juce::ParameterID Gain("Gain",1);
        const juce::ParameterID Mix("Mix",1 );
    }
    
    namespace Delay
    {
        const juce::ParameterID Time[2] { {"TimeL",1} , {"TimeR",1} };
        const juce::ParameterID Note[2] { {"NoteL",1} , {"NoteR",1} };
    }
    
    namespace FeedBack
    {
        const juce::ParameterID Amount("Amount", 1);
        const juce::ParameterID LowCut("LowCut", 1);
        const juce::ParameterID HighCut("HighCut", 1);
    }
    
    namespace PingPong
    {
        const juce::ParameterID Width("Width", 1);
    }
}

class MyParameters  : private juce::AudioProcessorValueTreeState::Listener,
                      private juce::Timer
{
public:
    MyParameters(juce::AudioProcessorValueTreeState& inApvts);
    ~MyParameters() override;
    
    void update(const double inBpm=120.0) noexcept;

    void prepare(const double inSampleRate) noexcept;
    void smoothen() noexcept;
    void reset() noexcept;

    float getValueGain() const noexcept;
    float getValueTest() const noexcept;
    float getValueMix() const noexcept;
    float getValueTime(const int inChannel) const noexcept;
    
    //Feedback
    float getValueAmount() const noexcept;
    
    //PingPong
    float getValueWidth() const noexcept;
    bool getValuePingPong() const noexcept;
    
    // LowCut
    float getValueLowCut() const noexcept;
    
    //HighCut
    float getValueHighCut() const noexcept;

    //Preset
    void setParamsByFactoryPreset(const FactoryPreset& inPreset) noexcept;
    
    bool setParamsByValueTree(const juce::ValueTree& inState) noexcept;
    
    juce::ValueTree getStateCopied() const noexcept;
    
    static constexpr float kTimeMin = 5.0f;
    static constexpr float kTimeMax = 2000.0f;
    static const float kTimeMin2;
    
    static juce::AudioProcessorValueTreeState::ParameterLayout initparameterLayout();
    
private:

    juce::AudioProcessorValueTreeState& mApvts;
    double mSampleRate;
    
    //Gain
    juce::AudioParameterFloat* mParamGain;
    juce::LinearSmoothedValue<float> mValueGain;
    
    //Test
    juce::AudioParameterFloat* mParamTest;
    //juce::LinearSmoothedValue<float> mValueTest;
    MySmoother mValueTest;
    
    //Delay
    juce::AudioParameterFloat* mParamTime[2];
    MySmoother mValueTime[2];
    
    //Mix
    juce::AudioParameterFloat* mParamMix;
    juce::LinearSmoothedValue<float> mValueMix;
    
    //Feedback
    juce::AudioParameterFloat* mParamAmount;
    juce::LinearSmoothedValue<float> mValueAmount;
    
    //Tempo
    juce::AudioParameterBool* mParamTemopo;
    
    //Note
    juce::AudioParameterChoice* mParamNote[2];
    
    double getTimeByNote(const double inBpm,const int inNote) const noexcept;
    
    juce::AudioParameterBool* mParamLink;
    void parameterChanged(const juce::String& inParamID,float inValue) override;
    std::atomic<int> mChannelMaster;
    std::atomic<bool> mFlagLinking;
    void timerCallback() override;
    
    //PingPong
    juce::AudioParameterFloat* mParamWidth;
    juce::LinearSmoothedValue<float> mValueWidth;
    
    juce::AudioParameterBool* mParamPingPong;
    bool mValuePingPong;
    
    // LowCut
    juce::AudioParameterFloat* mParamLowCut;
    juce::LinearSmoothedValue<float> mValueLowCut;
    
    //HighCut
    juce::AudioParameterFloat* mParamHighCut;
    juce::LinearSmoothedValue<float> mValueHighCut;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyParameters)
};

