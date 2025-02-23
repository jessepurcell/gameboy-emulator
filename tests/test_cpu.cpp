#include "../include/cpu.hpp"
#include <gtest/gtest.h>

class CPUTest : public ::testing::Test {
protected:
    CPU cpu;
    void SetUp() override { cpu.reset(); }
};

TEST_F(CPUTest, CPUInitialState) {
    EXPECT_EQ(cpu.registers[CPU::AF], 0x01B0);
    EXPECT_EQ(cpu.registers[CPU::BC], 0x0013);
    EXPECT_EQ(cpu.registers[CPU::DE], 0x00D8);
    EXPECT_EQ(cpu.registers[CPU::HL], 0x014D);
    EXPECT_EQ(cpu.registers[CPU::SP], 0xFFFE);
    EXPECT_EQ(cpu.registers[CPU::PC], 0x0100);
}

TEST_F(CPUTest, JumpInstruction) {
    cpu.writeByte(0x100, 0xC3);
    cpu.writeByte(0x101, 0x34);
    cpu.writeByte(0x102, 0x12);

    auto result = cpu.executeNextInstruction();
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(cpu.registers[CPU::PC], 0x1234);
}

TEST_F(CPUTest, FlagHandling) {
    cpu.setFlag(CPU::Z, true);
    EXPECT_TRUE(cpu.getFlag(CPU::Z));

    cpu.setFlag(CPU::Z, false);
    EXPECT_FALSE(cpu.getFlag(CPU::Z));
}
