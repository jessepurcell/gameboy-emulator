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
  opcodeTable[0x02] = std::bind(&CPU::LD_HL_r8, this, std::ref(A));
  opcodeTable[0x03] = std::bind(&CPU::INC_r16, this, std::ref(BC()));
  opcodeTable[0x04] = std::bind(&CPU::INC_r8, this, std::ref(B));
  opcodeTable[0x05] = std::bind(&CPU::DEC_r8, this, std::ref(B));

  opcodeTable[0x06] = std::bind(&CPU::LD_r8_n8, this, std::ref(B));
  opcodeTable[0x07] = std::bind(&CPU::RLCA, this);
  opcodeTable[0x08] = std::bind(&CPU::LD_n16_SP, this);
  opcodeTable[0x09] = std::bind(&CPU::ADD_HL_r16, this, std::ref(BC()));

  opcodeTable[0x0A] = std::bind(&CPU::LD_A_r16, this, std::ref(BC()));
  opcodeTable[0x0B] = std::bind(&CPU::DEC_r16, this, std::ref(BC()));
  opcodeTable[0x0C] = std::bind(&CPU::INC_r8, this, std::ref(C));
  opcodeTable[0x0D] = std::bind(&CPU::DEC_r8, this, std::ref(C));
  opcodeTable[0x0E] = std::bind(&CPU::LD_r8_n8, this, std::ref(C));
  opcodeTable[0x0F] = std::bind(&CPU::RRCA, this);

  opcodeTable[0x11] = std::bind(&CPU::LD_r16_n16, this, std::ref(DE()));
  opcodeTable[0x12] = std::bind(&CPU::LD_HL_r8, this, std::ref(A));
  opcodeTable[0x13] = std::bind(&CPU::INC_r16, this, std::ref(DE()));

  opcodeTable[0x16] = std::bind(&CPU::LD_r8_n8, this, std::ref(D));
  opcodeTable[0x17] = std::bind(&CPU::RLA, this);
  opcodeTable[0x18] = std::bind(&CPU::JR_n8, this);
  opcodeTable[0x19] = std::bind(&CPU::ADD_HL_r16, this, std::ref(DE()));
  opcodeTable[0x1A] = std::bind(&CPU::LD_A_r16, this, std::ref(DE()));
  opcodeTable[0x1E] = std::bind(&CPU::LD_r8_n8, this, std::ref(E));
  opcodeTable[0x1F] = std::bind(&CPU::RRA, this);

  opcodeTable[0x21] = std::bind(&CPU::LD_r16_n16, this, std::ref(HL()));
  opcodeTable[0x22] =
      std::bind(&CPU::LD_r16_r8, this, std::ref(HL()), std::ref(A));
  opcodeTable[0x23] = std::bind(&CPU::INC_r16, this, std::ref(HL()));
  opcodeTable[0x24] = std::bind(&CPU::INC_r8, this, std::ref(H));
  opcodeTable[0x25] = std::bind(&CPU::DEC_r8, this, std::ref(H));
  opcodeTable[0x26] = std::bind(&CPU::LD_r8_n8, this, std::ref(H));
  opcodeTable[0x27] = std::bind(&CPU::DAA, this);
  opcodeTable[0x28] = std::bind(&CPU::JR_con_n8, this, true);
  opcodeTable[0x29] = std::bind(&CPU::ADD_HL_r16, this, std::ref(HL()));
  opcodeTable[0x2A] = std::bind(&CPU::LD_A_r16, this, std::ref(HL()));
  opcodeTable[0x2B] = std::bind(&CPU::DEC_r16, this, std::ref(HL()));
  opcodeTable[0x2C] = std::bind(&CPU::INC_r8, this, std::ref(L));
  opcodeTable[0x2D] = std::bind(&CPU::DEC_r8, this, std::ref(L));
  opcodeTable[0x2E] = std::bind(&CPU::LD_r8_n8, this, std::ref(L));
  opcodeTable[0x2F] = std::bind(&CPU::CPL, this);

  opcodeTable[0x31] = std::bind(&CPU::LD_r16_n16, this, std::ref(SP));
  opcodeTable[0x32] =
      std::bind(&CPU::LD_r16_r8, this, std::ref(HL()), std::ref(A));
  opcodeTable[0x33] = std::bind(&CPU::INC_r16, this, std::ref(SP));
  opcodeTable[0x34] = std::bind(&CPU::INC_r16, this, std::ref(HL()));
  opcodeTable[0x35] = std::bind(&CPU::DEC_r16, this, std::ref(HL()));
  opcodeTable[0x36] = std::bind(&CPU::LD_r16_n8, this, std::ref(HL()));
  opcodeTable[0x37] = std::bind(&CPU::SCF, this);
  opcodeTable[0x38] = std::bind(&CPU::JR_con_n8, this, false);
  opcodeTable[0x39] = std::bind(&CPU::ADD_HL_r16, this, std::ref(SP));
  opcodeTable[0x3A] = std::bind(&CPU::LD_A_r16, this, std::ref(HL()));
  opcodeTable[0x3D] = std::bind(&CPU::DEC_r8, this, std::ref(A));
  opcodeTable[0x3E] = std::bind(&CPU::LD_r8_n8, this, std::ref(A));
  opcodeTable[0x3F] = std::bind(&CPU::CCF, this);

  opcodeTable[0x40] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(B));
  opcodeTable[0x41] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(C));
  opcodeTable[0x42] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(D));
  opcodeTable[0x43] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(E));
  opcodeTable[0x44] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(H));
  opcodeTable[0x45] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(L));
  opcodeTable[0x46] =
      std::bind(&CPU::LD_r8_r16, this, std::ref(B), std::ref(HL()));
  opcodeTable[0x47] = std::bind(&CPU::LD_r8_r8, this, std::ref(B), std::ref(A));

  opcodeTable[0x48] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(B));
  opcodeTable[0x49] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(C));
  opcodeTable[0x4A] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(D));
  opcodeTable[0x4B] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(E));
  opcodeTable[0x4C] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(H));
  opcodeTable[0x4D] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(L));
  opcodeTable[0x4E] =
      std::bind(&CPU::LD_r8_r16, this, std::ref(C), std::ref(HL()));
  opcodeTable[0x4F] = std::bind(&CPU::LD_r8_r8, this, std::ref(C), std::ref(A));

  opcodeTable[0x50] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(B));
  opcodeTable[0x51] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(C));
  opcodeTable[0x52] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(D));
  opcodeTable[0x53] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(E));
  opcodeTable[0x54] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(H));
  opcodeTable[0x55] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(L));
  opcodeTable[0x56] =
      std::bind(&CPU::LD_r8_r16, this, std::ref(D), std::ref(HL()));
  opcodeTable[0x57] = std::bind(&CPU::LD_r8_r8, this, std::ref(D), std::ref(A));

  opcodeTable[0x58] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(B));
  opcodeTable[0x59] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(C));
  opcodeTable[0x5A] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(D));
  opcodeTable[0x5B] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(E));
  opcodeTable[0x5C] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(H));
  opcodeTable[0x5D] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(L));
  opcodeTable[0x5E] =
      std::bind(&CPU::LD_r8_r16, this, std::ref(E), std::ref(HL()));
  opcodeTable[0x5F] = std::bind(&CPU::LD_r8_r8, this, std::ref(E), std::ref(A));

  opcodeTable[0x60] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(B));
  opcodeTable[0x61] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(C));
  opcodeTable[0x62] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(D));
  opcodeTable[0x63] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(E));
  opcodeTable[0x64] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(H));
  opcodeTable[0x65] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(L));
  opcodeTable[0x66] =
      std::bind(&CPU::LD_r8_r16, this, std::ref(H), std::ref(HL()));
  opcodeTable[0x67] = std::bind(&CPU::LD_r8_r8, this, std::ref(H), std::ref(A));

  opcodeTable[0x68] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(B));
  opcodeTable[0x69] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(C));
  opcodeTable[0x6A] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(D));
  opcodeTable[0x6B] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(E));
  opcodeTable[0x6C] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(H));
  opcodeTable[0x6D] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(L));
  opcodeTable[0x6E] =
      std::bind(&CPU::LD_r8_r16, this, std::ref(L), std::ref(HL()));
  opcodeTable[0x6F] = std::bind(&CPU::LD_r8_r8, this, std::ref(L), std::ref(A));

  opcodeTable[0x70] =
      std::bind(&CPU::LD_r16_r8, this, std::ref(HL()), std::ref(B));
  opcodeTable[0x71] =
      std::bind(&CPU::LD_r16_r8, this, std::ref(HL()), std::ref(C));
  opcodeTable[0x72] =
      std::bind(&CPU::LD_r16_r8, this, std::ref(HL()), std::ref(D));
  opcodeTable[0x73] =
      std::bind(&CPU::LD_r16_r8, this, std::ref(HL()), std::ref(E));
  opcodeTable[0x74] =
      std::bind(&CPU::LD_r16_r8, this, std::ref(HL()), std::ref(H));
  opcodeTable[0x75] =
      std::bind(&CPU::LD_r16_r8, this, std::ref(HL()), std::ref(L));
  opcodeTable[0x76] = std::bind(&CPU::HALT, this);  // ToDo: Implement HALT
  opcodeTable[0x77] =
      std::bind(&CPU::LD_r16_r8, this, std::ref(HL()), std::ref(A));

  opcodeTable[0x78] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(B));
  opcodeTable[0x79] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(C));
  opcodeTable[0x7A] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(D));
  opcodeTable[0x7B] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(E));
  opcodeTable[0x7C] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(H));
  opcodeTable[0x7D] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(L));
  opcodeTable[0x7E] =
      std::bind(&CPU::LD_r8_r16, this, std::ref(A), std::ref(HL()));
  opcodeTable[0x7F] = std::bind(&CPU::LD_r8_r8, this, std::ref(A), std::ref(A));
  opcodeTable[0x80] = std::bind(&CPU::ADD_A_r8, this, std::ref(B));
  opcodeTable[0x81] = std::bind(&CPU::ADD_A_r8, this, std::ref(C));
  opcodeTable[0x82] = std::bind(&CPU::ADD_A_r8, this, std::ref(D));
  opcodeTable[0x83] = std::bind(&CPU::ADD_A_r8, this, std::ref(E));
  opcodeTable[0x84] = std::bind(&CPU::ADD_A_r8, this, std::ref(H));
  opcodeTable[0x85] = std::bind(&CPU::ADD_A_r8, this, std::ref(L));

  opcodeTable[0x86] = std::bind(&CPU::ADD_A_r16, this, std::ref(HL()));
  opcodeTable[0x87] = std::bind(&CPU::ADD_A_r8, this, std::ref(A));
  opcodeTable[0x88] = std::bind(&CPU::ADC_A_r8, this, std::ref(B));
  opcodeTable[0x89] = std::bind(&CPU::ADC_A_r8, this, std::ref(C));
  opcodeTable[0x8A] = std::bind(&CPU::ADC_A_r8, this, std::ref(D));
  opcodeTable[0x8B] = std::bind(&CPU::ADC_A_r8, this, std::ref(E));
  opcodeTable[0x8C] = std::bind(&CPU::ADC_A_r8, this, std::ref(H));
  opcodeTable[0x8D] = std::bind(&CPU::ADC_A_r8, this, std::ref(L));
  opcodeTable[0x8E] = std::bind(&CPU::ADC_A_r16, this, std::ref(HL()));
  opcodeTable[0x8F] = std::bind(&CPU::ADC_A_r8, this, std::ref(A));

  opcodeTable[0x90] = std::bind(&CPU::SUB_A_r8, this, std::ref(B));
  opcodeTable[0x91] = std::bind(&CPU::SUB_A_r8, this, std::ref(C));
  opcodeTable[0x92] = std::bind(&CPU::SUB_A_r8, this, std::ref(D));
  opcodeTable[0x93] = std::bind(&CPU::SUB_A_r8, this, std::ref(E));
  opcodeTable[0x94] = std::bind(&CPU::SUB_A_r8, this, std::ref(H));
  opcodeTable[0x95] = std::bind(&CPU::SUB_A_r8, this, std::ref(L));
  opcodeTable[0x96] = std::bind(&CPU::SUB_A_r16, this, std::ref(HL()));
  opcodeTable[0x97] = std::bind(&CPU::SUB_A_r8, this, std::ref(A));

  opcodeTable[0x98] = std::bind(&CPU::SBC_A_r8, this, std::ref(B));
  opcodeTable[0x99] = std::bind(&CPU::SBC_A_r8, this, std::ref(C));
  opcodeTable[0x9A] = std::bind(&CPU::SBC_A_r8, this, std::ref(D));
  opcodeTable[0x9B] = std::bind(&CPU::SBC_A_r8, this, std::ref(E));
  opcodeTable[0x9C] = std::bind(&CPU::SBC_A_r8, this, std::ref(H));
  opcodeTable[0x9D] = std::bind(&CPU::SBC_A_r8, this, std::ref(L));
  opcodeTable[0x9E] = std::bind(&CPU::SBC_A_r16, this, std::ref(HL()));
  opcodeTable[0x9F] = std::bind(&CPU::SBC_A_r8, this, std::ref(A));

  opcodeTable[0xA0] = std::bind(&CPU::AND_A_r8, this, std::ref(B));
  opcodeTable[0xA1] = std::bind(&CPU::AND_A_r8, this, std::ref(C));
  opcodeTable[0xA2] = std::bind(&CPU::AND_A_r8, this, std::ref(D));
  opcodeTable[0xA3] = std::bind(&CPU::AND_A_r8, this, std::ref(E));
  opcodeTable[0xA4] = std::bind(&CPU::AND_A_r8, this, std::ref(H));
  opcodeTable[0xA5] = std::bind(&CPU::AND_A_r8, this, std::ref(L));
  opcodeTable[0xA6] = std::bind(&CPU::AND_A_r16, this, std::ref(HL()));
  opcodeTable[0xA7] = std::bind(&CPU::AND_A_r8, this, std::ref(A));

  opcodeTable[0xA8] = std::bind(&CPU::XOR_A_r8, this, std::ref(B));
  opcodeTable[0xA9] = std::bind(&CPU::XOR_A_r8, this, std::ref(C));
  opcodeTable[0xAA] = std::bind(&CPU::XOR_A_r8, this, std::ref(D));
  opcodeTable[0xAB] = std::bind(&CPU::XOR_A_r8, this, std::ref(E));
  opcodeTable[0xAC] = std::bind(&CPU::XOR_A_r8, this, std::ref(H));
  opcodeTable[0xAD] = std::bind(&CPU::XOR_A_r8, this, std::ref(L));
  opcodeTable[0xAE] = std::bind(&CPU::XOR_A_r16, this, std::ref(HL()));
  opcodeTable[0xAF] = std::bind(&CPU::XOR_A_r8, this, std::ref(A));

  opcodeTable[0xB0] = std::bind(&CPU::OR_A_r8, this, std::ref(B));
  opcodeTable[0xB1] = std::bind(&CPU::OR_A_r8, this, std::ref(C));
  opcodeTable[0xB2] = std::bind(&CPU::OR_A_r8, this, std::ref(D));
  opcodeTable[0xB3] = std::bind(&CPU::OR_A_r8, this, std::ref(E));
  opcodeTable[0xB4] = std::bind(&CPU::OR_A_r8, this, std::ref(H));
  opcodeTable[0xB5] = std::bind(&CPU::OR_A_r8, this, std::ref(L));
  opcodeTable[0xB6] = std::bind(&CPU::OR_A_r16, this, std::ref(HL()));
  opcodeTable[0xB7] = std::bind(&CPU::OR_A_r8, this, std::ref(A));

  opcodeTable[0xB8] = std::bind(&CPU::CP_A_r8, this, std::ref(B));
  opcodeTable[0xB9] = std::bind(&CPU::CP_A_r8, this, std::ref(C));
  opcodeTable[0xBA] = std::bind(&CPU::CP_A_r8, this, std::ref(D));
  opcodeTable[0xBB] = std::bind(&CPU::CP_A_r8, this, std::ref(E));
  opcodeTable[0xBC] = std::bind(&CPU::CP_A_r8, this, std::ref(H));
  opcodeTable[0xBD] = std::bind(&CPU::CP_A_r8, this, std::ref(L));
  opcodeTable[0xBE] = std::bind(&CPU::CP_A_r16, this, std::ref(HL()));
  opcodeTable[0xBF] = std::bind(&CPU::CP_A_r8, this, std::ref(A));

  opcodeTable[0xC0] = std::bind(&CPU::RET_con, this, false);
  opcodeTable[0xC1] = std::bind(&CPU::POP_r16, this, std::ref(BC()));
  opcodeTable[0xC2] = std::bind(&CPU::JP_con_n16, this, false);
  opcodeTable[0xC3] = std::bind(&CPU::JP_n16, this);
  opcodeTable[0xC4] =
      std::bind(&CPU::CALL_con_n16, this, getSubtractFlag() | getZeroFlag());
  opcodeTable[0xC5] = std::bind(&CPU::PUSH_r16, this, std::ref(BC()));
  opcodeTable[0xC6] = std::bind(&CPU::ADD_A_n8, this);
  opcodeTable[0xC7] = std::bind(&CPU::RST, this, 0x00);
  opcodeTable[0xC8] = std::bind(&CPU::RET_con, this, false);
  opcodeTable[0xC9] = std::bind(&CPU::RET, this);
  opcodeTable[0xCA] = std::bind(&CPU::JP_con_n16, this, false);
  // opcodeTable[0xCB] = std::bind(&CPU::PREFIX, this);
  opcodeTable[0xCC] = std::bind(&CPU::CALL_con_n16, this, getZeroFlag());
  opcodeTable[0xCD] = std::bind(&CPU::CALL_n16, this);
  opcodeTable[0xCE] = std::bind(&CPU::ADC_A_n8, this);
  opcodeTable[0xCF] = std::bind(&CPU::RST, this, 0x08);
  opcodeTable[0xD0] = std::bind(&CPU::RET_con, this, false);
  opcodeTable[0xD1] = std::bind(&CPU::POP_r16, this, std::ref(DE()));
  opcodeTable[0xD2] = std::bind(&CPU::JP_con_n16, this, false);
  opcodeTable[0xD4] =
      std::bind(&CPU::CALL_con_n16, this, getSubtractFlag() | getCarryFlag());
  opcodeTable[0xD5] = std::bind(&CPU::PUSH_r16, this, std::ref(DE()));
  opcodeTable[0xD6] = std::bind(&CPU::SUB_A_n8, this);
  opcodeTable[0xD7] = std::bind(&CPU::RST, this, 0x10);
  opcodeTable[0xD8] = std::bind(&CPU::RET_con, this, false);
  opcodeTable[0xD9] = std::bind(&CPU::RETI, this);
  opcodeTable[0xDA] = std::bind(&CPU::JP_con_n16, this, getCarryFlag());
  opcodeTable[0xDC] = std::bind(&CPU::CALL_con_n16, this, getCarryFlag());
  opcodeTable[0xDE] = std::bind(&CPU::SBC_A_n8, this);
  opcodeTable[0xDF] = std::bind(&CPU::RST, this, 0x18);
  opcodeTable[0xE0] = std::bind(&CPU::LDH_n8_A, this);
  opcodeTable[0xE1] = std::bind(&CPU::POP_r16, this, std::ref(HL()));
  opcodeTable[0xE2] = std::bind(&CPU::LDH_C_A, this);
  opcodeTable[0xE5] = std::bind(&CPU::PUSH_r16, this, std::ref(HL()));
  opcodeTable[0xE6] = std::bind(&CPU::AND_A_n8, this);
  opcodeTable[0xE7] = std::bind(&CPU::RST, this, 0x20);
  opcodeTable[0xE8] = std::bind(&CPU::ADD_SP_n8, this);
  opcodeTable[0xE9] = std::bind(&CPU::JP_HL, this);
  opcodeTable[0xEA] = std::bind(&CPU::LD_n16_A, this);
  opcodeTable[0xEE] = std::bind(&CPU::XOR_A_n8, this);
  opcodeTable[0xEF] = std::bind(&CPU::RST, this, 0x28);
  opcodeTable[0xF0] = std::bind(&CPU::LDH_A_n8, this);
  opcodeTable[0xF1] = std::bind(&CPU::POP_r16, this, std::ref(AF()));
  opcodeTable[0xF2] = std::bind(&CPU::LDH_A_r8, this, std::ref(C));
  opcodeTable[0xF3] = std::bind(&CPU::DI, this);

  // opcodeTable[0xF4] = std::bind(&CPU::CALL_con_n16, this, false);
  opcodeTable[0xF5] = std::bind(&CPU::PUSH_r16, this, std::ref(AF()));
  opcodeTable[0xF6] = std::bind(&CPU::OR_A_n8, this);
  opcodeTable[0xF7] = std::bind(&CPU::RST, this, 0x30);
  opcodeTable[0xF8] = std::bind(&CPU::LD_HL_SP_n8, this);
  opcodeTable[0xF9] = std::bind(&CPU::LD_SP_HL, this);
  opcodeTable[0xFA] = std::bind(&CPU::LD_A_n16, this);
  opcodeTable[0xFB] = std::bind(&CPU::EI, this);
  opcodeTable[0xFE] = std::bind(&CPU::CP_A_n8, this);
  opcodeTable[0xFF] = std::bind(&CPU::RST, this, 0x38);
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

