#include "../include/cartridge.hpp"

std::optional<uint8_t> Cartridge::loadROM(const std::string &filename) {
  if (!std::filesystem::exists(filename)) {
    std::cerr << "Error: File not found: " << filename << std::endl;
    return 1;
  }

  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    std::cerr << "Error: Failed to open file: " << filename << std::endl;
    return 2;
  }

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  rom.resize(size);
  if (!file.read(reinterpret_cast<char *>(rom.data()), size)) {
    std::cerr << "Error: Failed to read file: " << filename << std::endl;
    return 3;
  }

  std::cout << "Loaded ROM: " << filename << " (" << size << " bytes)"
            << std::endl;
  return {};
}

std::optional<uint8_t> Cartridge::readByte(uint16_t address) const {
  if (address < rom.size()) {
    return rom[address];
  } else {
    std::cerr << "Error: Address out of bounds: 0x" << std::hex << address
              << std::endl;
    return std::nullopt;
  }
}