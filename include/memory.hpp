/**
 * @file memory.hpp
 * @brief Defines the Memory class for the Game Boy emulator.
 */

#pragma once

#include <array>
#include <cstdint>

/**
 * @class Memory
 * @brief Represents the memory of the Game Boy.
 * 
 * This class provides methods to read and write bytes and words to the Game Boy's memory.
 */
class Memory {
public:
    /**
     * @brief Constructs a new Memory object.
     */
    Memory();

    /**
     * @brief Reads a byte from the specified address.
     * 
     * @param address The address to read from.
     * @return The byte read from the specified address.
     */
    uint8_t readByte(uint16_t address);

    /**
     * @brief Writes a byte to the specified address.
     * 
     * @param address The address to write to.
     * @param value The byte value to write.
     */
    void writeByte(uint16_t address, uint8_t value);

    /**
     * @brief Reads a word (two bytes) from the specified address.
     * 
     * @param address The address to read from.
     * @return The word read from the specified address.
     */
    uint16_t readWord(uint16_t address);

    /**
     * @brief Writes a word (two bytes) to the specified address.
     * 
     * @param address The address to write to.
     * @param value The word value to write.
     */
    void writeWord(uint16_t address, uint16_t value);

private:
    /**
     * @brief The memory array representing the Game Boy's memory.
     */
    std::array<uint8_t, 0x10000> memory{};
};