void CPU::INC_r8(uint8_t &registerPair) {
  bool halfCarry = (registerPair & 0x0F) == 0x0F;
  registerPair++;
  setZeroFlag(registerPair == 0);
  setSubtractFlag(false);
  setHalfCarryFlag(halfCarry);
}

void CPU::DEC_r8(uint8_t &registerPair) {
  bool halfCarry = (registerPair & 0x0F) == 0x00;
  registerPair--;
  setZeroFlag(registerPair == 0);
  setSubtractFlag(true);
  setHalfCarryFlag(halfCarry);
}

void CPU::ADD_A_r8(uint8_t value) {
  bool halfCarry = (A & 0x0F) + (value & 0x0F) > 0x0F;
  bool carry = A + value > 0xFF;

  resetFlags();
  setZeroFlag((A + value) == 0);
  setSubtractFlag(false);
  setHalfCarryFlag(halfCarry);
  setCarryFlag(carry);

  A += value;
}

void CPU::ADD_A_n8() {
  uint8_t value = fetchByte();
  ADD_A_r8(value);
}

void CPU::ADC_A_r8(uint8_t value) {
  uint8_t carry = getCarryFlag() ? 1 : 0;
  bool halfCarry = (A & 0x0F) + (value & 0x0F) + carry > 0x0F;
  bool carryFlag = A + value + carry > 0xFF;

  resetFlags();
  setZeroFlag((A + value + carry) == 0);
  setSubtractFlag(false);
  setHalfCarryFlag(halfCarry);
  setCarryFlag(carryFlag);

  A += value + carry;
}

