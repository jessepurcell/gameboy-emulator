/**
 * @file memory.cpp
 * @brief Implementation of the Memory class for the Game Boy emulator.
 * 
 * This file contains the implementation of the Memory class, which provides
 * methods to read and write bytes and words to the emulated memory.
 */

#include "../include/memory.hpp"
#include <iostream>

/**
 * @brief Constructs a Memory object and initializes the memory to zero.
 */
Memory::Memory() {
    memory.fill(0);
}

/**
 * @brief Reads a byte from the specified memory address.
 * 
 * @param address The 16-bit address to read from.
 * @return The byte value read from the specified address.
 */
uint8_t Memory::readByte(uint16_t address) {
    return memory[address];
}

/**
 * @brief Writes a byte to the specified memory address.
 * 
 * @param address The 16-bit address to write to.
 * @param value The byte value to write to the specified address.
 */
void Memory::writeByte(uint16_t address, uint8_t value) {
    memory[address] = value;
}

/**
 * @brief Reads a 16-bit word from the specified memory address.
 * 
 * @param address The 16-bit address to read from.
 * @return The 16-bit word value read from the specified address.
 */
uint16_t Memory::readWord(uint16_t address) {
    return readByte(address) | (readByte(address + 1) << 8);
}

/**
 * @brief Writes a 16-bit word to the specified memory address.
 * 
 * @param address The 16-bit address to write to.
 * @param value The 16-bit word value to write to the specified address.
 */
void Memory::writeWord(uint16_t address, uint16_t value) {
    writeByte(address, value & 0xFF);
    writeByte(address + 1, value >> 8);
}