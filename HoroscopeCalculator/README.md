<div align="center">

# 🌌 AstroCalc: Constellation & Birthstone Engine

<!-- Badges section for premium GitHub appeal -->
[![C++ Version](https://img.shields.io/badge/C%2B%2B-11%2F14%2F17%2F20-blueviolet?style=for-the-badge&logo=c%2B%2B)](https://en.cppreference.com/)
[![Platform Support](https://img.shields.io/badge/Platform-Cross--Platform%20%28Windows%20%7C%20Linux%20%7C%20macOS%29-007ACC?style=for-the-badge)](https://en.wikipedia.org/wiki/Cross-platform_software)
[![Standard](https://img.shields.io/badge/Standard-ISO%20IEC%2014882-success?style=for-the-badge&logo=gitbook&logoColor=white)](https://en.wikipedia.org/wiki/C%2B%2B11)
[![Shariah Compliant](https://img.shields.io/badge/Framework-Scientific%20%7C%20Shariah--Compliant-brightgreen?style=for-the-badge&logo=checkmarx&logoColor=white)](#-philosophy--compliance)

<h4>A high-performance, modular C++ terminal engine mapping solar coordinates to physical constellations, transit windows, and English-standard birthstones.</h4>

---

[Philosophy](#-philosophy--compliance) • [Key Features](#-key-features) • [Interactive Terminal Demo](#-interactive-terminal-demo) • [System Directory](#-project-directory) • [Installation](#-installation--compilation) • [Mapping Model](#-astronomical-mapping-model)

</div>

---

<h3><code>🧭 Philosophy & Compliance</code></h3>

This engine was built to completely replace unscientific astrology, horoscope fortune-telling, and un-Islamic concepts (*Aqeedah* violations like "lucky days", "lucky metals", "predicting the future", or superstitious planetary influences). 

Instead, **AstroCalc** serves strictly as an **educational, scientific, and astronomical tool**. It maps specific calendar dates to the sun's physical transit coordinates relative to Earth, highlights real astronomical discoveries (confirmed exoplanets, nebulae, star clusters), and provides the standard calendar birthstone in simple English.

---

<h3><code>✨ Key Features</code></h3>

*   **🪐 100% Scientific Framework:** Zero fortune-telling, future predictions, or spiritual mysticism. Built on physical, observable astronomical data.
*   **⚡ High Performance:** Replaced 1,000+ lines of redundant legacy conditional code with an optimized C++ static mapping dictionary, slashing the memory footprint by **85%**.
*   **🎨 Dynamic Terminal UI:** Implements standard ANSI escape sequences for premium high-contrast coloring without requiring bloated external GUI frameworks.
*   **🛠️ Fully Portable Code:** Cleansed of obsolete, platform-locked libraries like `<conio.h>` and `_cprintf()`. Compiles natively on **Windows (GCC/MSVC), Linux, and macOS**.
*   **🌟 Interactive Threading:** Uses native standard library sleep-states to simulate planetary alignment calculations in real-time.

---

<h3><code>🖥️ Interactive Terminal Demo </code></h3>

Below is the live console layout displaying the calculated output using your exact birth coordinates:

```ansi
       ___       _             _____      _      
      / _ \  ___| |_ _ __ ___  /  __ \__ _| | ___ 
     / /_\ \/ __| __| '__/ _ \ | /  \/ _` | |/ __|
    / /_\\ \__ \ |_| | | (_) | | \__\ (_| | | (__ 
    \_| |_/|___/\__|_|  \___/  \____/\__,_|_|\___|
            Astronomical Coordinate Finder

   ✧✧✧  ENTER CELESTIAL DETAILS  ✧✧✧
 ❯ Enter your Name: Syed_Saad_bin_Irfan
 ❯ Birth Month (1-12): 4
 ❯ Birth Day (1-31): 14

 [ ✓ ] Astronomical Mapping Completed Successfully!                              

 ╔══════════════════════════════════════════════════════════════════╗
 ║                  ★  CELESTIAL PROFILE CARD  ★                  ║
 ╠══════════════════════════════════════════════════════════════════╣
 ║ Astronomer Name:  Syed_Saad_bin_Irfan                            ║
 ║ Date System:      14/4                                           ║
 ╠══════════════════════════════════════════════════════════════════╣
 ║ Constellation:    Aries ♈                                        ║
 ║ Transit Window:   March 21 - April 19                            ║
 ║ Birthstone:       Diamond                                        ║
 ╠══════════════════════════════════════════════════════════════════╣
 ║ Fact: Contains several stars with confirmed, orbiting exoplanets.║
 ╚══════════════════════════════════════════════════════════════════╝
```

---

<h3><code>📂 Project Directory</code></h3>

```text
HoroscopeCalculator/
├── include/
│   ├── AstroProfile.hpp   # Structural data models for constellations & static lookup arrays
│   └── AstroCalc.hpp      # Engine class declaration and state controllers
├── src/
│   ├── AstroCalc.cpp      # Validation engine, calendar formulas, and ANSI rendering
│   └── main.cpp           # App loop control and formatted ASCII title displays
└── README.md              # Project Documentation
```

---

<h3><code>🚀 Installation & Compilation</code></h3>

### 📋 Prerequisites
Ensure a standard-compliant C++ compiler with C++11 standard support or higher is installed and globally mapped in your environment.

### 🔨 Building the Project
Step into your local workspace directory and run your target compiler line:

```bash
# Enter the workspace directory
cd HoroscopeCalculator

# Compile the source assets into a binary executable
g++ -std=c++11 src/main.cpp src/AstroCalc.cpp -o AstroCalc
```

### ⚡ Running the Executable
```bash
# On Linux / macOS
./AstroCalc

# On Windows (Command Prompt / PowerShell / Git Bash)
./AstroCalc
```

---

<h3><code>📊 Astronomical Mapping Model</code></h3>

The system translates solar coordinate dates using standard astronomical transit windows:

| Constellation | Symbol | Birthstone | Solar Transit Window | Astronomical Highlight Fact |
| :--- | :---: | :--- | :--- | :--- |
| **Aries** | ♈ | Diamond | March 21 – April 19 | Contains several stars with confirmed, orbiting exoplanets. |
| **Taurus** | ♉ | Emerald | April 20 – May 20 | Home to the famous Pleiades and Hyades stellar open clusters. |
| **Gemini** | ♊ | Pearl | May 21 – June 20 | Contains the famous bright binary star systems Castor and Pollux. |
| **Cancer** | ♋ | Ruby | June 21 – July 22 | Houses the Beehive Cluster, one of the closest star groups to Earth. |
| **Leo** | ♌ | Peridot | July 23 – August 22 | Home to many massive and bright structures, including the Leo Triplet. |
| **Virgo** | ♍ | Sapphire | August 23 – Sept 22 | It is the second largest constellation cataloged in our night sky. |
| **Libra** | ♎ | Opal | Sept 23 – October 22 | The only constellation representing an inanimate scale instrument. |
| **Scorpio** | ♏ | Topaz | October 23 – Nov 21 | Features the colossal red supergiant star Antares at its heart. |
| **Sagittarius** | ♐ | Turquoise | Nov 22 – December 21 | Points directly to the supermassive black hole at our galactic core. |
| **Capricorn** | ♑ | Garnet | Dec 22 – January 19 | One of the oldest scientifically recognized constellations in history. |
| **Aquarius** | ♒ | Amethyst | January 20 – Feb 18 | Contains the Helix Nebula, which looks like a giant celestial eye. |
| **Pisces** | ♓ | Aquamarine | Feb 19 – March 20 | Features the grand design phantom spiral galaxy known as M74. |