void CPU::ADC_A_n8() {
  uint8_t value = fetchByte();
  ADC_A_r8(value);
}

void CPU::SUB_A_r8(uint8_t value) {
  bool halfCarry = (A & 0x0F) < (value & 0x0F);
  bool carry = A < value;

  resetFlags();
  setZeroFlag(A == value);
  setSubtractFlag(true);
  setHalfCarryFlag(halfCarry);
  setCarryFlag(carry);

  A -= value;
}

void CPU::SUB_A_n8() {
  uint8_t value = fetchByte();
  SUB_A_r8(value);
}

void CPU::SBC_A_r8(uint8_t value) {
  uint8_t carry = getCarryFlag() ? 1 : 0;
  bool halfCarry = (A & 0x0F) < (value & 0x0F) + carry;
  bool carryFlag = A < value + carry;

  resetFlags();
  setZeroFlag(A == value + carry);
  setSubtractFlag(true);
  setHalfCarryFlag(halfCarry);
  setCarryFlag(carryFlag);

  A -= value + carry;
}

void CPU::SBC_A_n8() {
  uint8_t value = fetchByte();
  SBC_A_r8(value);
}

void CPU::AND_A_r8(uint8_t value) {
  A &= value;
  resetFlags();
  setZeroFlag(A == 0);
  setSubtractFlag(false);
  setHalfCarryFlag(true);
  setCarryFlag(false);
}

