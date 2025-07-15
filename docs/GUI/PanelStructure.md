##  2. Panel Structure

The GUI is composed of modular panels that all inherit from a common base class, ```PanelBase```.
Each panel is responsible for a specific function, but shares a consistent layout system and visual frame.

<br>
<br>

###  1. ```PanelBase``` and ```GroupComponent```-Based Design

All panels inherit from ```PanelBase```, which itself is based on ```juce::GroupComponent```.
```GroupComponent``` provides a **visual frame with a title**, and the title is centered using:


<img width="479" alt="image" src="https://github.com/user-attachments/assets/31b55820-5e4c-4d62-b867-8ed9537f060e" />


~~~cpp
PanelBase::PanelBase(const juce::String& inTitle, EulerDelayAudioProcessor& inAudioprocessor)
: juce::GroupComponent(inTitle, inTitle), mAudioprocessor(inAudioprocessor)
{
    setTextLabelPosition(juce::Justification::horizontallyCentred);
}
~~~

This ensures that every panel shares a consistent frame structure, while allowing each subclass
to define its own internal controls like buttons or knobs.

<br>
<br>


###  2. Static Layout via Constants

Each panel manually calculates component size and position using layout constants defined in the ```Mysize```
namespace. 

~~~cpp
mLabelMix.setSize(MySize::RotaryKnob::Width, MySize::Label::Height);
mKnobMix.setSize(MySize::RotaryKnob::Width, MySize::RotaryKnob::Height);
~~~

All layout logic is placed inside each panel's ```resized()``` method. For example:

~~~cpp
const int xLabelMix = boundlocal.getX() + MySize::Padding::Width;
const int yLabelMix = boundlocal.getY() + MySize::Padding::Top::Height;
mLabelMix.setTopLeftPosition(xLabelMix, yLabelMix);
~~~
-> This provides **pixel-level precision**, centralized layout control, and consistent spacing
across panels.

<br>
<br>

###  3. Manual Panel Placement in Editor

All panels are manually created and positioned in the editor class (```EulerDelayAudioProcessorEditor```) using ```setSize()``` and ```setTopLeftPosition()```

~~~cpp
mPanelControl.setTopLeftPosition(0, MySize::GUI::Header::Height);
mPanelDelay.setTopLeftPosition(mPanelControl.getRight(), mPanelControl.getY());
~~~

Certain UI states - like PingPong mode - dynamically affect panel layout or visibillity:

~~~cpp
mPanelDelay.setSize(MySize::Panel::Delay::Width,
                    inButton->getToggleState() ? MySize::Panel::Delay::Height / 2
                                               : MySize::Panel::Delay::Height);
~~~
-> This approach allows full layout control without layout managers, and supports
**state - driven UI tranformations**.
