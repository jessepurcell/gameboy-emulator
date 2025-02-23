#pragma once

#include <cstdint>
#include <bitset>
#include <array>
#include <expected>

class CPU
{
public:
    CPU();
    void reset();
    std::expected<void, std::string> executeNextInstruction(); // Modern error handling

    // Registers (16-bit pairs)
    enum Reg16
    {
        AF,
        BC,
        DE,
        HL,
        SP,
        PC,
        COUNT
    };
    std::array<uint16_t, COUNT> registers{};

    // Memory Access (via MMU)
    uint8_t readByte(uint16_t address);
    void writeByte(uint16_t address, uint8_t value);

    // Flags using std::bitset for clarity
    std::bitset<8> flags;
    enum FlagBit
    {
        Z = 7,
        N = 6,
        H = 5,
        C = 4
    }; // Zero, Subtract, Half-Carry, Carry
    bool getFlag(FlagBit flag) const { return flags.test(flag); }
    void setFlag(FlagBit flag, bool value) { flags.set(flag, value); }

private:
    void executeInstruction(uint8_t opcode);
};
