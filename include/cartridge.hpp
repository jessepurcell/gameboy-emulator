//*
//* This file contains the declaration of the Cartridge class.
//* The Cartridge class is responsible for loading the ROM file into memory.
//* The Cartridge class also provides a method to read a byte from the ROM.
//*

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

  std::vector<uint8_t> getROM() const { return rom; }

 private:
  std::vector<uint8_t> rom;
};