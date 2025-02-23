# 🎮 Game Boy Emulator
![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/jessepurcell/gameboy-emulator/ci.yml?branch=main)
![GitHub repo size](https://img.shields.io/github/repo-size/jessepurcell/gameboy-emulator)
![GitHub license](https://img.shields.io/github/license/jessepurcell/gameboy-emulator)
![C++ Version](https://img.shields.io/badge/C%2B%2B-23-blue.svg)
![GitHub last commit](https://img.shields.io/github/last-commit/jessepurcell/gameboy-emulator)

🚀 **Game Boy Emulator** is a work-in-progress emulator written in **C++23** that aims to emulate the original **Nintendo Game Boy (DMG-01)** hardware. This project is still under active development, with the goal of accurately replicating the CPU, memory, and graphics system.

---

## 📖 **Table of Contents**
- [🎮 Features](#-features)
- [⚙️ Installation](#️-installation)
- [🚀 Usage](#-usage)
- [📝 Roadmap](#-roadmap)
- [📜 License](#-license)
- [🤝 Contributing](#-contributing)

---

## 🎮 **Features (Planned)**
❌ **Full CPU Emulation** – Implements the Game Boy's **LR35902** CPU (Z80-like).  
❌ **Memory Management** – Emulates **8KB RAM**, **8KB VRAM**, and cartridge ROM banking.  
❌ **Graphics (PPU) Emulation** – Uses SDL2 for pixel-accurate rendering.  
❌ **Sound Emulation** – Implements the Game Boy’s **APU** (Audio Processing Unit).  
❌ **Input Handling** – Maps keyboard/controller inputs to the Game Boy’s buttons.  
❌ **Unit Tests** – Uses **GoogleTest** for regression testing.  
❌ **Cross-Platform Support** – Runs on **Windows, macOS, and Linux**.  

🚧 **Development is ongoing! Check the [roadmap](#-roadmap) for upcoming milestones.**  

---

## ⚙️ **Installation**
### **🔹 Requirements**
Ensure you have the following installed:
- **C++20** compiler (GCC, Clang, or MSVC)
- **CMake 3.14+**
- **GoogleTest** (for testing)
- **SDL3** (for graphics rendering)

### **🔹 Build Instructions**
```sh
# Clone the repository
git clone https://github.com/jessepurcell/gameboy-emulator.git
cd gameboy-emulator

# Initialize submodules (for GoogleTest)
git submodule update --init --recursive

# Create a build directory and compile
mkdir build && cd build
cmake ..
make

# Run the emulator (once implemented)
./gameboy-emulator
```

---

## 🚀 **Usage**
🚧 **Emulator is not yet functional.** 🚧  

When implemented, you will be able to run a Game Boy ROM like this:
```sh
./gameboy-emulator path/to/rom.gb
```

### **🎮 Planned Controls**
| Game Boy Button | Keyboard Mapping |
|----------------|-----------------|
| A             | X               |
| B             | Z               |
| Start         | Enter           |
| Select        | Shift           |
| D-Pad Up      | Up Arrow        |
| D-Pad Down    | Down Arrow      |
| D-Pad Left    | Left Arrow      |
| D-Pad Right   | Right Arrow     |

---

## 📝 **Roadmap**
📌 **Phase 1**:  
- [ ] Implement CPU (LR35902) instruction set  
- [ ] Implement memory banking system  
- [ ] Add basic I/O operations  

📌 **Phase 2**:  
- [ ] Implement PPU for graphics rendering  
- [ ] Implement APU for audio emulation  
- [ ] Add save state support  

📌 **Phase 3**:  
- [ ] Add Game Boy Color support  
- [ ] Optimize performance  
- [ ] Port to WebAssembly  

---

## 📜 **License**
This project is licensed under the **MIT License**. See [`LICENSE`](LICENSE) for details.

---

## 🤝 **Contributing**
Contributions are welcome! 🎉  

1. Fork the repository 🍴  
2. Create a new branch (`git checkout -b feature-name`)  
3. Commit your changes (`git commit -m "Add feature"`)  
4. Push to your branch (`git push origin feature-name`)  
5. Open a pull request 📌  

---

## 📬 **Contact**
📧 Email: **jesse.purcell@my.jcu.edu.au**  
🐦 Twitter: **[@Slaydevil1](https://x.com/Slaydevil1)**  
💻 GitHub: **[jessepurcell](https://github.com/jessepurcell)**  
