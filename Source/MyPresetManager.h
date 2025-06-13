/*
  ==============================================================================

    MyPresetManager.h
    Created: 12 Mar 2025 11:50:46am
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MyParameters.h"

class MyPresetManager
{
    public:
        MyPresetManager(MyParameters& inParameters);
        ~MyPresetManager();
        
        juce::String getNametFactoryPreset(const int inIndex) const noexcept;
        int getNumFactoryPresets() const noexcept;
        int getFactoryPresetCurrent() const noexcept;
        void setFactoryPreset(const int inIndex) noexcept;
        
        const juce::File& getDirPreset() const noexcept;
        
        const juce::String& getXmlPresetCurrent() const noexcept;
        void setXmlPresetCurrnet(const juce::String& inNamePreset) noexcept;
        void saveXmlPreset(const juce::File& inFileXml) noexcept;
        void loadXmlPreset(const juce::File& inFileXml) noexcept;
        
        //state
        const juce::Identifier& getIdState() const noexcept;
        juce::ValueTree getState() const noexcept;
        void setByState(const juce::ValueTree& inState) noexcept;
        
    private:
        MyParameters& mParameters;
        
        juce::Array<FactoryPreset> mArrayFactoryPreset;
        int mFactoryPresetCurrent;
        void resetFactoryPreset() noexcept;
        
        const juce::File mDirPreset;
        juce::String mXmlPresetCurrent;
        
        const juce::Identifier mIdstate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyPresetManager)
};
