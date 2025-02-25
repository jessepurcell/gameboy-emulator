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
    memory.writeByte(0x0000, 0x3E); // LD A, 0x42
    memory.writeByte(0x0001, 0x42);
    cpu.PC = 0;
    
    EXPECT_EQ(cpu.fetchByte(), 0x3E);
    EXPECT_EQ(cpu.PC, 1);
    EXPECT_EQ(cpu.fetchByte(), 0x42);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: Fetch Word**
TEST_F(CPUTest, FetchWord) {
    memory.writeByte(0x1000, 0x34); // Low byte
    memory.writeByte(0x1001, 0x12); // High byte
    cpu.PC = 0x1000;

    EXPECT_EQ(cpu.fetchWord(), 0x1234);
    EXPECT_EQ(cpu.PC, 0x1002);
}

// ✅ **Test: LOAD A, B (0x78 opcode)**
TEST_F(CPUTest, LoadA_B) {
    cpu.A = 0x12;
    cpu.B = 0x34;
    memory.writeByte(0x0000, 0x78); // LD A, B
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x78

    EXPECT_EQ(cpu.A, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD B, C (0x41 opcode)**
TEST_F(CPUTest, LoadB_C) {
    cpu.B = 0x00;
    cpu.C = 0x34;
    memory.writeByte(0x0000, 0x41); // LD B, C
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x41

    EXPECT_EQ(cpu.B, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD D, E (0x53 opcode)**
TEST_F(CPUTest, LoadD_E) {
    cpu.D = 0x00;
    cpu.E = 0x56;
    memory.writeByte(0x0000, 0x53); // LD D, E
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x53

    EXPECT_EQ(cpu.D, 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD H, L (0x65 opcode)**
TEST_F(CPUTest, LoadH_L) {
    cpu.H = 0x00;
    cpu.L = 0x78;
    memory.writeByte(0x0000, 0x65); // LD H, L
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x65

    EXPECT_EQ(cpu.H, 0x78);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD A, A (0x7F opcode)**
TEST_F(CPUTest, LoadA_A) {
    cpu.A = 0x9A;
    memory.writeByte(0x0000, 0x7F); // LD A, A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x7F

    EXPECT_EQ(cpu.A, 0x9A);
    EXPECT_EQ(cpu.PC, 1);
}
// ✅ **Test: LOAD (n16), SP (0x08 opcode)**
TEST_F(CPUTest, Load_n16_SP) {
    cpu.SP = 0x1234;
    memory.writeByte(0x0000, 0x08); // LD (n16), SP
    memory.writeByte(0x0001, 0x00); // Low byte of address
    memory.writeByte(0x0002, 0x80); // High byte of address
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x08

    EXPECT_EQ(memory.readByte(0x8000), 0x34); // Low byte of SP
    EXPECT_EQ(memory.readByte(0x8001), 0x12); // High byte of SP
    EXPECT_EQ(cpu.PC, 3);
}
// ✅ **Test: LOAD A, (BC) (0x0A opcode)**
TEST_F(CPUTest, LoadA_BC) {
    cpu.B = 0x12;
    cpu.C = 0x34;
    memory.writeByte(0x1234, 0x56); // Value at address BC
    memory.writeByte(0x0000, 0x0A); // LD A, (BC)
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x0A

    EXPECT_EQ(cpu.A, 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD A, (DE) (0x1A opcode)**
TEST_F(CPUTest, LoadA_DE) {
    cpu.D = 0x12;
    cpu.E = 0x34;
    memory.writeByte(0x1234, 0x78); // Value at address DE
    memory.writeByte(0x0000, 0x1A); // LD A, (DE)
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x1A

    EXPECT_EQ(cpu.A, 0x78);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD (BC), A (0x02 opcode)**
TEST_F(CPUTest, LoadBC_A) {
    cpu.A = 0x12;
    cpu.B = 0x00;
    cpu.C = 0x34;
    memory.writeByte(0x0000, 0x02); // LD (BC), A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x02

    EXPECT_EQ(memory.readByte(0x0034), 0x12);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD (DE), A (0x12 opcode)**
TEST_F(CPUTest, LoadDE_A) {
    cpu.A = 0x56;
    cpu.D = 0x00;
    cpu.E = 0x78;
    memory.writeByte(0x0000, 0x12); // LD (DE), A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x12

    EXPECT_EQ(memory.readByte(0x0078), 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD (HL+), A (0x22 opcode)**
TEST_F(CPUTest, LoadHLPlus_A) {
    cpu.A = 0x9A;
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x0000, 0x22); // LD (HL+), A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x22

    EXPECT_EQ(memory.readByte(0x1234), 0x9A);
    EXPECT_EQ(cpu.HL(), 0x1235); // HL should be incremented
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD (HL-), A (0x32 opcode)**
TEST_F(CPUTest, LoadHLMinus_A) {
    cpu.A = 0xBC;
    cpu.H = 0x56;
    cpu.L = 0x78;
    memory.writeByte(0x0000, 0x32); // LD (HL-), A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x32

    EXPECT_EQ(memory.readByte(0x5678), 0xBC);
    EXPECT_EQ(cpu.HL(), 0x5677); // HL should be decremented
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD BC, n16 (0x01 opcode)**
TEST_F(CPUTest, LoadBC_n16) {
    memory.writeByte(0x0000, 0x01); // LD BC, n16
    memory.writeByte(0x0001, 0x34); // Low byte
    memory.writeByte(0x0002, 0x12); // High byte
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x01

    EXPECT_EQ(cpu.BC(), 0x1234);
    EXPECT_EQ(cpu.PC, 3);
}

// ✅ **Test: LOAD DE, n16 (0x11 opcode)**
TEST_F(CPUTest, LoadDE_n16) {
    memory.writeByte(0x0000, 0x11); // LD DE, n16
    memory.writeByte(0x0001, 0x78); // Low byte
    memory.writeByte(0x0002, 0x56); // High byte
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x11

    EXPECT_EQ(cpu.DE(), 0x5678);
    EXPECT_EQ(cpu.PC, 3);
}

// ✅ **Test: LOAD HL, n16 (0x21 opcode)**
TEST_F(CPUTest, LoadHL_n16) {
    memory.writeByte(0x0000, 0x21); // LD HL, n16
    memory.writeByte(0x0001, 0xBC); // Low byte
    memory.writeByte(0x0002, 0x9A); // High byte
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x21

    EXPECT_EQ(cpu.HL(), 0x9ABC);
    EXPECT_EQ(cpu.PC, 3);
}

// ✅ **Test: LOAD SP, n16 (0x31 opcode)**
TEST_F(CPUTest, LoadSP_n16) {
    memory.writeByte(0x0000, 0x31); // LD SP, n16
    memory.writeByte(0x0001, 0xF0); // Low byte
    memory.writeByte(0x0002, 0x0D); // High byte
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x31

    EXPECT_EQ(cpu.SP, 0x0DF0);
    EXPECT_EQ(cpu.PC, 3);
}

// ✅ **Test: LOAD B, n8 (0x06 opcode)**
TEST_F(CPUTest, LoadB_n8) {
    memory.writeByte(0x0000, 0x06); // LD B, n8
    memory.writeByte(0x0001, 0x34); // Value to load into B
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x06

    EXPECT_EQ(cpu.B, 0x34);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD C, n8 (0x0E opcode)**
TEST_F(CPUTest, LoadC_n8) {
    memory.writeByte(0x0000, 0x0E); // LD C, n8
    memory.writeByte(0x0001, 0x56); // Value to load into C
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x0E

    EXPECT_EQ(cpu.C, 0x56);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD D, n8 (0x16 opcode)**
TEST_F(CPUTest, LoadD_n8) {
    memory.writeByte(0x0000, 0x16); // LD D, n8
    memory.writeByte(0x0001, 0x78); // Value to load into D
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x16

    EXPECT_EQ(cpu.D, 0x78);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD E, n8 (0x1E opcode)**
TEST_F(CPUTest, LoadE_n8) {
    memory.writeByte(0x0000, 0x1E); // LD E, n8
    memory.writeByte(0x0001, 0x9A); // Value to load into E
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x1E

    EXPECT_EQ(cpu.E, 0x9A);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD H, n8 (0x26 opcode)**
TEST_F(CPUTest, LoadH_n8) {
    memory.writeByte(0x0000, 0x26); // LD H, n8
    memory.writeByte(0x0001, 0xBC); // Value to load into H
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x26

    EXPECT_EQ(cpu.H, 0xBC);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD L, n8 (0x2E opcode)**
TEST_F(CPUTest, LoadL_n8) {
    memory.writeByte(0x0000, 0x2E); // LD L, n8
    memory.writeByte(0x0001, 0xDE); // Value to load into L
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x2E

    EXPECT_EQ(cpu.L, 0xDE);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD A, n8 (0x3E opcode)**
TEST_F(CPUTest, LoadA_n8) {
    memory.writeByte(0x0000, 0x3E); // LD A, n8
    memory.writeByte(0x0001, 0xF0); // Value to load into A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x3E

    EXPECT_EQ(cpu.A, 0xF0);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: INC BC (0x03 opcode)**
TEST_F(CPUTest, IncBC) {
    cpu.B = 0x12;
    cpu.C = 0x34;
    memory.writeByte(0x0000, 0x03); // INC BC
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x03

    EXPECT_EQ(cpu.BC(), 0x1235);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: INC DE (0x13 opcode)**
TEST_F(CPUTest, IncDE) {
    cpu.D = 0x56;
    cpu.E = 0x78;
    memory.writeByte(0x0000, 0x13); // INC DE
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x13

    EXPECT_EQ(cpu.DE(), 0x5679);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: INC HL (0x23 opcode)**
TEST_F(CPUTest, IncHL) {
    cpu.H = 0x9A;
    cpu.L = 0xBC;
    memory.writeByte(0x0000, 0x23); // INC HL
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x23

    EXPECT_EQ(cpu.HL(), 0x9ABD);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: INC SP (0x33 opcode)**
TEST_F(CPUTest, IncSP) {
    cpu.SP = 0x0DF0;
    memory.writeByte(0x0000, 0x33); // INC SP
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x33

    EXPECT_EQ(cpu.SP, 0x0DF1);
    EXPECT_EQ(cpu.PC, 1);
}