#include <gtest/gtest.h>

#include "../include/cpu.hpp"
#include "../include/memory.hpp"

// ✅ Test Fixture for CPU
class CPUTest : public ::testing::Test {
 protected:
  Memory memory;
  CPU cpu{memory};

  void SetUp() override {
    // Reset memory and registers before each test
    memory = Memory();
    // for (uint16_t addr = 0; addr < 0x10000; addr++) {
    //     memory.writeByte(addr, 0);
    // }
    cpu.PC = 0;
    cpu.SP = 0;
    cpu.A = 0;
    cpu.B = 0;
    cpu.C = 0;
    cpu.D = 0;
    cpu.E = 0;
    cpu.H = 0;
    cpu.L = 0;
  }
};

// ✅ **Test: CPU Initial State**
TEST_F(CPUTest, InitialState) {
  EXPECT_EQ(cpu.PC, 0);
  EXPECT_EQ(cpu.SP, 0);
  EXPECT_EQ(cpu.A, 0);
  EXPECT_EQ(cpu.B, 0);
  EXPECT_EQ(cpu.C, 0);
  EXPECT_EQ(cpu.D, 0);
  EXPECT_EQ(cpu.E, 0);
  EXPECT_EQ(cpu.H, 0);
  EXPECT_EQ(cpu.L, 0);
}

// ✅ **Test: Fetch Byte**
TEST_F(CPUTest, FetchByte) {
  memory.writeByte(0x0000, 0x3E);  // LD A, 0x42
  memory.writeByte(0x0001, 0x42);
  cpu.PC = 0;

  EXPECT_EQ(cpu.fetchByte(), 0x3E);
  EXPECT_EQ(cpu.PC, 1);
  EXPECT_EQ(cpu.fetchByte(), 0x42);
  EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: Fetch Word**
TEST_F(CPUTest, FetchWord) {
  memory.writeByte(0x1000, 0x34);  // Low byte
  memory.writeByte(0x1001, 0x12);  // High byte
  cpu.PC = 0x1000;

  EXPECT_EQ(cpu.fetchWord(), 0x1234);
  EXPECT_EQ(cpu.PC, 0x1002);
}
// ✅ **Test: LD_r8_n8**
TEST_F(CPUTest, LD_r8_n8) {
  memory.writeByte(0x0000, 0x06);  // LD B, 0x42
  memory.writeByte(0x0001, 0x42);
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.B, 0x42);
  EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LD_r16_n16**
TEST_F(CPUTest, LD_r16_n16) {
  memory.writeByte(0x0000, 0x01);  // LD BC, 0x1234
  memory.writeByte(0x0001, 0x34);
  memory.writeByte(0x0002, 0x12);
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.BC(), 0x1234);
  EXPECT_EQ(cpu.PC, 3);
}

