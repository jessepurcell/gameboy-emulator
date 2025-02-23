#pragma once

#include <array>
#include <cstdint>

class CPU
{
public:
    uint8_t testMemory[0x10000] = {}; // 64KB of memory
    using OpcodeHandler = void (CPU::*)();

    CPU();                // Constructor to initialize the LUT
    void executeOpcode(); // Fetch, decode, and execute an instruction

    // Registers
    uint8_t A = 0, B = 0, C = 0, D = 0, E = 0, H = 0, L = 0;
    uint16_t SP = 0, PC = 0;
    uint16_t BC() const { return (B << 8) | C; }
    void setBC(uint16_t value)
    {
        B = value >> 8;
        C = value & 0xFF;
    }

    // Fetching and execution helpers
    uint8_t fetchByte();
    uint16_t fetchWord();
    void updateFlags();

private:
    // Lookup tables for opcodes
    std::array<OpcodeHandler, 256> opcodeTable{};
    std::array<OpcodeHandler, 256> cbOpcodeTable{};

    // Instruction handlers
    void NOP();
    void LD_BC_nn();
    void ADD_A_B();
    void RLC_B();
};