void CPU::AND_A_n8() {
  uint8_t value = fetchByte();
  AND_A_r8(value);
}

void CPU::XOR_A_r8(uint8_t value) {
  A ^= value;
  resetFlags();
  setZeroFlag(A == 0);
}

void CPU::XOR_A_n8() {
  uint8_t value = fetchByte();
  XOR_A_r8(value);
}

void CPU::OR_A_r8(uint8_t value) {
  A |= value;
  resetFlags();
  setZeroFlag(A == 0);
}

void CPU::OR_A_n8() {
  uint8_t value = fetchByte();
  OR_A_r8(value);
}

void CPU::CP_A_r8(uint8_t value) {
  uint8_t result = A - value;
  bool halfCarry = (A & 0x0F) < (value & 0x0F);
  bool carry = A < value;

  resetFlags();
  setZeroFlag(result == 0);
  setSubtractFlag(true);
  setHalfCarryFlag(halfCarry);
  setCarryFlag(carry);
}

void CPU::CP_A_n8() {
  uint8_t value = fetchByte();
  CP_A_r8(value);
}

void CPU::ADD_SP_n8() {
  int8_t value = fetchByte();
  bool halfCarry = (SP & 0x0F) + (value & 0x0F) > 0x0F;
  bool carry = (SP & 0xFF) + value > 0xFF;

  resetFlags();
  setZeroFlag(false);
  setSubtractFlag(false);
  setHalfCarryFlag(halfCarry);
  setCarryFlag(carry);

  SP += value;
}

