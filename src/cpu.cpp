#include "../include/cpu.hpp"
#include <algorithm>

CPU::CPU()
{
    // Default all opcodes to NOP to prevent crashes
    opcodeTable.fill(&CPU::NOP);
    cbOpcodeTable.fill(&CPU::NOP);

    // Map primary opcodes
    opcodeTable[0x00] = &CPU::NOP;
    opcodeTable[0x01] = &CPU::LD_BC_nn;
    opcodeTable[0x80] = &CPU::ADD_A_B;

    // Map CB-prefixed opcodes
    cbOpcodeTable[0x00] = &CPU::RLC_B;
}

void CPU::executeOpcode()
{
    uint8_t opcode = fetchByte();

    if (opcode == 0xCB)
    {
        uint8_t cbOpcode = fetchByte();
        (this->*cbOpcodeTable[cbOpcode])();
    }
    else
    {
        (this->*opcodeTable[opcode])();
    }
}

void CPU::NOP() { /* No operation */ }

void CPU::LD_BC_nn()
{
    setBC(fetchWord());
}

void CPU::ADD_A_B()
{
    A += B;
    updateFlags();
}

void CPU::RLC_B()
{
    B = (B << 1) | (B >> 7);
    updateFlags();
}

// uint8_t CPU::fetchByte()
// {
//     // TODO: Fetch byte from memory at PC++
//     return 0x00;
// }

uint8_t CPU::fetchByte() {
    return testMemory[PC++];
}

uint16_t CPU::fetchWord()
{
    uint16_t lo = fetchByte();
    uint16_t hi = fetchByte();
    return (hi << 8) | lo;
}

void CPU::updateFlags()
{
    // TODO: Implement flag updates
}
