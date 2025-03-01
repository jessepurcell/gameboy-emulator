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
  opcodeTable[0x7F] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(A));
  opcodeTable[0x80] = std::bind(&CPU::ADD_A_r8, this, std::ref(B));
  opcodeTable[0x81] = std::bind(&CPU::ADD_A_r8, this, std::ref(C));
  opcodeTable[0x82] = std::bind(&CPU::ADD_A_r8, this, std::ref(D));
  opcodeTable[0x83] = std::bind(&CPU::ADD_A_r8, this, std::ref(E));
  opcodeTable[0x84] = std::bind(&CPU::ADD_A_r8, this, std::ref(H));
  opcodeTable[0x85] = std::bind(&CPU::ADD_A_r8, this, std::ref(L));

  // opcodeTable[0x86] = std::bind(&CPU::ADD_A_r16, this, std::ref(HL()));
  opcodeTable[0x87] = std::bind(&CPU::ADD_A_r8, this, std::ref(A));
  opcodeTable[0x88] = std::bind(&CPU::ADC_A_r8, this, std::ref(B));
  opcodeTable[0x89] = std::bind(&CPU::ADC_A_r8, this, std::ref(C));
  opcodeTable[0x8A] = std::bind(&CPU::ADC_A_r8, this, std::ref(D));
  opcodeTable[0x8B] = std::bind(&CPU::ADC_A_r8, this, std::ref(E));
  opcodeTable[0x8C] = std::bind(&CPU::ADC_A_r8, this, std::ref(H));
  opcodeTable[0x8D] = std::bind(&CPU::ADC_A_r8, this, std::ref(L));
  // opcodeTable[0x8E] = std::bind(&CPU::ADC_A_r16, this, std::ref(HL()));
  opcodeTable[0x8F] = std::bind(&CPU::ADC_A_r8, this, std::ref(A));

  opcodeTable[0x90] = std::bind(&CPU::SUB_A_r8, this, std::ref(B));
  opcodeTable[0x91] = std::bind(&CPU::SUB_A_r8, this, std::ref(C));
  opcodeTable[0x92] = std::bind(&CPU::SUB_A_r8, this, std::ref(D));
  opcodeTable[0x93] = std::bind(&CPU::SUB_A_r8, this, std::ref(E));
  opcodeTable[0x94] = std::bind(&CPU::SUB_A_r8, this, std::ref(H));
  opcodeTable[0x95] = std::bind(&CPU::SUB_A_r8, this, std::ref(L));
  // opcodeTable[0x96] = std::bind(&CPU::SUB_A_r16, this, std::ref(HL()));
  opcodeTable[0x97] = std::bind(&CPU::SUB_A_r8, this, std::ref(A));

  opcodeTable[0x98] = std::bind(&CPU::SBC_A_r8, this, std::ref(B));
  opcodeTable[0x99] = std::bind(&CPU::SBC_A_r8, this, std::ref(C));
  opcodeTable[0x9A] = std::bind(&CPU::SBC_A_r8, this, std::ref(D));
  opcodeTable[0x9B] = std::bind(&CPU::SBC_A_r8, this, std::ref(E));
  opcodeTable[0x9C] = std::bind(&CPU::SBC_A_r8, this, std::ref(H));
  opcodeTable[0x9D] = std::bind(&CPU::SBC_A_r8, this, std::ref(L));
  // opcodeTable[0x9E] = std::bind(&CPU::SBC_A_r16, this, std::ref(HL()));
  opcodeTable[0x9F] = std::bind(&CPU::SBC_A_r8, this, std::ref(A));

  opcodeTable[0xA0] = std::bind(&CPU::AND_A_r8, this, std::ref(B));
  opcodeTable[0xA1] = std::bind(&CPU::AND_A_r8, this, std::ref(C));
  opcodeTable[0xA2] = std::bind(&CPU::AND_A_r8, this, std::ref(D));
  opcodeTable[0xA3] = std::bind(&CPU::AND_A_r8, this, std::ref(E));
  opcodeTable[0xA4] = std::bind(&CPU::AND_A_r8, this, std::ref(H));
  opcodeTable[0xA5] = std::bind(&CPU::AND_A_r8, this, std::ref(L));
  // opcodeTable[0xA6] = std::bind(&CPU::AND_A_r16, this, std::ref(HL()));
  opcodeTable[0xA7] = std::bind(&CPU::AND_A_r8, this, std::ref(A));

  opcodeTable[0xA8] = std::bind(&CPU::XOR_A_r8, this, std::ref(B));
  opcodeTable[0xA9] = std::bind(&CPU::XOR_A_r8, this, std::ref(C));
  opcodeTable[0xAA] = std::bind(&CPU::XOR_A_r8, this, std::ref(D));
  opcodeTable[0xAB] = std::bind(&CPU::XOR_A_r8, this, std::ref(E));
  opcodeTable[0xAC] = std::bind(&CPU::XOR_A_r8, this, std::ref(H));
  opcodeTable[0xAD] = std::bind(&CPU::XOR_A_r8, this, std::ref(L));
  // opcodeTable[0xAE] = std::bind(&CPU::XOR_A_r16, this, std::ref(HL()));
  opcodeTable[0xAF] = std::bind(&CPU::XOR_A_r8, this, std::ref(A));

  opcodeTable[0xB0] = std::bind(&CPU::OR_A_r8, this, std::ref(B));
  opcodeTable[0xB1] = std::bind(&CPU::OR_A_r8, this, std::ref(C));
  opcodeTable[0xB2] = std::bind(&CPU::OR_A_r8, this, std::ref(D));
  opcodeTable[0xB3] = std::bind(&CPU::OR_A_r8, this, std::ref(E));
  opcodeTable[0xB4] = std::bind(&CPU::OR_A_r8, this, std::ref(H));
  opcodeTable[0xB5] = std::bind(&CPU::OR_A_r8, this, std::ref(L));
  // opcodeTable[0xB6] = std::bind(&CPU::OR_A_r16, this, std::ref(HL()));
  opcodeTable[0xB7] = std::bind(&CPU::OR_A_r8, this, std::ref(A));

  opcodeTable[0xB8] = std::bind(&CPU::CP_A_r8, this, std::ref(B));
  opcodeTable[0xB9] = std::bind(&CPU::CP_A_r8, this, std::ref(C));
  opcodeTable[0xBA] = std::bind(&CPU::CP_A_r8, this, std::ref(D));
  opcodeTable[0xBB] = std::bind(&CPU::CP_A_r8, this, std::ref(E));
  opcodeTable[0xBC] = std::bind(&CPU::CP_A_r8, this, std::ref(H));
  opcodeTable[0xBD] = std::bind(&CPU::CP_A_r8, this, std::ref(L));
  // opcodeTable[0xBE] = std::bind(&CPU::CP_A_r16, this, std::ref(HL()));
  opcodeTable[0xBF] = std::bind(&CPU::CP_A_r8, this, std::ref(A));

  // opcodeTable[0xC0] = std::bind(&CPU::RET_cc, this, std::ref(Flag::NZ));
  opcodeTable[0xC1] = std::bind(&CPU::POP_r16, this, std::ref(BC()));
  // opcodeTable[0xC2] = std::bind(&CPU::JP_cc_n16, this, std::ref(Flag::NZ));
  opcodeTable[0xC3] = std::bind(&CPU::JP_n16, this);
  // opcodeTable[0xC4] = std::bind(&CPU::CALL_cc_n16, this, std::ref(Flag::NZ));
  opcodeTable[0xC5] = std::bind(&CPU::PUSH_r16, this, std::ref(BC()));
  opcodeTable[0xC6] = std::bind(&CPU::ADD_A_n8, this);
  // opcodeTable[0xC7] = std::bind(&CPU::RST, this, 0x00);
  // opcodeTable[0xC8] = std::bind(&CPU::RET_cc, this, std::ref(Flag::Z));
  opcodeTable[0xC9] = std::bind(&CPU::RET, this);
  // opcodeTable[0xCA] = std::bind(&CPU::JP_cc_n16, this, std::ref(Flag::Z));
  // opcodeTable[0xCB] = std::bind(&CPU::PREFIX, this);
  // opcodeTable[0xCC] = std::bind(&CPU::CALL_cc_n16, this, std::ref(Flag::Z));
  opcodeTable[0xCD] = std::bind(&CPU::CALL_n16, this);
  opcodeTable[0xCE] = std::bind(&CPU::ADC_A_n8, this);
  // opcodeTable[0xCF] = std::bind(&CPU::RST, this, 0x08);
  // opcodeTable[0xD0] = std::bind(&CPU::RET_cc, this, std::ref(Flag::NC));
  opcodeTable[0xD1] = std::bind(&CPU::POP_r16, this, std::ref(DE()));
  // opcodeTable[0xD2] = std::bind(&CPU::JP_cc_n16, this, std::ref(Flag::NC));
  // opcodeTable[0xD4] = std::bind(&CPU::CALL_cc_n16, this, std::ref(Flag::NC));
  opcodeTable[0xD5] = std::bind(&CPU::PUSH_r16, this, std::ref(DE()));
  opcodeTable[0xD6] = std::bind(&CPU::SUB_A_n8, this);
  // opcodeTable[0xD7] = std::bind(&CPU::RST, this, 0x10);
  // opcodeTable[0xD8] = std::bind(&CPU::RET_cc, this, std::ref(Flag::C));
  opcodeTable[0xD9] = std::bind(&CPU::RETI, this);
  // opcodeTable[0xDA] = std::bind(&CPU::JP_cc_n16, this, std::ref(Flag::C));
  // opcodeTable[0xDC] = std::bind(&CPU::CALL_cc_n16, this, std::ref(Flag::C));
  opcodeTable[0xDE] = std::bind(&CPU::SBC_A_n8, this);
  // opcodeTable[0xDF] = std::bind(&CPU::RST, this, 0x18);
  opcodeTable[0xE0] = std::bind(&CPU::LDH_n8_A, this);
  opcodeTable[0xE1] = std::bind(&CPU::POP_r16, this, std::ref(HL()));
  // opcodeTable[0xE2] = std::bind(&CPU::LDH_C_A, this);
  opcodeTable[0xE5] = std::bind(&CPU::PUSH_r16, this, std::ref(HL()));
  opcodeTable[0xE6] = std::bind(&CPU::AND_A_n8, this);
  // opcodeTable[0xE7] = std::bind(&CPU::RST, this, 0x20);
  opcodeTable[0xE8] = std::bind(&CPU::ADD_SP_n8, this);
  opcodeTable[0xE9] = std::bind(&CPU::JP_HL, this);
  opcodeTable[0xEA] = std::bind(&CPU::LD_n16_A, this);
  opcodeTable[0xEE] = std::bind(&CPU::XOR_A_n8, this);
  // opcodeTable[0xEF] = std::bind(&CPU::RST, this, 0x28);
  opcodeTable[0xF0] = std::bind(&CPU::LDH_A_n8, this);
  // opcodeTable[0xF1] = std::bind(&CPU::POP_r16, this, std::ref(AF()));
  // opcodeTable[0xF2] = std::bind(&CPU::LDH_A_C, this);
  opcodeTable[0xF3] = std::bind(&CPU::DI, this);
  // opcodeTable[0xF5] = std::bind(&CPU::PUSH_r16, this, std::ref(AF()));
  opcodeTable[0xF6] = std::bind(&CPU::OR_A_n8, this);
  // opcodeTable[0xF7] = std::bind(&CPU::RST, this, 0x30);
  opcodeTable[0xF8] = std::bind(&CPU::LD_HL_SP_n8, this);
  opcodeTable[0xF9] = std::bind(&CPU::LD_SP_HL, this);
  opcodeTable[0xFA] = std::bind(&CPU::LD_A_n16, this);
  opcodeTable[0xFB] = std::bind(&CPU::EI, this);
  opcodeTable[0xFE] = std::bind(&CPU::CP_A_n8, this);
  // opcodeTable[0xFF] = std::bind(&CPU::RST, this, 0x38);
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