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

// ✅ **Test: LD BC, nn (0x01 opcode)**
TEST_F(CPUTest, LoadBCImmediate) {
    memory.writeByte(0x0000, 0x01); // LD BC, 0x1234
    memory.writeByte(0x0001, 0x34);
    memory.writeByte(0x0002, 0x12);
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x01

    EXPECT_EQ(cpu.B, 0x12);
    EXPECT_EQ(cpu.C, 0x34);
    EXPECT_EQ(cpu.BC(), 0x1234);
    EXPECT_EQ(cpu.PC, 3);
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

// ✅ **Test: LOAD A, C (0x79 opcode)**
TEST_F(CPUTest, LoadA_C) {
    cpu.A = 0x12;
    cpu.C = 0x34;
    memory.writeByte(0x0000, 0x79); // LD A, C
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x79

    EXPECT_EQ(cpu.A, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD A, D (0x7A opcode)**
TEST_F(CPUTest, LoadA_D) {
    cpu.A = 0x12;
    cpu.D = 0x34;
    memory.writeByte(0x0000, 0x7A); // LD A, D
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x7A

    EXPECT_EQ(cpu.A, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD A, E (0x7B opcode)**
TEST_F(CPUTest, LoadA_E) {
    cpu.A = 0x12;
    cpu.E = 0x34;
    memory.writeByte(0x0000, 0x7B); // LD A, E
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x7B

    EXPECT_EQ(cpu.A, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD A, H (0x7C opcode)**
TEST_F(CPUTest, LoadA_H) {
    cpu.A = 0x12;
    cpu.H = 0x34;
    memory.writeByte(0x0000, 0x7C); // LD A, H
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x7C

    EXPECT_EQ(cpu.A, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD A, L (0x7D opcode)**
TEST_F(CPUTest, LoadA_L) {
    cpu.A = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x0000, 0x7D); // LD A, L
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x7D

    EXPECT_EQ(cpu.A, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD A, (HL) (0x7E opcode)**
TEST_F(CPUTest, LoadA_HL) {
    cpu.A = 0x0;
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x1234, 0x56); // Value at address HL
    memory.writeByte(0x0000, 0x7E); // LD A, (HL)
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x7E

    EXPECT_EQ(cpu.A, 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD A, A (0x7F opcode)**
TEST_F(CPUTest, LoadA_A) {
    cpu.A = 0x12;
    memory.writeByte(0x0000, 0x7F); // LD A, A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x7F

    EXPECT_EQ(cpu.A, 0x12);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD B, B (0x40 opcode)**
TEST_F(CPUTest, LoadB_B) {
    cpu.B = 0x12;
    memory.writeByte(0x0000, 0x40); // LD A, A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x40

    EXPECT_EQ(cpu.B, 0x12);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD B, C (0x41 opcode)**
TEST_F(CPUTest, LoadB_C) {
    cpu.B = 0x12;
    cpu.C = 0x34;
    memory.writeByte(0x0000, 0x41); // LD B, C
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x41

    EXPECT_EQ(cpu.B, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD B, D (0x42 opcode)**
TEST_F(CPUTest, LoadB_D) {
    cpu.B = 0x12;
    cpu.D = 0x34;
    memory.writeByte(0x0000, 0x42); // LD B, D
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x42

    EXPECT_EQ(cpu.B, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD B, E (0x43 opcode)**
TEST_F(CPUTest, LoadB_E) {
    cpu.B = 0x12;
    cpu.E = 0x34;
    memory.writeByte(0x0000, 0x43); // LD B, E
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x43

    EXPECT_EQ(cpu.B, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD B, H (0x44 opcode)**
TEST_F(CPUTest, LoadB_H) {
    cpu.B = 0x12;
    cpu.H = 0x34;
    memory.writeByte(0x0000, 0x44); // LD B, H
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x44

    EXPECT_EQ(cpu.B, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD B, L (0x45 opcode)**
TEST_F(CPUTest, LoadB_L) {
    cpu.B = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x0000, 0x45); // LD B, L
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x45

    EXPECT_EQ(cpu.B, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD B, (HL) (0x46 opcode)**
TEST_F(CPUTest, LoadB_HL) {
    cpu.B = 0x12;
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x1234, 0x56); // Value at address HL
    memory.writeByte(0x0000, 0x46); // LD B, (HL)
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x46

    EXPECT_EQ(cpu.B, 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD B, A (0x47 opcode)**
TEST_F(CPUTest, LoadB_A) {
    cpu.B = 0x12;
    cpu.A = 0x34;
    memory.writeByte(0x0000, 0x47); // LD B, A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x47

    EXPECT_EQ(cpu.B, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}