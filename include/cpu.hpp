#pragma once

#include <array>
#include <cstdint>
#include <functional>

#include "memory.hpp"

class CPU {
 public:
  CPU(Memory &memory);
  void executeOpcode();
  void handleInterrupts();

  // Registers
  uint8_t &F = registers[0];
  uint8_t &A = registers[1];
  uint8_t &C = registers[2];
  uint8_t &B = registers[3];
  uint8_t &E = registers[4];
  uint8_t &D = registers[5];
  uint8_t &L = registers[6];
  uint8_t &H = registers[7];

  uint16_t SP = 0xFFF, PC = 0;
  bool IME = false;

  // Access and return reference to combined AF using pointer
  uint16_t &AF() {
    // Cast pointer to uint16_t* to treat A and F as a 16-bit value
    return *reinterpret_cast<uint16_t *>(&registers[0]);
  }

  // Access and return reference to combined BC using pointer
  uint16_t &BC() {
    // Cast pointer to uint16_t* to treat B and C as a 16-bit value
    return *reinterpret_cast<uint16_t *>(&registers[2]);
  }

  uint16_t &DE() {
    return *reinterpret_cast<uint16_t *>(&registers[4]);  // D and E
  }

  uint16_t &HL() {
    return *reinterpret_cast<uint16_t *>(&registers[6]);  // H and L
  }

  void setAF(uint16_t value) {
    A = value >> 8;
    F = value & 0xFF;
  }

  void setBC(uint16_t value) {
    B = value >> 8;
    C = value & 0xFF;
  }

  void setDE(uint16_t value) {
    D = value >> 8;
    E = value & 0xFF;
  }

  void setHL(uint16_t value) {
    H = value >> 8;
    L = value & 0xFF;
  }

  // Fetching and execution helpers
  uint8_t fetchByte();
  uint16_t fetchWord();
  bool getZeroFlag() { return F & 0x80; }
  bool getCarryFlag() { return F & 0x10; }
  bool getHalfCarryFlag() { return F & 0x20; }
  bool getSubtractFlag() { return F & 0x40; }
  void resetFlags() { F = 0; }
  void setCarryFlag(bool value) {
    if (value) {
      F |= 0x10;
    } else {
      F &= ~0x10;
    }
  }

  void setHalfCarryFlag(bool value) {
    if (value) {
      F |= 0x20;
    } else {
      F &= ~0x20;
    }
  }

  void setSubtractFlag(bool value) {
    if (value) {
      F |= 0x40;
    } else {
      F &= ~0x40;
    }
  }

  void setZeroFlag(bool value) {
    if (value) {
      F |= 0x80;
    } else {
      F &= ~0x80;
    }
  }

 private:
  uint8_t registers[8] = {0};
  uint16_t AF_register = 0;
  uint16_t BC_register = 0;
  uint16_t DE_register = 0;
  uint16_t HL_register = 0;

  Memory &memory;
  // Lookup tables for opcodes
  std::array<std::function<void()>, 256> opcodeTable{};

  void logState();

  void bindOpcodes();

  // Instruction handlers
  void NOP();

  // Load Instructions
  void LD_r16_n16(uint16_t &registerPair);  //
  void LD_r16_A(uint16_t &registerPair);    //
  void LD_A_r16(uint16_t &registerPair);    //
  void LD_n16_SP();                         //
  void LD_HL_r8(uint8_t &registerPair);     //
  void LD_r16_r8(uint16_t &destinationRegister, uint8_t sourceRegister);
  void LD_r16_r16(uint16_t &destinationRegister, uint16_t &sourceRegister);
  void LD_r16_n8(uint16_t &registerPair);
  void LD_r8_r16(uint8_t &destinationRegister, uint16_t sourceRegister);

  void INC_r16(uint16_t &registerPair);     //
  void DEC_r16(uint16_t &registerPair);     //
  void ADD_HL_r16(uint16_t &registerPair);  //

  void INC_r8(uint8_t &registerPair);
  void DEC_r8(uint8_t &registerPair);

  void LD_r8_n8(uint8_t &registerPair);

  void RLCA();
  void RRCA();
  void RLA();
  void RRA();
  void DAA();
  void CPL();
  void SCF();
  void CCF();

  void JR_n8();
  void JR_con_n8(bool condition);

  void STOP();

  void LD_r8_r8(uint8_t &destinationRegister, uint8_t sourceRegister);

  void HALT();

  void ADD_A_r8(uint8_t sourceRegister);
  void ADD_A_r16(uint16_t &registerPair);
  void ADC_A_r8(uint8_t sourceRegister);
  void ADC_A_r16(uint16_t &registerPair);
  void SUB_A_r8(uint8_t sourceRegister);
  void SUB_A_r16(uint16_t &registerPair);
  void SBC_A_r8(uint8_t sourceRegister);
  void SBC_A_r16(uint16_t &registerPair);
  void AND_A_r8(uint8_t sourceRegister);
  void AND_A_r16(uint16_t &registerPair);
  void XOR_A_r8(uint8_t sourceRegister);
  void XOR_A_r16(uint16_t &registerPair);
  void OR_A_r8(uint8_t sourceRegister);
  void OR_A_r16(uint16_t &registerPair);
  void CP_A_r8(uint8_t sourceRegister);
  void CP_A_r16(uint16_t &registerPair);

  void ADD_A_n8();
  void ADC_A_n8();
  void SUB_A_n8();
  void SBC_A_n8();
  void AND_A_n8();
  void XOR_A_n8();
  void OR_A_n8();
  void CP_A_n8();

  void RET_con(bool condition);
  void RET();
  void RETI();
  void n16(bool condition);
  void JP_n16();
  void JP_HL();
  void JP_con_n16(bool condition);
  void CALL_con_n16(bool condition);
  void CALL_n16();
  void RST_TGT3();

  void RST(uint16_t target);

  void POP_r16(uint16_t &registerPair);
  void PUSH_r16(uint16_t &registerPair);

  void LDH_r8_A();
  void LDH_n8_A();
  void LD_n16_A();
  void LDH_A_r8(uint8_t &registerPair);
  void LDH_A_n8();
  void LD_A_n16();

  void LDH_C_A();

  void ADD_SP_n8();
  void LD_HL_SP_n8();
  void LD_SP_HL();

  void DI();
  void EI();
};