void CPU::LD_HL_SP_n8() {
  int8_t value = fetchByte();
  bool halfCarry = (SP & 0x0F) + (value & 0x0F) > 0x0F;
  bool carry = (SP & 0xFF) + value > 0xFF;

  resetFlags();
  setZeroFlag(false);
  setSubtractFlag(false);
  setHalfCarryFlag(halfCarry);
  setCarryFlag(carry);

  HL() = SP + value;
}

void CPU::JP_n16() { PC = fetchWord(); }

void CPU::JP_HL() { PC = HL(); }

void CPU::CALL_n16() {
  uint16_t address = fetchWord();
  SP -= 2;
  memory.writeWord(SP, PC);
  PC = address;
}

void CPU::RET() { PC = memory.readWord(--SP); }

void CPU::RETI() {
  PC = memory.readWord(SP);
  EI();
}

void CPU::PUSH_r16(uint16_t &registerPair) {
  SP -= 2;
  memory.writeWord(SP, registerPair);
}

void CPU::POP_r16(uint16_t &registerPair) {
  SP += 2;
  registerPair = memory.readWord(SP);
}

void CPU::LDH_n8_A() {
  uint8_t address = fetchByte();
  memory.writeByte(0xFF00 + address, A);
}

void CPU::LDH_A_n8() {
  uint8_t address = fetchByte();
  A = memory.readByte(0xFF00 + address);
}

