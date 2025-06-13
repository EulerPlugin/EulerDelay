/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 25 Apr 2025 9:42:10am
    Author:  sanghoonyou

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MyLookAndFeel.h"
#include "MySize.h"

//==============================================================================
MyLookAndFeel::MyLookAndFeel()
:mFontOption(juce::Typeface::createSystemTypefaceFor(BinaryData::LatoMedium_ttf,BinaryData::LatoMedium_ttfSize))
{
    //Background
    setColour(juce::ResizableWindow::backgroundColourId, MyColors::Main::background);
    
    //GroupComponent
    setColour(juce::GroupComponent::outlineColourId, MyColors::Panel::outline);
    setColour(juce::GroupComponent::textColourId, MyColors::Panel::title);
    
    //Label
    setColour(juce::Label::textColourId, MyColors::RotaryKnob::label);
    
    //Button
    setColour(juce::TextButton::textColourOffId, MyColors::Button::text);
    setColour(juce::TextButton::textColourOnId, MyColors::Button::textToggled);
    setColour(juce::TextButton::buttonColourId, MyColors::Button::background);
    setColour(juce::TextButton::buttonOnColourId, MyColors::Button::background);
    
    //ComboBox
    setColour(juce::ComboBox::backgroundColourId, MyColors::ComboBox::background);
    setColour(juce::ComboBox::arrowColourId, MyColors::ComboBox::arrow);
    setColour(juce::ComboBox::outlineColourId, MyColors::ComboBox::outline);
    setColour(juce::ComboBox::textColourId, MyColors::ComboBox::text);
    
    //PopupMenu
    setColour(juce::PopupMenu::backgroundColourId, MyColors::PopupMenu::background);
    setColour(juce::PopupMenu::textColourId, MyColors::PopupMenu::text);
    setColour(juce::PopupMenu::highlightedBackgroundColourId, MyColors::PopupMenu::backgroundHighlighted);
    setColour(juce::PopupMenu::highlightedTextColourId, MyColors::PopupMenu::textHighlighted);
    
    //Slider
    setColour(juce::Slider::rotarySliderFillColourId, MyColors::RotaryKnob::trackActive);
    setColour(juce::Slider::textBoxTextColourId, MyColors::RotaryKnob::label);
    
    setColour(juce::CaretComponent::caretColourId,MyColors::RotaryKnob::caret);
    
}

MyLookAndFeel::~MyLookAndFeel()
{

}

juce::Font MyLookAndFeel::getLabelFont (juce::Label& inLabel)
{
    //Default
    //return juce::LookAndFeel_V4::getLabelFont(inLabel);
    
    return mFontOption.withMetricsKind(juce::TypefaceMetricsKind::legacy).withHeight(MySize::Font::Height);
}

juce::Font MyLookAndFeel::getPopupMenuFont()
{
    //Default
//    return juce::LookAndFeel_V4::getPopupMenuFont();
    
    return mFontOption.withMetricsKind(juce::TypefaceMetricsKind::legacy).withHeight(MySize::Font::Height);

}
    

void MyLookAndFeel::drawRotarySlider (juce::Graphics& g,
                                       int x, int y, int width, int height,
                                       float sliderPosProportional,
                                       float rotaryStartAngle,
                                       float rotaryEndAngle,
                                       juce::Slider& inSlider)
{
    // Default
    // juce::LookAndFeel_V4::drawRotarySlider(inGraphics, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, inSlider);

    // 1. boundlocal
    const juce::Rectangle<float> boundSlider(x, y, width, height);
//    g.setColour(juce::Colours::red);
//    g.drawRect(boundSlider);
    
    // 2. boundSquare
    const int length = (width > height) ? height : width;
    const float lengthSquare = (float)length * 0.85f;
    const juce::Rectangle<float> boundSquare = boundSlider.withSizeKeepingCentre(lengthSquare, lengthSquare);
    
//    g.setColour(juce::Colours::green);
//    g.drawRect(boundSquare);
    
    // 3. boundKnob
    const juce::Rectangle<float> boundKnob = boundSquare.reduced(boundSquare.getWidth() * 0.15f);
//    g.setColour(juce::Colours::blue);
//    g.drawRect(boundKnob);
    
    // 4. dropShadow
    juce::Path path;
    path.addEllipse(boundKnob);
    juce::DropShadow dropShadow(MyColors::RotaryKnob::dropShadow, 10, {0, 3});
    dropShadow.drawForPath(g, path);
    
    g.setColour(MyColors::RotaryKnob::outline);
    g.fillEllipse(boundKnob);
    
    // 5. gradient
    const juce::Rectangle<float> boundInner = boundKnob.reduced(boundKnob.getWidth() * 0.05f);
    const juce::ColourGradient gradient(MyColors::RotaryKnob::gradientTop, 0.0f, boundInner.getY(),
                                        MyColors::RotaryKnob::gradientBottom, 0.0f, boundInner.getBottom(),
                                        false);
    g.setGradientFill(gradient);
    g.fillEllipse(boundInner);
    
    // 6. track background
    const float radiusSquare = boundSquare.getWidth() * 0.5f;
    const float thicknessTrack = radiusSquare * 0.1f;
    const float radiusTrack = radiusSquare - (thicknessTrack * 0.5f);
    
    path.clear();
    path.addCentredArc(boundSquare.getCentreX(), boundSquare.getCentreY(),
                       radiusTrack, radiusTrack, 0.0f,
                       rotaryStartAngle, rotaryEndAngle, true);
    
    const juce::PathStrokeType strokeType(thicknessTrack,
                                          juce::PathStrokeType::JointStyle::curved,
                                          juce::PathStrokeType::EndCapStyle::rounded);
    g.setColour(MyColors::RotaryKnob::trackBackground);
    g.strokePath(path, strokeType);
    
    // 7. dial
    const float angleSliderPos = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
    const float theta = angleSliderPos - juce::MathConstants<float>::halfPi;
    const float radiusDial = boundInner.getWidth() * 0.5f;
    const float Rstart = radiusDial * 0.5f;
    const float Rend = radiusDial * 0.85f;
    
    const juce::Point<float> postDialStart(boundInner.getCentreX() + Rstart * std::cos(theta),
                                           boundInner.getCentreY() + Rstart * std::sin(theta));
    const juce::Point<float> postDialEnd(boundInner.getCentreX() + Rend * std::cos(theta),
                                           boundInner.getCentreY() + Rend * std::sin(theta));
    
    path.clear();
    path.startNewSubPath(postDialStart);
    path.lineTo(postDialEnd);
    
    g.setColour(MyColors::RotaryKnob::dial);
    g.strokePath(path, strokeType);
    
    
    // 8. track value
    const bool fromMiddle = inSlider.getProperties()["drawFromMiddle"];
    const float angleStart = fromMiddle ? rotaryStartAngle + ( rotaryEndAngle - rotaryStartAngle ) / 2 :
                                          rotaryStartAngle;
                    
    
    path.clear();
    path.addCentredArc(boundSquare.getCentreX(), boundSquare.getCentreY(),
                       radiusTrack, radiusTrack, 0.0f,
                       angleStart, angleSliderPos, true);

    g.setColour(MyColors::RotaryKnob::trackActive);
    g.strokePath(path, strokeType);
    
    // 8. track value 그냥 했을대
//    path.clear();
//    path.addCentredArc(boundSquare.getCentreX(), boundSquare.getCentreY(),
//                       radiusTrack, radiusTrack, 0.0f,
//                       rotaryStartAngle, angleSliderPos, true);
//    g.setColour(MyColors::RotaryKnob::trackActive);
//    g.strokePath(path, strokeType);
    
    
    
}
