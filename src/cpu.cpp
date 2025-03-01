#include "../include/cpu.hpp"

#include <stdio.h>

#include <algorithm>
#include <array>

CPU::CPU(Memory &memory) : memory(memory) {
  // Default all opcodes to NOP to prevent crashes
  opcodeTable.fill([&]() { NOP(); });

  // Map primary opcodes
  opcodeTable[0x00] = std::bind(&CPU::NOP, this);
  opcodeTable[0x01] = std::bind(&CPU::LD_r16_n16, this, std::ref(BC()));
  // opcodeTable[0x02] = std::bind(&CPU::LD_HL_r8, this, std::ref(A));
  opcodeTable[0x03] = std::bind(&CPU::INC_r16, this, std::ref(BC()));
  // opcodeTable[0x04] = std::bind(&CPU::INC_r8, this, std::ref(B));
  // opcodeTable[0x05] = std::bind(&CPU::DEC_r8, this, std::ref(B));

  opcodeTable[0x06] = std::bind(&CPU::LD_r8_n8, this, std::ref(B));
  // opcodeTable[0x07] = std::bind(&CPU::RLCA, this);
  // opcodeTable[0x08] = std::bind(&CPU::LD_n16_SP, this);
  opcodeTable[0x09] = std::bind(&CPU::ADD_HL_r16, this, std::ref(BC()));

  opcodeTable[0x0A] = std::bind(&CPU::LD_A_r16, this, std::ref(BC()));
  // opcodeTable[0x0B] = std::bind(&CPU::DEC_r16, this, std::ref(BC()));
  // opcodeTable[0x0C] = std::bind(&CPU::INC_r8, this, std::ref(C));
  // opcodeTable[0x0D] = std::bind(&CPU::DEC_r8, this, std::ref(C));
  opcodeTable[0x0E] = std::bind(&CPU::LD_r8_n8, this, std::ref(C));
  // opcodeTable[0x0F] = std::bind(&CPU::RRCA, this);

  opcodeTable[0x11] = std::bind(&CPU::LD_r16_n16, this, std::ref(DE()));
  // opcodeTable[0x12] = std::bind(&CPU::LD_HL_r8, this, std::ref(A));
  opcodeTable[0x13] = std::bind(&CPU::INC_r16, this, std::ref(DE()));

  opcodeTable[0x16] = std::bind(&CPU::LD_r8_n8, this, std::ref(D));
  // opcodeTable[0x17] = std::bind(&CPU::RLA, this);
  // opcodeTable[0x18] = std::bind(&CPU::JR, this, std::ref(Flag::Z), true);
  opcodeTable[0x19] = std::bind(&CPU::ADD_HL_r16, this, std::ref(DE()));
  opcodeTable[0x1A] = std::bind(&CPU::LD_A_r16, this, std::ref(DE()));
  opcodeTable[0x1E] = std::bind(&CPU::LD_r8_n8, this, std::ref(E));

  opcodeTable[0x21] = std::bind(&CPU::LD_r16_n16, this, std::ref(HL()));
  // opcodeTable[0x22] = std::bind(&CPU::LD_r16_r8, this, std::ref(HL()),
  // std::ref(A));
  opcodeTable[0x23] = std::bind(&CPU::INC_r16, this, std::ref(HL()));
  // opcodeTable[0x24] = std::bind(&CPU::INC_r8, this, std::ref(H));
  // opcodeTable[0x25] = std::bind(&CPU::DEC_r8, this, std::ref(H));
  opcodeTable[0x26] = std::bind(&CPU::LD_r8_n8, this, std::ref(H));
  // opcodeTable[0x27] = std::bind(&CPU::DAA, this);
  // opcodeTable[0x28] = std::bind(&CPU::JR, this, std::ref(Flag::Z), false);
  opcodeTable[0x29] = std::bind(&CPU::ADD_HL_r16, this, std::ref(HL()));
  // opcodeTable[0x2A] = std::bind(&CPU::LD_r8_r16, this, std::ref(A),
  // std::ref(HL())); opcodeTable[0x2B] = std::bind(&CPU::DEC_r16, this,
  // std::ref(HL())); opcodeTable[0x2C] = std::bind(&CPU::INC_r8, this,
  // std::ref(L)); opcodeTable[0x2D] = std::bind(&CPU::DEC_r8, this,
  // std::ref(L));
  opcodeTable[0x2E] = std::bind(&CPU::LD_r8_n8, this, std::ref(L));

  opcodeTable[0x31] = std::bind(&CPU::LD_r16_n16, this, std::ref(SP));
  // opcodeTable[0x32] = std::bind(&CPU::LD_r16_r8, this, std::ref(HL()),
  // std::ref(A)); opcodeTable[0x36] = std::bind(&CPU::LD_r16_n8, this,
  // std::ref(HL()));
  opcodeTable[0x39] = std::bind(&CPU::ADD_HL_r16, this, std::ref(SP));
  opcodeTable[0x3A] = std::bind(&CPU::LD_A_r16, this, std::ref(HL()));
  // opcodeTable[0x3D] = std::bind(&CPU::DEC_r8, this, std::ref(A));
  opcodeTable[0x3E] = std::bind(&CPU::LD_r8_n8, this, std::ref(A));

  opcodeTable[0x40] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(B));
  opcodeTable[0x41] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(C));
  opcodeTable[0x42] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(D));
  opcodeTable[0x43] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(E));
  opcodeTable[0x44] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(H));
  opcodeTable[0x45] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(L));
  // opcodeTable[0x46] = std::bind(&CPU::LD_r8_r16, this, std::ref(B),
  // std::ref(HL()));
  opcodeTable[0x47] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(A));

  opcodeTable[0x48] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(B));
  opcodeTable[0x49] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(C));
  opcodeTable[0x4A] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(D));
  opcodeTable[0x4B] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(E));
  opcodeTable[0x4C] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(H));
  opcodeTable[0x4D] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(L));
  // opcodeTable[0x4E] = std::bind(&CPU::LD_r8_r16, this, std::ref(C),
  // std::ref(HL()));
  opcodeTable[0x4F] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(A));

  opcodeTable[0x50] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(B));
  opcodeTable[0x51] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(C));
  opcodeTable[0x52] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(D));
  opcodeTable[0x53] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(E));
  opcodeTable[0x54] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(H));
  opcodeTable[0x55] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(L));
  // opcodeTable[0x56] = std::bind(&CPU::LD_r8_r16, this, std::ref(D),
  // std::ref(HL()));
  opcodeTable[0x57] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(A));

  opcodeTable[0x58] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(B));
  opcodeTable[0x59] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(C));
  opcodeTable[0x5A] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(D));
  opcodeTable[0x5B] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(E));
  opcodeTable[0x5C] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(H));
  opcodeTable[0x5D] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(L));
  // opcodeTable[0x5E] = std::bind(&CPU::LD_r8_r16, this, std::ref(E),
  // std::ref(HL()));
  opcodeTable[0x5F] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(A));

  opcodeTable[0x60] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(B));
  opcodeTable[0x61] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(C));
  opcodeTable[0x62] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(D));
  opcodeTable[0x63] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(E));
  opcodeTable[0x64] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(H));
  opcodeTable[0x65] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(L));
  // opcodeTable[0x66] = std::bind(&CPU::LD_r8_r16, this, std::ref(H),
  // std::ref(HL()));
  opcodeTable[0x67] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(A));

  opcodeTable[0x68] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(B));
  opcodeTable[0x69] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(C));
  opcodeTable[0x6A] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(D));
  opcodeTable[0x6B] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(E));
  opcodeTable[0x6C] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(H));
  opcodeTable[0x6D] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(L));
  // opcodeTable[0x6E] = std::bind(&CPU::LD_r8_r16, this, std::ref(L),
  // std::ref(HL()));
  opcodeTable[0x6F] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(A));

  // opcodeTable[0x70] = std::bind(&CPU::LD_r16_r8, this, std::ref(HL()),
  // std::ref(B)); opcodeTable[0x71] = std::bind(&CPU::LD_r16_r8, this,
  // std::ref(HL()),  std::ref(C)); opcodeTable[0x72] =
  // std::bind(&CPU::LD_r16_r8, this, std::ref(HL()),  std::ref(D));
  // opcodeTable[0x73] = std::bind(&CPU::LD_r16_r8, this, std::ref(HL()),
  // std::ref(E)); opcodeTable[0x74] = std::bind(&CPU::LD_r16_r8, this,
  // std::ref(HL()),  std::ref(H)); opcodeTable[0x75] =
  // std::bind(&CPU::LD_r16_r8, this, std::ref(HL()),  std::ref(L));
  // opcodeTable[0x76] = std::bind(&CPU::NOP, this); //ToDo: Implement HALT
  // opcodeTable[0x77] = std::bind(&CPU::LD_r16_r8, this, std::ref(HL()),
  // std::ref(A));

  opcodeTable[0x78] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(B));
  opcodeTable[0x79] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(C));
  opcodeTable[0x7A] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(D));
  opcodeTable[0x7B] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(E));
  opcodeTable[0x7C] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(H));
  opcodeTable[0x7D] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(L));
  // opcodeTable[0x7E] = std::bind(&CPU::LD_r8_r16, this, std::ref(A),
  // std::ref(HL()));
  opcodeTable[0x7F] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(A));
  // Continue with more opcodes...
}