void CPU::LD_n16_A() {
  uint16_t address = fetchWord();
  memory.writeByte(address, A);
}

void CPU::LD_A_n16() {
  uint16_t address = fetchWord();
  A = memory.readByte(address);
}

void CPU::LD_SP_HL() { SP = HL(); }

void CPU::DI() {  // IME = false;
}

void CPU::EI() {  // IME = true;
}

void CPU::RLCA() {
  bool carry = (A & 0x80) == 0x80;
  A = (A << 1) | carry;
  resetFlags();
  setCarryFlag(carry);
}

void CPU::LD_HL_r8(uint8_t &registerPair) {
  memory.writeByte(HL(), registerPair);
}

void CPU::RLA() {
  bool carry = (A & 0x80) == 0x80;
  A = (A << 1) | getCarryFlag();
  resetFlags();
  setCarryFlag(carry);
}

void CPU::RRA() {
  bool carry = (A & 0x01) == 0x01;
  A = (A >> 1) | (getCarryFlag() << 7);
  resetFlags();
  setCarryFlag(carry);
}

void CPU::DAA() {
  uint8_t correction = 0;
  if (getHalfCarryFlag() || (!getSubtractFlag() && (A & 0x0F) > 9)) {
    correction |= 0x06;
  }
  if (getCarryFlag() || (!getSubtractFlag() && A > 0x99)) {
    correction |= 0x60;
    setCarryFlag(true);
  }
  A += getSubtractFlag() ? -correction : correction;
  setZeroFlag(A == 0);
  setHalfCarryFlag(false);
}

