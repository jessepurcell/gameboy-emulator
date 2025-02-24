#pragma once

#include "memory.hpp"

#include <array>
#include <cstdint>
#include <functional>

class CPU
{
public:
    CPU(Memory &memory);
    void executeOpcode();

    // Registers
    uint8_t &A = registers[0];
    uint8_t &C = registers[1];
    uint8_t &B = registers[2];
    uint8_t &E = registers[3];
    uint8_t &D = registers[4];
    uint8_t &L = registers[5];
    uint8_t &H = registers[6];
    uint8_t &F = registers[7];

    uint16_t SP = 0, PC = 0;

    // Access and return reference to combined BC using pointer
    uint16_t& BC() {
        // Cast pointer to uint16_t* to treat B and C as a 16-bit value
        return *reinterpret_cast<uint16_t*>(&registers[1]);
    }

    uint16_t& DE() {
        return *reinterpret_cast<uint16_t*>(&registers[3]);  // D and E
    }

    uint16_t& HL() {
        return *reinterpret_cast<uint16_t*>(&registers[5]);  // H and L
    }

    void setBC(uint16_t value)
    {
        B = value >> 8;
        C = value & 0xFF;
    }

    void setDE(uint16_t value)
    {
        D = value >> 8;
        E = value & 0xFF;
    }

    void setHL(uint16_t value)
    {
        H = value >> 8;
        L = value & 0xFF;
    }

    // Fetching and execution helpers
    uint8_t fetchByte();
    uint16_t fetchWord();
    void updateFlags();

private:
    uint8_t registers[8] = {0};
    uint16_t BC_register = 0;
    uint16_t DE_register = 0;
    uint16_t HL_register = 0;

    Memory &memory;
    // Lookup tables for opcodes
    std::array<std::function<void()>, 256> opcodeTable{};

    // Instruction handlers
    void NOP();

    // Load Instructions
    void LD_r8_r8(uint8_t &destinationRegister, uint8_t sourceRegister);
    void LD_r8_n8(uint8_t &destinationRegister);
    void LD_r16_n16(uint16_t &destination);
    void LD_r16_r16(uint16_t &destination, uint16_t source);
    void LD_r16_r8(uint16_t &destination, uint8_t sourceRegister);
    void LD_r16_n8(uint16_t &destination);
    void LD_r8_r16(uint8_t &destinationRegister, uint16_t &sourceRegister);
};
