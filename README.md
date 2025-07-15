https://github.com/user-attachments/assets/581d852f-8d63-471f-80a1-2d97df4a2f69



# EulerDelay
A JUCE-based delay plugin developed in C++.

<br>

##  Documentation
**All DSP and implementation details are available in the `docs/` folder:**


### DSP
- BlockDiagram
- DelayEngine
- FeedbackModule
- Filter
- PingPong

### Parameters
- APVTS
- Smoothing
- StereoLink
- Stucture
- TimeMode

### GUI
- LookAndFeel
- Overview
- PanelStructure
- ParameterBlinding

### Preset
- FactoryPreset
- PluginState
- XmlPreset
 
<br>

##  Features

 **Delay Section**
- Tempo-synced or time-based delay modes (sync to BPM or set in milliseconds)
- Independent L/R settings
- Link toggle for syncing L/R delay times
- Ping-Pong mode support

 **Feedback Section**
- Adjustable feedback amount
- Low-cut filter
- High-cut filter

 **Output Section**
- Dry/Wet Mix control
- Output Gain control

 **Preset Management**
- Preset loading & saving system

 **Technical Info**
- Built using JUCE & Xcode
- Supports AU, VST3, and AAX plugin formats

<br>

##  Build Instructions
1. Open `EulerDelay.jucer` in Projucer
2. Export to Xcode and open project
3. Build and run

<br>

##  Author
Created by SangHoon You (2025)
