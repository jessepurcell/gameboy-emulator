#pragma once
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

inline void printHexDump(const std::vector<uint8_t>& buffer) {
  const size_t bytesPerRow = 32;

  for (size_t i = 0; i < buffer.size(); i += bytesPerRow) {
    // Print offset
    std::cout << std::hex << std::setw(6) << std::setfill('0') << i << "  ";

    // Print hex values
    for (size_t j = 0; j < bytesPerRow; ++j) {
      if (i + j < buffer.size())
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << (int)buffer[i + j] << " ";
      else
        std::cout << "   ";  // Padding for alignment
    }

    std::cout << " ";

    // Print ASCII characters
    for (size_t j = 0; j < bytesPerRow; ++j) {
      if (i + j < buffer.size()) {
        char c = buffer[i + j];
        std::cout << (isprint(c)
                          ? c
                          : '.');  // Print ASCII or '.' for non-printables
      }
    }

    std::cout << "\n";
  }
}