// ✅ **Test: INC_r8**
TEST_F(CPUTest, INC_r8) {
  cpu.B = 0x01;
  memory.writeByte(0x0000, 0x04);  // INC B
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.B, 0x02);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: DEC_r8**
TEST_F(CPUTest, DEC_r8) {
  cpu.B = 0x02;
  memory.writeByte(0x0000, 0x05);  // DEC B
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.B, 0x01);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: ADD_A_r8**
TEST_F(CPUTest, ADD_A_r8) {
  cpu.A = 0x01;
  cpu.B = 0x01;
  memory.writeByte(0x0000, 0x80);  // ADD A, B
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x02);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: SUB_A_r8**
TEST_F(CPUTest, SUB_A_r8) {
  cpu.A = 0x02;
  cpu.B = 0x01;
  memory.writeByte(0x0000, 0x90);  // SUB A, B
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x01);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: AND_A_r8**
TEST_F(CPUTest, AND_A_r8) {
  cpu.A = 0x03;
  cpu.B = 0x01;
  memory.writeByte(0x0000, 0xA0);  // AND A, B
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x01);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: OR_A_r8**
TEST_F(CPUTest, OR_A_r8) {
  cpu.A = 0x01;
  cpu.B = 0x02;
  memory.writeByte(0x0000, 0xB0);  // OR A, B
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x03);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: XOR_A_r8**
TEST_F(CPUTest, XOR_A_r8) {
  cpu.A = 0x03;
  cpu.B = 0x01;
  memory.writeByte(0x0000, 0xA8);  // XOR A, B
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x02);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: CP_A_r8**
TEST_F(CPUTest, CP_A_r8) {
  cpu.A = 0x02;
  cpu.B = 0x02;
  memory.writeByte(0x0000, 0xB8);  // CP A, B
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.getZeroFlag(), true);
  EXPECT_EQ(cpu.PC, 1);
}
// ✅ **Test: ADC_A_r8**
TEST_F(CPUTest, ADC_A_r8) {
  cpu.A = 0x01;
  cpu.B = 0x01;
  cpu.setCarryFlag(true);
  memory.writeByte(0x0000, 0x88);  // ADC A, B
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x03);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: SBC_A_r8**
TEST_F(CPUTest, SBC_A_r8) {
  cpu.A = 0x03;
  cpu.B = 0x01;
  cpu.setCarryFlag(true);
  memory.writeByte(0x0000, 0x98);  // SBC A, B
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x01);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LD_r16_A**
TEST_F(CPUTest, LD_r16_A) {
  cpu.A = 0x42;
  cpu.HL() = 0x1234;
  memory.writeByte(0x0000, 0x22);  // LD (HL+), A
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(memory.readByte(0x1234), 0x42);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LD_A_r16**
TEST_F(CPUTest, LD_A_r16) {
  cpu.HL() = 0x1234;
  memory.writeByte(0x1234, 0x42);
  memory.writeByte(0x0000, 0x2A);  // LD A, (HL+)
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x42);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LD_n16_SP**
TEST_F(CPUTest, LD_n16_SP) {
  cpu.SP = 0x1234;
  memory.writeByte(0x0000, 0x08);  // LD (0x5678), SP
  memory.writeByte(0x0001, 0x78);
  memory.writeByte(0x0002, 0x56);
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(memory.readWord(0x5678), 0x1234);
  EXPECT_EQ(cpu.PC, 3);
}

// ✅ **Test: ADD_HL_r16**
TEST_F(CPUTest, ADD_HL_r16) {
  cpu.HL() = 0x1234;
  cpu.BC() = 0x1111;
  memory.writeByte(0x0000, 0x09);  // ADD HL, BC
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.HL(), 0x2345);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: JP_n16**
TEST_F(CPUTest, JP_n16) {
  memory.writeByte(0x0000, 0xC3);  // JP 0x1234
  memory.writeByte(0x0001, 0x34);
  memory.writeByte(0x0002, 0x12);
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.PC, 0x1234);
}

// ✅ **Test: CALL_n16**
TEST_F(CPUTest, CALL_n16) {
  memory.writeByte(0x0000, 0xCD);  // CALL 0x1234
  memory.writeByte(0x0001, 0x34);
  memory.writeByte(0x0002, 0x12);
  cpu.PC = 0;
  cpu.SP = 0xFFFE;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.PC, 0x1234);  // PC should jump to 0x1234
  EXPECT_EQ(memory.readWord(0xFFFC),
            0x0003);          // Return address should be stored at 0xFFFC
  EXPECT_EQ(cpu.SP, 0xFFFC);  // SP should decrement by 2
}

// ✅ **Test: ADD_SP_n8**
TEST_F(CPUTest, ADD_SP_n8) {
  cpu.SP = 0xFFF0;
  memory.writeByte(0x0000, 0xE8);  // ADD SP, 0x10
  memory.writeByte(0x0001, 0x10);
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.SP, 0x0000);
  EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LD_HL_SP_n8**
TEST_F(CPUTest, LD_HL_SP_n8) {
  cpu.SP = 0xFFF0;
  memory.writeByte(0x0000, 0xF8);  // LD HL, SP+0x10
  memory.writeByte(0x0001, 0x10);
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.HL(), 0x0000);
  EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: JR_con_n8**
TEST_F(CPUTest, JR_con_n8) {
  memory.writeByte(0x0000, 0x28);  // JR Z, 0x02
  memory.writeByte(0x0001, 0x02);
  cpu.PC = 0;
  cpu.setZeroFlag(true);

  cpu.executeOpcode();

  EXPECT_EQ(cpu.PC, 0x0004);
}

