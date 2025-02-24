#include "../include/cpu.hpp"
#include <algorithm>
#include <array>

CPU::CPU(Memory &memory)
    : memory(memory)
{
    // Default all opcodes to NOP to prevent crashes
    opcodeTable.fill([&]() { NOP(); });

    // Map primary opcodes
    opcodeTable[0x00] = std::bind(&CPU::NOP, this);
    opcodeTable[0x01] = std::bind(&CPU::LD_BC_nn, this);
    opcodeTable[0x80] = std::bind(&CPU::ADD_A_B, this);

    opcodeTable[0x40] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(B));
    opcodeTable[0x41] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(C));
    opcodeTable[0x42] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(D));
    opcodeTable[0x43] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(E));
    opcodeTable[0x44] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(H));
    opcodeTable[0x45] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(L));
    opcodeTable[0x46] = std::bind(&CPU::LD_r8_HL, this, std::ref(B));
    opcodeTable[0x47] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(A));

    opcodeTable[0x48] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(B));
    opcodeTable[0x49] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(C));
    opcodeTable[0x4A] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(D));
    opcodeTable[0x4B] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(E));
    opcodeTable[0x4C] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(H));
    opcodeTable[0x4D] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(L));
    opcodeTable[0x4E] = std::bind(&CPU::LD_r8_HL, this, std::ref(C));
    opcodeTable[0x4F] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(A));

    opcodeTable[0x50] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(B));
    opcodeTable[0x51] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(C));
    opcodeTable[0x52] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(D));
    opcodeTable[0x53] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(E));
    opcodeTable[0x54] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(H));
    opcodeTable[0x55] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(L));
    opcodeTable[0x56] = std::bind(&CPU::LD_r8_HL, this, std::ref(D));
    opcodeTable[0x57] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(A));

    opcodeTable[0x58] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(B));
    opcodeTable[0x59] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(C));
    opcodeTable[0x5A] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(D));
    opcodeTable[0x5B] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(E));
    opcodeTable[0x5C] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(H));
    opcodeTable[0x5D] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(L));
    opcodeTable[0x5E] = std::bind(&CPU::LD_r8_HL, this, std::ref(E));
    opcodeTable[0x5F] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(A));

    opcodeTable[0x60] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(B));
    opcodeTable[0x61] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(C));
    opcodeTable[0x62] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(D));
    opcodeTable[0x63] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(E));
    opcodeTable[0x64] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(H));
    opcodeTable[0x65] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(L));
    opcodeTable[0x66] = std::bind(&CPU::LD_r8_HL, this, std::ref(H));
    opcodeTable[0x67] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(A));

    opcodeTable[0x68] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(B));
    opcodeTable[0x69] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(C));
    opcodeTable[0x6A] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(D));
    opcodeTable[0x6B] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(E));
    opcodeTable[0x6C] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(H));
    opcodeTable[0x6D] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(L));
    opcodeTable[0x6E] = std::bind(&CPU::LD_r8_HL, this, std::ref(L));
    opcodeTable[0x6F] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(A));

    opcodeTable[0x70] = std::bind(&CPU::LD_HL_r8, this, std::ref(B));
    opcodeTable[0x71] = std::bind(&CPU::LD_HL_r8, this, std::ref(C));
    opcodeTable[0x72] = std::bind(&CPU::LD_HL_r8, this, std::ref(D));
    opcodeTable[0x73] = std::bind(&CPU::LD_HL_r8, this, std::ref(E));
    opcodeTable[0x74] = std::bind(&CPU::LD_HL_r8, this, std::ref(H));
    opcodeTable[0x75] = std::bind(&CPU::LD_HL_r8, this, std::ref(L));
    opcodeTable[0x76] = std::bind(&CPU::NOP, this); //ToDo: Implement HALT
    opcodeTable[0x77] = std::bind(&CPU::LD_HL_r8, this, std::ref(A));

    opcodeTable[0x78] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(B));
    opcodeTable[0x79] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(C));
    opcodeTable[0x7A] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(D));
    opcodeTable[0x7B] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(E));
    opcodeTable[0x7C] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(H));
    opcodeTable[0x7D] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(L));
    opcodeTable[0x7E] = std::bind(&CPU::LD_r8_HL, this, std::ref(A));
    opcodeTable[0x7F] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(A));
    // Continue with more opcodes...
}

void CPU::executeOpcode()
{
    uint8_t opcode = fetchByte();
    opcodeTable[opcode]();
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

uint8_t CPU::fetchByte()
{
    return memory.readByte(PC++);
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

void CPU::LD_r8_r8(uint8_t &destinationRegister, uint8_t sourceRegister)
{
    destinationRegister = sourceRegister;
}

void CPU::LD_r8_HL(uint8_t &dest)
{
    dest = memory.readByte(HL());
}

void CPU::LD_HL_r8(uint8_t src)
{
    memory.writeByte(HL(), src);
}