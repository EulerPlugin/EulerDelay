## ✅ 4. LookAndFeel System

<br>

**🔹 1. Purpose**

```MyLookAndFeel``` customized the entire plugin GUI by inheriting from ```LookAndFeel_V4```
It unsures consistent **font, colors and component rendering logic**
It is applied at the end of the PluginEditor constructor:

~~~cpp
// Class: EulerDelayAudioProcessorEditor
// Function: Constructor
setLookAndFeel(&mLookAndFeel);
~~~

This comes after all panels are added, to endure no visual inconsistencies.
