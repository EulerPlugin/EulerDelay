## ✅ 4. LookAndFeel System

<br>

### 🔹 1. Purpose**

```MyLookAndFeel``` customized the entire plugin GUI by inheriting from ```LookAndFeel_V4```
It unsures consistent **font, colors and component rendering logic**
It is applied at the end of the PluginEditor constructor:

~~~cpp
// Class: EulerDelayAudioProcessorEditor
// Function: Constructor
setLookAndFeel(&mLookAndFeel);
~~~

This comes after all panels are added, to endure no visual inconsistencies.

<br>
<br>

### 🔹 2. What is LookAndFeel?**

JUCE's ```LookAndFeel``` is a base class designed to fully override the drawing logic for all UI components

~~~cpp
// Class: juce::LookAndFeel
class LookAndFeel : public Slider::LookAndFeelMethods, ...
~~~

It inherits multiple ```LookAndFeelMethods``` and defines many **pure virtual functions**, such as:

~~~cpp
// Class: LookAndFeel
// Function: drawRotarySlider()
virtual void drawRotarySlider(...) = 0;
~~~

This makes it an **interface-like base**, requiring full implementation by the user

<br>
<br>

### 🔹 3. Class Definition and Font Customization**

<img width="486" alt="image" src="https://github.com/user-attachments/assets/6ffe0863-6cb9-4268-8fc0-d36c8daf48b3" />

~~~cpp
// Class: MyLookAndFeel
// Function: Constructor
MyLookAndFeel::MyLookAndFeel()
: mFontOption(juce::Typeface::createSystemTypefaceFor(BinaryData::LatoMedium_ttf,
                                                      BinaryData::LatoMedium_ttfSize))
~~~

- Loads a ```.ttf``` font from binary resources
- Applied in:

~~~cpp
// Class: MyLookAndFeel
// Function: getLabelFont()
juce::Font MyLookAndFeel::getLabelFont(...)
{
    return mFontOption.withHeight(MySize::Font::Height);
}

// Class: MyLookAndFeel
// Function: getPopupMenuFont()
juce::Font MyLookAndFeel::getPopupMenuFont()
{
    return mFontOption.withHeight(MySize::Font::Height);
}
~~~
-> Ensures consistent typeface across labels and popups

<br>
<br>

### 🔹 4. Centralized Color Management**

~~~cpp
// Class: MyLookAndFeel
// Function: Constructor
setColour(juce::Slider::rotarySliderFillColourId, MyColors::RotaryKnob::trackActive);
setColour(juce::Label::textColourId, MyColors::RotaryKnob::label);
setColour(juce::TextButton::textColourOnId, MyColors::Button::textToggled);
...
~~~

- All UI elements referene the ```MyColors``` namespace
- Centralized style system improves maintainabillity


<br>
<br>


### 🔹 5. Rotary Knob Custom Drawing**

<img width="550" alt="image" src="https://github.com/user-attachments/assets/5bee16e8-5f5b-4a54-b90d-44fb32dd1492" />

~~~cpp
// Class: MyLookAndFeel
// Function: drawRotarySlider()
void MyLookAndFeel::drawRotarySlider(...)
~~~

- Draw order:
  1. Outer bounds
  2. Inner knob with drop shadow
  3. Gradient fill
  4. Background ring
  5. Value track
  6. Dial indicator

