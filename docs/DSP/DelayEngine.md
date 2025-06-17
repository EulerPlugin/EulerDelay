## 2. Delay Engine

### 🔷 Overview
The Delay Engine handles per-channel delay processing using a **circular buffer** and supports fractional delay times through **Hermite interpolation.** Each channel (L/R) is processed independently via the ModuleDelay class, which internally uses the MyDelay class.

<br>

🌀 Why Circular Buffer?

![image](https://github.com/user-attachments/assets/2465bb49-4543-4788-be7b-b46365a9abe1)

A circular buffer is a fixed-size data structure that treats memory as a ring, where the end wraps around to the beginning. It uses two pointers:

- TAIL (Write Index): where new incoming samples are stored
- HEAD (Read Index): where delayed samples are retrieved

This mechanism allows efficient, continuous memory reuse without shifting data, which is ideal for real-time audio processing.

Why it's used in delay DSP:

- Fixed memory size: perfect for time-based delays with a maximum delay time
- Fast performance: read/write in constant time without dynamic memory allocation
- Natural fit for time-based indexing: past samples can be accessed by computing readIndex = writeIndex - delaySamples, with wrap-around handling

<br>
<br>


🎯 Why Is Interpolation Needed?

<img src="https://github.com/user-attachments/assets/b4ac097b-cdef-4d00-9fc3-85f79cde52dc" width="300"/>

Delay times are often non-integer when expressed in milliseconds or beats.

Example:
At 44.1 kHz, a 7.3 ms delay = 322.53 samples → fractional index.

Without interpolation:

- ❌ Artifacts (clicks, harsh edges)
- ❌ Aliasing when modulating delay time
- ❌ Poor quality for effects like flanging or chorus
  
To solve this, we interpolate between buffer samples to approximate the correct value at a fractional index.

<br>
<br>

🔁 Step-by-Step Explanation

**1. Write to Circular Buffer**
   
The incoming sample is stored at the current mIndexWriting position:

~~~cpp
mBuffer.set(mIndexWriting, inSample);
~~~

<br>

**2. Calculate Read Index**

The delay time (in samples) is subtracted from the write index to determine where to read the delayed sample:
~~~cpp
float indexReading = mIndexWriting - inDelay;
if (indexReading < 0.0f)
    indexReading += mSizeBuffer;  // wrap-around if negative
~~~

<br>

**3. Read Delayed Sample**

Since indexReading can be fractional, interpolation is required:
~~~cpp
const float sampleDelayed = getSampleByHermit(indexReading);
~~~

<br>

**4. Advance the Write Index (Wrap-Around)**

The write index moves forward, and wraps to 0 when it reaches the buffer size:

~~~cpp
mIndexWriting = (mIndexWriting + 1) % mSizeBuffer;
~~~
