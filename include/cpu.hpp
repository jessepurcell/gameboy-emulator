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
    uint8_t registers[8] = {0};
    uint8_t &A = registers[0];
    uint8_t &B = registers[1];
    uint8_t &C = registers[2];
    uint8_t &D = registers[3];
    uint8_t &E = registers[4];
    uint8_t &H = registers[5];
    uint8_t &L = registers[6];
    uint8_t &F = registers[7];

    uint16_t SP = 0, PC = 0;
    uint16_t BC() const { return (B << 8) | C; }
    uint16_t DE() const { return (D << 8) | E; }
    uint16_t HL() const { return (H << 8) | L; }

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
    Memory &memory;
    // Lookup tables for opcodes
    std::array<std::function<void()>, 256> opcodeTable{};

    // Instruction handlers
    void NOP();
    void LD_BC_nn();
    void ADD_A_B();
    void RLC_B();

    // Load Instructions
    void LD_r8_r8(uint8_t &destinationRegister, uint8_t sourceRegister);
    void LD_r8_n8(uint8_t &destinationRegister);
    void LD_r8_HL(uint8_t &destinationRegister);
    // void LD_r16_n16(uint16_t &destination);
    // void LD_r16_A(uint16_t& dest);
};
