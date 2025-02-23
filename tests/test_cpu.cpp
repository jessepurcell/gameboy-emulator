#include "../include/cpu.hpp"
#include <gtest/gtest.h>

// Test Fixture for CPU Tests
class CPUTest : public ::testing::Test
{
protected:
    CPU cpu;

    void SetUp() override
    {
        // Reset memory and CPU state
        std::fill(std::begin(cpu.testMemory), std::end(cpu.testMemory), 0);
        cpu.PC = 0;
        cpu.A = cpu.B = cpu.C = cpu.D = cpu.E = cpu.H = cpu.L = 0;
    }
};

// Test: NOP (0x00)
TEST_F(CPUTest, NOP_DoesNothing)
{
    cpu.testMemory[0x0000] = 0x00; // NOP
    cpu.executeOpcode();
    EXPECT_EQ(cpu.PC, 1); // PC should increment
}

// Test: LD BC, nn (0x01)
TEST_F(CPUTest, LD_BC_nn_LoadsCorrectValue)
{
    cpu.testMemory[0x0000] = 0x01; // LD BC, 0x1234
    cpu.testMemory[0x0001] = 0x34;
    cpu.testMemory[0x0002] = 0x12;
    cpu.executeOpcode();

    EXPECT_EQ(cpu.BC(), 0x1234);
    EXPECT_EQ(cpu.PC, 3);
}

// Test: ADD A, B (0x80)
TEST_F(CPUTest, ADD_A_B_AddsCorrectly)
{
    cpu.A = 0x10;
    cpu.B = 0x05;
    cpu.testMemory[0x0000] = 0x80; // ADD A, B
    cpu.executeOpcode();

    EXPECT_EQ(cpu.A, 0x15);
}

// Run all tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
