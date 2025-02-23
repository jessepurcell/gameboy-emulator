#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <bitset>
#include <array>
#include <expected>
#include <string>

class CPU {
public:
    CPU();
    void reset();
    
    // Executes next instruction, returns success or error message
    std::expected<bool, std::string> executeNextInstruction();

    // Registers (16-bit pairs)
    enum Reg16 { AF, BC, DE, HL, COUNT };
    std::array<uint16_t, COUNT> registers{};
    
    // Stack Pointer and Program Counter (separate from general-purpose registers)
    uint16_t SP = 0;
    uint16_t PC = 0;

    // Memory Access (via MMU, to be implemented elsewhere)
    uint8_t readByte(uint16_t address);
    void writeByte(uint16_t address, uint8_t value);

    // Flags using std::bitset for clarity
    std::bitset<8> flags;
    enum FlagBit { ZF = 7, NF = 6, HF = 5, CF = 4 }; // Zero, Subtract, Half-Carry, Carry

    // Flag Manipulation Functions
    bool getFlag(FlagBit flag) const { return flags.test(flag); }
    void setFlag(FlagBit flag, bool value) { flags.set(flag, value); }
    void clearFlags() { flags.reset(); } // Utility function

private:
    void executeInstruction(uint8_t opcode);
};

#endif // CPU_HPP
