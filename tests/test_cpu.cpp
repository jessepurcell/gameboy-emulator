#include <gtest/gtest.h>
#include "../include/cpu.hpp"

// Test if CPU resets correctly
TEST(CPUTest, ResetState) {
    CPU cpu;
    cpu.reset();
    
    EXPECT_EQ(cpu.registers[CPU::AF], 0x01B0);
    EXPECT_EQ(cpu.registers[CPU::BC], 0x0013);
    EXPECT_EQ(cpu.registers[CPU::DE], 0x00D8);
    EXPECT_EQ(cpu.registers[CPU::HL], 0x014D);
    EXPECT_EQ(cpu.SP, 0xFFFE);
    EXPECT_EQ(cpu.PC, 0x0100);
}

// Test flag manipulation
TEST(CPUTest, FlagOperations) {
    CPU cpu;
    cpu.setFlag(CPU::ZF, true);
    EXPECT_TRUE(cpu.getFlag(CPU::ZF));

    cpu.setFlag(CPU::ZF, false);
    EXPECT_FALSE(cpu.getFlag(CPU::ZF));
}

// Test memory read/write (currently stubbed)
TEST(CPUTest, MemoryAccess) {
    CPU cpu;
    cpu.writeByte(0xC000, 0x42);
    EXPECT_EQ(cpu.readByte(0xC000), 0xFF); // Stub always returns 0xFF for now
}

// Test instruction execution (NOP)
TEST(CPUTest, ExecuteNOP) {
    CPU cpu;
    cpu.writeByte(0x0100, 0x00); // NOP instruction at PC
    cpu.executeNextInstruction();
    EXPECT_EQ(cpu.PC, 0x0101); // PC should increment
}

// Test unknown opcode handling
TEST(CPUTest, ExecuteUnknownOpcode) {
    CPU cpu;
    cpu.writeByte(0x0100, 0xFF); // Invalid opcode
    auto result = cpu.executeNextInstruction();
    EXPECT_FALSE(result); // Should return an error
    EXPECT_EQ(result.error(), "CPU Error: Unknown opcode: 255");
}

// Test HALT instruction (should throw an error)
TEST(CPUTest, ExecuteHALT) {
    CPU cpu;
    cpu.writeByte(0x0100, 0x76); // HALT instruction
    auto result = cpu.executeNextInstruction();
    EXPECT_FALSE(result);
    EXPECT_EQ(result.error(), "CPU Error: HALT executed");
}

// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
