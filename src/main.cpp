#include <chrono>
#include <iostream>
#include <thread>

#include "cpu.hpp"
#include "gpu.hpp"
#include "input.hpp"
#include "memory.hpp"
#include "timers.hpp"

CPU cpu;
Memory memory;
GPU gpu;
Input input;
Timers timers;

void syncClock() {
  static auto lastTime = std::chrono::high_resolution_clock::now();
  auto currentTime = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed = currentTime - lastTime;
  double targetFrameTime = 1.0 / 59.7;  // Game Boy refresh rate ~59.7 Hz

  if (elapsed.count() < targetFrameTime) {
    std::this_thread::sleep_for(
        std::chrono::duration<double>(targetFrameTime - elapsed.count()));
  }

  lastTime = std::chrono::high_resolution_clock::now();
}

void runEmulator() {
  bool running = true;

  while (running) {
    // Fetch, Decode, Execute
    cpu.executeOpcode();
    // Handle Hardware Timers
    timers.update();
    // Handle Interrupts
    cpu.handleInterrupts();
    // Update Graphics
    gpu.update();
    // Handle Input
    input.pollEvents();
    // Synchronize to Game Boy Clock Speed
    syncClock();
  }
}

int main(int argc, char* argv[]) {
  //   if (argc < 2) {
  //     std::cerr << "Usage: " << argv[0] << " <ROM file>" << std::endl;
  //     return 1;
  //   }

  //   std::string romPath = argv[1];

  // Start Emulator Loop
  runEmulator();

  return 0;
}
