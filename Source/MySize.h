/*
  ==============================================================================

    MySize.h
    Created: 23 Feb 2025 5:38:42pm
    Author:  sanghoonyou

  ==============================================================================
*/

#pragma once

namespace MySize
{
    namespace Padding
    {
        static constexpr int Width = 15;
        
        namespace Top
        {
            static constexpr int Height = 25;
        }
        
        namespace Mid
        {
            static constexpr int Height = 15;
        }
        
        namespace Bottom
        {
            static constexpr int Height = 20;
        }
    }
    
    namespace Label
    {
        static constexpr int Height = 20;
    }
    
    namespace RotaryKnob
    {
        static constexpr int Width = 75;
        
        namespace TextBox
        {
            static constexpr int Height = Label::Height;
        }
        static constexpr int Height = Width + TextBox::Height;
    }
    
    namespace PresetComboBox
    {
        static constexpr int Width = 85;
        static constexpr int Height = 23;
    }
    
    namespace ParamToggleButton
    {
        static constexpr int Width = 34;
        static constexpr int Height = 22;
    }
    
    namespace Panel
    {
        namespace Delay
        {
            static constexpr int Width = Padding::Width + RotaryKnob::Width + Padding::Width;
            static constexpr int Height = Padding::Top::Height +
                                          Label::Height +
                                          RotaryKnob::Height +
                                          Padding::Bottom::Height +
                                          Padding::Top::Height +
                                          Label::Height +
                                          RotaryKnob::Height +
                                          Padding::Bottom::Height;
        }
        
        namespace Output
        {
            static constexpr int Width = Padding::Width + RotaryKnob::Width + Padding::Width;
            static constexpr int Height = Delay::Height;
        }
        
        namespace Feedback
        {
            static constexpr int Width = Padding::Width +
                                         RotaryKnob::Width + Padding::Width +
                                         RotaryKnob::Width + Padding::Width +
                                         RotaryKnob::Width + Padding::Width;
                                         
            static constexpr int Height = Delay::Height;
        }
        namespace Control
        {
            static constexpr int Width = Padding::Width + PresetComboBox::Width + Padding::Width;
            static constexpr int Height = Delay::Height;
        }
        
        namespace PingPong
        {
            static constexpr int Width = Padding::Width + RotaryKnob::Width + Padding::Width;
            static constexpr int Height = Delay::Height / 2;
        }
    }
    
    namespace GUI
    {
        namespace Header
        {
            static constexpr int Height = 40;
        }
        
        static constexpr int Width = Panel::Control::Width + Panel::Delay::Width + Panel::Feedback::Width +Panel::Output::Width;
        static constexpr int Height = Header::Height + Panel::Delay::Height;
    }
    
    namespace Font
    {
        static constexpr int Height = 15.0f;
    }
}
