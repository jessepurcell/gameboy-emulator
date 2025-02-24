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
        for (uint16_t addr = 0; addr < 0x10000; addr++) {
            memory.writeByte(addr, 0);
        }
        cpu.PC = 0;
        cpu.SP = 0;
        cpu.A = cpu.B = cpu.C = cpu.D = cpu.E = cpu.H = cpu.L = 0;
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

// ✅ **Test: ADD A, B (0x80 opcode)**
TEST_F(CPUTest, AddA_B) {
    cpu.A = 0x10;
    cpu.B = 0x20;
    memory.writeByte(0x0000, 0x80); // ADD A, B
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x80

    EXPECT_EQ(cpu.A, 0x30);
}

// ✅ **Test: RLC B (0xCB 0x00 opcode)**
TEST_F(CPUTest, RotateLeftCircularB) {
    cpu.B = 0b10000001;
    memory.writeByte(0x0000, 0xCB);
    memory.writeByte(0x0001, 0x00);
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute CB prefix opcode

    EXPECT_EQ(cpu.B, 0b00000011); // RLC should rotate left
}