void CPU::CPL() {
  A = ~A;
  setSubtractFlag(true);
  setHalfCarryFlag(true);
}

void CPU::SCF() {
  setSubtractFlag(false);
  setHalfCarryFlag(false);
  setCarryFlag(true);
}

void CPU::CCF() {
  setSubtractFlag(false);
  setHalfCarryFlag(false);
  setCarryFlag(!getCarryFlag());
}

void CPU::HALT() {
  //   if (IME) {
  //     HALTed = true;
  //   } else {
  //     HALTbug = true;
  //   }
}

void CPU::STOP() {
  //   STOPped = true;
  //   PC++;
}

void CPU::LD_r16_n8(uint16_t &destinationRegister) {
  uint8_t value = fetchByte();
  memory.writeByte(destinationRegister, value);
}

void CPU::RRCA() {
  bool carry = (A & 0x01) == 0x01;
  A = (A >> 1) | (carry << 7);
  resetFlags();
  setCarryFlag(carry);
}

void CPU::LD_r16_r8(uint16_t &destinationRegister, uint8_t sourceRegister) {
  memory.writeByte(destinationRegister, sourceRegister);
}

void CPU::LD_r8_r16(uint8_t &destinationRegister, uint16_t sourceRegister) {
  destinationRegister = memory.readByte(sourceRegister);
}