void CPU::executeOpcode() {
  uint8_t opcode = fetchByte();
  opcodeTable[opcode]();
}

void CPU::NOP() { /* No operation */ }

uint8_t CPU::fetchByte() { return memory.readByte(PC++); }

uint16_t CPU::fetchWord() {
  uint16_t lo = fetchByte();
  uint16_t hi = fetchByte();
  return (hi << 8) | lo;
}

void CPU::LD_r8_r8(uint8_t &destinationRegister, uint8_t sourceRegister) {
  destinationRegister = sourceRegister;
}

void CPU::LD_r8_n8(uint8_t &destinationRegister) {
  destinationRegister = fetchByte();
}

void CPU::LD_r16_n16(uint16_t &destination) { destination = fetchWord(); }

void CPU::LD_r16_A(uint16_t &registerPair) {
  memory.writeByte(registerPair, A);
}

void CPU::LD_A_r16(uint16_t &registerPair) {
  A = memory.readByte(registerPair);
}

void CPU::LD_n16_SP() { memory.writeWord(fetchWord(), SP); }

void CPU::INC_r16(uint16_t &registerPair) { registerPair++; }

void CPU::DEC_r16(uint16_t &registerPair) { registerPair--; }

void CPU::ADD_HL_r16(uint16_t &registerPair) {
  uint16_t result = (HL() + registerPair);
  bool halfCarry = (HL() & 0x0FFF) + (registerPair & 0x0FFF) > 0x0FFF;
  bool carry = result < HL();

  resetFlags();
  setHalfCarryFlag(halfCarry);
  setCarryFlag(carry);

  //   printf("0x%016X\n", result);
  //   printf("0x%016X\n", halfCarry);
  //   printf("0x%016X\n", carry);
  //   printf("0x%016X\n", F);
  HL() = result & 0xFFFF;
}