// ✅ **Test: RET_con**
TEST_F(CPUTest, RET_con) {
  memory.writeWord(0xFFFE, 0x1234);
  memory.writeByte(0x0000, 0xC0);  // RET NZ
  cpu.PC = 0;
  cpu.SP = 0xFFFE;
  cpu.setZeroFlag(false);

  cpu.executeOpcode();

  EXPECT_EQ(cpu.PC, 0x1234);
  EXPECT_EQ(cpu.SP, 0xFFFF);
}

// ✅ **Test: JP_con_n16**
TEST_F(CPUTest, JP_con_n16) {
  memory.writeByte(0x0000, 0xC2);  // JP NZ, 0x1234
  memory.writeByte(0x0001, 0x34);
  memory.writeByte(0x0002, 0x12);
  cpu.PC = 0;
  cpu.setZeroFlag(false);

  cpu.executeOpcode();

  EXPECT_EQ(cpu.PC, 0x1234);
}

// ✅ **Test: CALL_con_n16**
TEST_F(CPUTest, CALL_con_n16) {
  memory.writeByte(0x0000, 0xC4);  // CALL NZ, 0x1234
  memory.writeByte(0x0001, 0x34);
  memory.writeByte(0x0002, 0x12);
  cpu.PC = 0;
  cpu.SP = 0xFFFE;
  cpu.setZeroFlag(false);

  cpu.executeOpcode();

  EXPECT_EQ(cpu.PC, 0x1234);
  EXPECT_EQ(memory.readWord(0xFFFE), 0x0003);
  EXPECT_EQ(cpu.SP, 0xFFFD);
}

// ✅ **Test: HALT**
TEST_F(CPUTest, HALT) {
  memory.writeByte(0x0000, 0x76);  // HALT
  cpu.PC = 0;

  cpu.executeOpcode();

  // Add check for HALTed state if implemented
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: RET**
TEST_F(CPUTest, RET) {
  memory.writeWord(0xFFFE, 0x1234);
  memory.writeByte(0x0000, 0xC9);  // RET
  cpu.PC = 0;
  cpu.SP = 0xFFFE;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.PC, 0x1234);
  EXPECT_EQ(cpu.SP, 0xFFFF);
}

// ✅ **Test: RST**
TEST_F(CPUTest, RST) {
  memory.writeByte(0x0000, 0xC7);  // RST 0x00
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.PC, 0x0000);
  EXPECT_EQ(memory.readWord(0xFFFE), 0x0001);
  EXPECT_EQ(cpu.SP, 0xFFFE);
}

// ✅ **Test: LD_r8_r8**
TEST_F(CPUTest, LD_r8_r8) {
  cpu.B = 0x42;
  memory.writeByte(0x0000, 0x40);  // LD B, B
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.B, 0x42);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: INC_r16**
TEST_F(CPUTest, INC_r16) {
  cpu.BC() = 0x1234;
  memory.writeByte(0x0000, 0x03);  // INC BC
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.BC(), 0x1235);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: DEC_r16**
TEST_F(CPUTest, DEC_r16) {
  cpu.BC() = 0x1234;
  memory.writeByte(0x0000, 0x0B);  // DEC BC
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.BC(), 0x1233);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: JR_n8**
TEST_F(CPUTest, JR_n8) {
  memory.writeByte(0x0000, 0x18);  // JR 0x02
  memory.writeByte(0x0001, 0x02);
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.PC, 0x0004);
}

// ✅ **Test: JP_HL**
TEST_F(CPUTest, JP_HL) {
  cpu.HL() = 0x1234;
  memory.writeByte(0x0000, 0xE9);  // JP (HL)
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.PC, 0x1234);
}

// ✅ **Test: RETI**
TEST_F(CPUTest, RETI) {
  memory.writeWord(0xFFFE, 0x1234);
  memory.writeByte(0x0000, 0xD9);  // RETI
  cpu.PC = 0;
  cpu.SP = 0xFFFE;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.PC, 0x1234);
  EXPECT_EQ(cpu.SP, 0xFFFF);
  // Add check for EI if implemented
}