void CPU::JR_n8() { PC += fetchByte(); }

void CPU::JR_con_n8(bool condition) {
  int8_t value = fetchByte();
  if (condition) {
    PC += value;
  }
}

void CPU::ADD_A_r16(uint16_t &registerPair) {
  ADD_A_r8(memory.readByte(registerPair));
}

void CPU::ADC_A_r16(uint16_t &registerPair) {
  ADC_A_r8(memory.readByte(registerPair));
}

void CPU::SUB_A_r16(uint16_t &registerPair) {
  SUB_A_r8(memory.readByte(registerPair));
}

void CPU::SBC_A_r16(uint16_t &registerPair) {
  SBC_A_r8(memory.readByte(registerPair));
}

void CPU::AND_A_r16(uint16_t &registerPair) {
  AND_A_r8(memory.readByte(registerPair));
}

void CPU::XOR_A_r16(uint16_t &registerPair) {
  XOR_A_r8(memory.readByte(registerPair));
}

void CPU::OR_A_r16(uint16_t &registerPair) {
  OR_A_r8(memory.readByte(registerPair));
}

void CPU::CP_A_r16(uint16_t &registerPair) {
  CP_A_r8(memory.readByte(registerPair));
}

void CPU::RET_con(bool condition) {
  if (condition) {
    RET();
  }
}

void CPU::JP_con_n16(bool condition) {
  uint16_t address = fetchWord();
  if (condition) {
    PC = address;
  }
}

void CPU::CALL_con_n16(bool condition) {
  if (condition) {
    CALL_n16();
  } else {
    fetchWord();
  }
}

void CPU::RST(uint16_t target) {
  SP -= 2;
  memory.writeWord(SP, PC);
  PC = target;
}

void CPU::LDH_C_A() { memory.writeByte(0xFF00 + C, A); }

void CPU::LDH_A_r8(uint8_t &registerPair) {
  A = memory.readByte(0xFF00 + registerPair);
}