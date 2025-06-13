/*
  ==============================================================================

    LookAndFeel.h
    Created: 25 Apr 2025 9:42:10am
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace MyColors
{
    namespace Main
    {
        const juce::Colour background { 245, 240, 235 };
        const juce::Colour header { 40, 40, 40 };
    }
    
    namespace Panel
    {
        const juce::Colour title { 120, 115, 110 };
        const juce::Colour outline { 215, 210, 205 };
    }
    
    namespace RotaryKnob
    {
        const juce::Colour trackBackground { 205, 200, 195 };
        const juce::Colour trackActive { 177, 101, 135 };
        const juce::Colour outline { 255, 250, 245 };
        const juce::Colour gradientTop { 250, 245, 240 };
        const juce::Colour gradientBottom { 240, 235, 230 };
        const juce::Colour dial { 100, 100, 100 };
        const juce::Colour dropShadow { 195, 190, 185 };
        const juce::Colour label { 80, 80, 80 };
        const juce::Colour textBoxBackground { 80, 80, 80 };
        const juce::Colour value { 240, 240, 240 };
        const juce::Colour caret { 255, 255, 255 };
        const juce::Colour selected { 0, 206, 209 }; // dark turquoise
    }
    
    namespace Button
    {
        const juce::Colour text { 80, 80, 80 };
        const juce::Colour textToggled { 40, 40, 40 };
        const juce::Colour background { 245, 240, 235 };
        const juce::Colour backgroundToggled { 255, 250, 245 };
        const juce::Colour outline { 215, 210, 205 };
    }
    
    namespace ComboBox
    {
        const juce::Colour background { 245, 240, 235 };
        const juce::Colour text { 80, 80, 80 };
        const juce::Colour outline { 169, 169, 169 };
        const juce::Colour arrow { 105, 105, 105 };
    }
    
    namespace PopupMenu
    {
        const juce::Colour background { 245, 240, 235 };
        const juce::Colour text  { 80, 80, 80 };
        const juce::Colour backgroundHighlighted { 177, 101, 135 };
        const juce::Colour textHighlighted { 240, 240, 240 };
    }
    
    namespace LevelMeter
    {
        const juce::Colour background { 245, 240, 235 };
        const juce::Colour tickLine { 200, 200, 200 };
        const juce::Colour tickLabel { 80, 80, 80 };
        const juce::Colour tooLoud { 226, 74, 81 };
        const juce::Colour levelOK { 50, 205, 50 }; // Lime green
    }
}

class MyLookAndFeel  : public juce::LookAndFeel_V4
{
    public:
        MyLookAndFeel();
        ~MyLookAndFeel() override;
        
        juce::Font getLabelFont (juce::Label& inLabel) override;
        juce::Font getPopupMenuFont() override;

        void drawRotarySlider (juce::Graphics& g,
                               int x, int y, int width, int height,
                               float sliderPosProportional,
                               float rotaryStartAngle,
                               float rotaryEndAngle,
                               juce::Slider& inSlider) override;
    private:
        juce::FontOptions mFontOption;
        
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyLookAndFeel)
};
