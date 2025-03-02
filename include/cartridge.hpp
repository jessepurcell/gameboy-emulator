#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

class Cartridge {
 public:
  Cartridge() {};
  ~Cartridge() {};

  std::optional<uint8_t> loadROM(const std::string &filename);
  std::optional<uint8_t> readByte(uint16_t address) const;

 private:
  std::vector<uint8_t> rom;
};