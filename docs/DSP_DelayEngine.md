## 2. Delay Engine

### 🔷 Overview
The Delay Engine handles per-channel delay processing using a **circular buffer** and supports fractional delay times through **Hermite interpolation.** Each channel (L/R) is processed independently via the ModuleDelay class, which internally uses the MyDelay class.

<br>

🌀 Why Circular Buffer?

![image](https://github.com/user-attachments/assets/2465bb49-4543-4788-be7b-b46365a9abe1)

A circular buffer is a fixed-size data structure that treats memory as a ring, where the end wraps around to the beginning. It uses two pointers:

- TAIL (Write Index): where new incoming samples are stored
- HEAD (Read Index): where delayed samples are retrieved