// ✅ **Test: LDH_n8_A**
TEST_F(CPUTest, LDH_n8_A) {
  cpu.A = 0x42;
  memory.writeByte(0x0000, 0xE0);  // LDH (0xFF00 + 0x10), A
  memory.writeByte(0x0001, 0x10);
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(memory.readByte(0xFF10), 0x42);
  EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LDH_A_n8**
TEST_F(CPUTest, LDH_A_n8) {
  memory.writeByte(0xFF10, 0x42);
  memory.writeByte(0x0000, 0xF0);  // LDH A, (0xFF00 + 0x10)
  memory.writeByte(0x0001, 0x10);
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x42);
  EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LD_n16_A**
TEST_F(CPUTest, LD_n16_A) {
  cpu.A = 0x42;
  memory.writeByte(0x0000, 0xEA);  // LD (0x1234), A
  memory.writeByte(0x0001, 0x34);
  memory.writeByte(0x0002, 0x12);
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(memory.readByte(0x1234), 0x42);
  EXPECT_EQ(cpu.PC, 3);
}

// ✅ **Test: LD_A_n16**
TEST_F(CPUTest, LD_A_n16) {
  memory.writeByte(0x1234, 0x42);
  memory.writeByte(0x0000, 0xFA);  // LD A, (0x1234)
  memory.writeByte(0x0001, 0x34);
  memory.writeByte(0x0002, 0x12);
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x42);
  EXPECT_EQ(cpu.PC, 3);
}

// ✅ **Test: LD_SP_HL**
TEST_F(CPUTest, LD_SP_HL) {
  cpu.HL() = 0x1234;
  memory.writeByte(0x0000, 0xF9);  // LD SP, HL
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.SP, 0x1234);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: DI**
TEST_F(CPUTest, DI) {
  memory.writeByte(0x0000, 0xF3);  // DI
  cpu.PC = 0;

  cpu.executeOpcode();

  // Add check for IME if implemented
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: EI**
TEST_F(CPUTest, EI) {
  memory.writeByte(0x0000, 0xFB);  // EI
  cpu.PC = 0;

  cpu.executeOpcode();

  // Add check for IME if implemented
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: RLCA**
TEST_F(CPUTest, RLCA) {
  cpu.A = 0x85;                    // 10000101
  memory.writeByte(0x0000, 0x07);  // RLCA
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x0B);  // 00001011
  EXPECT_EQ(cpu.getCarryFlag(), true);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: RLA**
TEST_F(CPUTest, RLA) {
  cpu.A = 0x85;  // 10000101
  cpu.setCarryFlag(true);
  memory.writeByte(0x0000, 0x17);  // RLA
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x0B);  // 00001011
  EXPECT_EQ(cpu.getCarryFlag(), true);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: RRCA**
TEST_F(CPUTest, RRCA) {
  cpu.A = 0x85;                    // 10000101
  memory.writeByte(0x0000, 0x0F);  // RRCA
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0xC2);  // 11000010
  EXPECT_EQ(cpu.getCarryFlag(), true);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: RRA**
TEST_F(CPUTest, RRA) {
  cpu.A = 0x85;  // 10000101
  cpu.setCarryFlag(true);
  memory.writeByte(0x0000, 0x1F);  // RRA
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0xC2);  // 11000010
  EXPECT_EQ(cpu.getCarryFlag(), true);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: DAA**
TEST_F(CPUTest, DAA) {
  cpu.A = 0x15;                    // 00010101
  memory.writeByte(0x0000, 0x27);  // DAA
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x15);  // 00010101 (no change)
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: CPL**
TEST_F(CPUTest, CPL) {
  cpu.A = 0x85;                    // 10000101
  memory.writeByte(0x0000, 0x2F);  // CPL
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.A, 0x7A);  // 01111010
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: SCF**
TEST_F(CPUTest, SCF) {
  memory.writeByte(0x0000, 0x37);  // SCF
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.getCarryFlag(), true);
  EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: CCF**
TEST_F(CPUTest, CCF) {
  cpu.setCarryFlag(true);
  memory.writeByte(0x0000, 0x3F);  // CCF
  cpu.PC = 0;

  cpu.executeOpcode();

  EXPECT_EQ(cpu.getCarryFlag(), false);
  EXPECT_EQ(cpu.PC, 1);
}
