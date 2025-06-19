## Factory Preset System

<br>

📌 **Introduction**

The Factory Preset system provides a set of hardcoded parameter values directly 
embedded into the plugin.Users can select from these presets using a combo box, instantly applying them to 
the processor without relying on any external files.
It’s ideal for testing, resetting, or providing reliable default states.

<br>
<br>

**⚙️ Architecture & Flow**

**1. Component Hierarchy (Top-Down)**

~~~cpp
EulerDelayAudioProcessorEditor
└── mPanelControl
    └── MyPresetComboBox
~~~

<br>

**2. Execution Flow (Bottom-Up)**

~~~cpp
User clicks ComboBox
  ↓
MyPresetComboBox → MyPresetManager → MyParameters → APVTS
~~~

