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

// ✅ **Test: LOAD C, B (0x48 opcode)**
TEST_F(CPUTest, LoadC_B) {
    cpu.C = 0x12;
    cpu.B = 0x34;
    memory.writeByte(0x0000, 0x48); // LD C, B
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x48

    EXPECT_EQ(cpu.C, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD C, C (0x49 opcode)**
TEST_F(CPUTest, LoadC_C) {
    cpu.C = 0x12;
    memory.writeByte(0x0000, 0x49); // LD C, C
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x49

    EXPECT_EQ(cpu.C, 0x12);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD C, D (0x4A opcode)**
TEST_F(CPUTest, LoadC_D) {
    cpu.C = 0x12;
    cpu.D = 0x34;
    memory.writeByte(0x0000, 0x4A); // LD C, D
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x4A

    EXPECT_EQ(cpu.C, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD C, E (0x4B opcode)**
TEST_F(CPUTest, LoadC_E) {
    cpu.C = 0x12;
    cpu.E = 0x34;
    memory.writeByte(0x0000, 0x4B); // LD C, E
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x4B

    EXPECT_EQ(cpu.C, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD C, H (0x4C opcode)**
TEST_F(CPUTest, LoadC_H) {
    cpu.C = 0x12;
    cpu.H = 0x34;
    memory.writeByte(0x0000, 0x4C); // LD C, H
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x4C

    EXPECT_EQ(cpu.C, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD C, L (0x4D opcode)**
TEST_F(CPUTest, LoadC_L) {
    cpu.C = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x0000, 0x4D); // LD C, L
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x4D

    EXPECT_EQ(cpu.C, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD C, (HL) (0x4E opcode)**
TEST_F(CPUTest, LoadC_HL) {
    cpu.C = 0x12;
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x1234, 0x56); // Value at address HL
    memory.writeByte(0x0000, 0x4E); // LD C, (HL)
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x4E

    EXPECT_EQ(cpu.C, 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD C, A (0x4F opcode)**
TEST_F(CPUTest, LoadC_A) {
    cpu.C = 0x12;
    cpu.A = 0x34;
    memory.writeByte(0x0000, 0x4F); // LD C, A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x4F

    EXPECT_EQ(cpu.C, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD D, B (0x50 opcode)**
TEST_F(CPUTest, LoadD_B) {
    cpu.D = 0x12;
    cpu.B = 0x34;
    memory.writeByte(0x0000, 0x50); // LD D, B
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x50

    EXPECT_EQ(cpu.D, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD D, C (0x51 opcode)**
TEST_F(CPUTest, LoadD_C) {
    cpu.D = 0x12;
    cpu.C = 0x34;
    memory.writeByte(0x0000, 0x51); // LD D, C
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x51

    EXPECT_EQ(cpu.D, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD D, D (0x52 opcode)**
TEST_F(CPUTest, LoadD_D) {
    cpu.D = 0x12;
    memory.writeByte(0x0000, 0x52); // LD D, D
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x52

    EXPECT_EQ(cpu.D, 0x12);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD D, E (0x53 opcode)**
TEST_F(CPUTest, LoadD_E) {
    cpu.D = 0x12;
    cpu.E = 0x34;
    memory.writeByte(0x0000, 0x53); // LD D, E
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x53

    EXPECT_EQ(cpu.D, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD D, H (0x54 opcode)**
TEST_F(CPUTest, LoadD_H) {
    cpu.D = 0x12;
    cpu.H = 0x34;
    memory.writeByte(0x0000, 0x54); // LD D, H
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x54

    EXPECT_EQ(cpu.D, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD D, L (0x55 opcode)**
TEST_F(CPUTest, LoadD_L) {
    cpu.D = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x0000, 0x55); // LD D, L
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x55

    EXPECT_EQ(cpu.D, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD D, (HL) (0x56 opcode)**
TEST_F(CPUTest, LoadD_HL) {
    cpu.D = 0x12;
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x1234, 0x56); // Value at address HL
    memory.writeByte(0x0000, 0x56); // LD D, (HL)
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x56

    EXPECT_EQ(cpu.D, 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD D, A (0x57 opcode)**
TEST_F(CPUTest, LoadD_A) {
    cpu.D = 0x12;
    cpu.A = 0x34;
    memory.writeByte(0x0000, 0x57); // LD D, A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x57

    EXPECT_EQ(cpu.D, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD E, B (0x58 opcode)**
TEST_F(CPUTest, LoadE_B) {
    cpu.E = 0x12;
    cpu.B = 0x34;
    memory.writeByte(0x0000, 0x58); // LD E, B
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x58

    EXPECT_EQ(cpu.E, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD E, C (0x59 opcode)**
TEST_F(CPUTest, LoadE_C) {
    cpu.E = 0x12;
    cpu.C = 0x34;
    memory.writeByte(0x0000, 0x59); // LD E, C
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x59

    EXPECT_EQ(cpu.E, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD E, D (0x5A opcode)**
TEST_F(CPUTest, LoadE_D) {
    cpu.E = 0x12;
    cpu.D = 0x34;
    memory.writeByte(0x0000, 0x5A); // LD E, D
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x5A

    EXPECT_EQ(cpu.E, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD E, E (0x5B opcode)**
TEST_F(CPUTest, LoadE_E) {
    cpu.E = 0x12;
    memory.writeByte(0x0000, 0x5B); // LD E, E
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x5B

    EXPECT_EQ(cpu.E, 0x12);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD E, H (0x5C opcode)**
TEST_F(CPUTest, LoadE_H) {
    cpu.E = 0x12;
    cpu.H = 0x34;
    memory.writeByte(0x0000, 0x5C); // LD E, H
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x5C

    EXPECT_EQ(cpu.E, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD E, L (0x5D opcode)**
TEST_F(CPUTest, LoadE_L) {
    cpu.E = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x0000, 0x5D); // LD E, L
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x5D

    EXPECT_EQ(cpu.E, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD E, (HL) (0x5E opcode)**
TEST_F(CPUTest, LoadE_HL) {
    cpu.E = 0x12;
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x1234, 0x56); // Value at address HL
    memory.writeByte(0x0000, 0x5E); // LD E, (HL)
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x5E

    EXPECT_EQ(cpu.E, 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD E, A (0x5F opcode)**
TEST_F(CPUTest, LoadE_A) {
    cpu.E = 0x12;
    cpu.A = 0x34;
    memory.writeByte(0x0000, 0x5F); // LD E, A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x5F

    EXPECT_EQ(cpu.E, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD H, B (0x60 opcode)**
TEST_F(CPUTest, LoadH_B) {
    cpu.H = 0x12;
    cpu.B = 0x34;
    memory.writeByte(0x0000, 0x60); // LD H, B
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x60

    EXPECT_EQ(cpu.H, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD H, C (0x61 opcode)**
TEST_F(CPUTest, LoadH_C) {
    cpu.H = 0x12;
    cpu.C = 0x34;
    memory.writeByte(0x0000, 0x61); // LD H, C
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x61

    EXPECT_EQ(cpu.H, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD H, D (0x62 opcode)**
TEST_F(CPUTest, LoadH_D) {
    cpu.H = 0x12;
    cpu.D = 0x34;
    memory.writeByte(0x0000, 0x62); // LD H, D
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x62

    EXPECT_EQ(cpu.H, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD H, E (0x63 opcode)**
TEST_F(CPUTest, LoadH_E) {
    cpu.H = 0x12;
    cpu.E = 0x34;
    memory.writeByte(0x0000, 0x63); // LD H, E
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x63

    EXPECT_EQ(cpu.H, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD H, H (0x64 opcode)**
TEST_F(CPUTest, LoadH_H) {
    cpu.H = 0x12;
    memory.writeByte(0x0000, 0x64); // LD H, H
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x64

    EXPECT_EQ(cpu.H, 0x12);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD H, L (0x65 opcode)**
TEST_F(CPUTest, LoadH_L) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x0000, 0x65); // LD H, L
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x65

    EXPECT_EQ(cpu.H, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD H, (HL) (0x66 opcode)**
TEST_F(CPUTest, LoadH_HL) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x1234, 0x56); // Value at address HL
    memory.writeByte(0x0000, 0x66); // LD H, (HL)
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x66

    EXPECT_EQ(cpu.H, 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD H, A (0x67 opcode)**
TEST_F(CPUTest, LoadH_A) {
    cpu.H = 0x12;
    cpu.A = 0x34;
    memory.writeByte(0x0000, 0x67); // LD H, A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x67

    EXPECT_EQ(cpu.H, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD L, B (0x68 opcode)**
TEST_F(CPUTest, LoadL_B) {
    cpu.L = 0x12;
    cpu.B = 0x34;
    memory.writeByte(0x0000, 0x68); // LD L, B
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x68

    EXPECT_EQ(cpu.L, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD L, C (0x69 opcode)**
TEST_F(CPUTest, LoadL_C) {
    cpu.L = 0x12;
    cpu.C = 0x34;
    memory.writeByte(0x0000, 0x69); // LD L, C
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x69

    EXPECT_EQ(cpu.L, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD L, D (0x6A opcode)**
TEST_F(CPUTest, LoadL_D) {
    cpu.L = 0x12;
    cpu.D = 0x34;
    memory.writeByte(0x0000, 0x6A); // LD L, D
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x6A

    EXPECT_EQ(cpu.L, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD L, E (0x6B opcode)**
TEST_F(CPUTest, LoadL_E) {
    cpu.L = 0x12;
    cpu.E = 0x34;
    memory.writeByte(0x0000, 0x6B); // LD L, E
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x6B

    EXPECT_EQ(cpu.L, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD L, H (0x6C opcode)**
TEST_F(CPUTest, LoadL_H) {
    cpu.L = 0x12;
    cpu.H = 0x34;
    memory.writeByte(0x0000, 0x6C); // LD L, H
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x6C

    EXPECT_EQ(cpu.L, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD L, L (0x6D opcode)**
TEST_F(CPUTest, LoadL_L) {
    cpu.L = 0x12;
    memory.writeByte(0x0000, 0x6D); // LD L, L
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x6D

    EXPECT_EQ(cpu.L, 0x12);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD L, (HL) (0x6E opcode)**
TEST_F(CPUTest, LoadL_HL) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x1234, 0x56); // Value at address HL
    memory.writeByte(0x0000, 0x6E); // LD L, (HL)
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x6E

    EXPECT_EQ(cpu.L, 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD L, A (0x6F opcode)**
TEST_F(CPUTest, LoadL_A) {
    cpu.L = 0x12;
    cpu.A = 0x34;
    memory.writeByte(0x0000, 0x6F); // LD L, A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x6F

    EXPECT_EQ(cpu.L, 0x34);
    EXPECT_EQ(cpu.PC, 1);
}
// ✅ **Test: LOAD B, n (0x06 opcode)**
TEST_F(CPUTest, LoadB_n) {
    memory.writeByte(0x0000, 0x06); // LD B, n
    memory.writeByte(0x0001, 0x34); // Immediate value
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x06

    EXPECT_EQ(cpu.B, 0x34);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD C, n (0x0E opcode)**
TEST_F(CPUTest, LoadC_n) {
    memory.writeByte(0x0000, 0x0E); // LD C, n
    memory.writeByte(0x0001, 0x34); // Immediate value
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x0E

    EXPECT_EQ(cpu.C, 0x34);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD D, n (0x16 opcode)**
TEST_F(CPUTest, LoadD_n) {
    memory.writeByte(0x0000, 0x16); // LD D, n
    memory.writeByte(0x0001, 0x34); // Immediate value
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x16

    EXPECT_EQ(cpu.D, 0x34);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD E, n (0x1E opcode)**
TEST_F(CPUTest, LoadE_n) {
    memory.writeByte(0x0000, 0x1E); // LD E, n
    memory.writeByte(0x0001, 0x34); // Immediate value
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x1E

    EXPECT_EQ(cpu.E, 0x34);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD H, n (0x26 opcode)**
TEST_F(CPUTest, LoadH_n) {
    memory.writeByte(0x0000, 0x26); // LD H, n
    memory.writeByte(0x0001, 0x34); // Immediate value
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x26

    EXPECT_EQ(cpu.H, 0x34);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD L, n (0x2E opcode)**
TEST_F(CPUTest, LoadL_n) {
    memory.writeByte(0x0000, 0x2E); // LD L, n
    memory.writeByte(0x0001, 0x34); // Immediate value
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x2E

    EXPECT_EQ(cpu.L, 0x34);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD A, n (0x3E opcode)**
TEST_F(CPUTest, LoadA_n) {
    memory.writeByte(0x0000, 0x3E); // LD A, n
    memory.writeByte(0x0001, 0x34); // Immediate value
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x3E

    EXPECT_EQ(cpu.A, 0x34);
    EXPECT_EQ(cpu.PC, 2);
}
// ✅ **Test: LOAD BC, nn (0x01 opcode)**
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

// ✅ **Test: LOAD DE, nn (0x11 opcode)**
TEST_F(CPUTest, LoadDEImmediate) {
    memory.writeByte(0x0000, 0x11); // LD DE, 0x5678
    memory.writeByte(0x0001, 0x78);
    memory.writeByte(0x0002, 0x56);
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x11

    EXPECT_EQ(cpu.D, 0x56);
    EXPECT_EQ(cpu.E, 0x78);
    EXPECT_EQ(cpu.DE(), 0x5678);
    EXPECT_EQ(cpu.PC, 3);
}

// ✅ **Test: LOAD HL, nn (0x21 opcode)**
TEST_F(CPUTest, LoadHLImmediate) {
    memory.writeByte(0x0000, 0x21); // LD HL, 0x9ABC
    memory.writeByte(0x0001, 0xBC);
    memory.writeByte(0x0002, 0x9A);
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x21

    EXPECT_EQ(cpu.H, 0x9A);
    EXPECT_EQ(cpu.L, 0xBC);
    EXPECT_EQ(cpu.HL(), 0x9ABC);
    EXPECT_EQ(cpu.PC, 3);
}

// ✅ **Test: LOAD SP, nn (0x31 opcode)**
TEST_F(CPUTest, LoadSPImmediate) {
    memory.writeByte(0x0000, 0x31); // LD SP, 0xDEF0
    memory.writeByte(0x0001, 0xF0);
    memory.writeByte(0x0002, 0xDE);
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x31

    EXPECT_EQ(cpu.SP, 0xDEF0);
    EXPECT_EQ(cpu.PC, 3);
}
// ✅ **Test: LOAD (HL), B (0x70 opcode)**
TEST_F(CPUTest, LoadHL_B) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    cpu.B = 0x56;
    memory.writeByte(0x0000, 0x70); // LD (HL), B
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x70

    EXPECT_EQ(memory.readByte(0x1234), 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD (HL), C (0x71 opcode)**
TEST_F(CPUTest, LoadHL_C) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    cpu.C = 0x56;
    memory.writeByte(0x0000, 0x71); // LD (HL), C
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x71

    EXPECT_EQ(memory.readByte(0x1234), 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD (HL), D (0x72 opcode)**
TEST_F(CPUTest, LoadHL_D) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    cpu.D = 0x56;
    memory.writeByte(0x0000, 0x72); // LD (HL), D
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x72

    EXPECT_EQ(memory.readByte(0x1234), 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD (HL), E (0x73 opcode)**
TEST_F(CPUTest, LoadHL_E) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    cpu.E = 0x56;
    memory.writeByte(0x0000, 0x73); // LD (HL), E
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x73

    EXPECT_EQ(memory.readByte(0x1234), 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD (HL), H (0x74 opcode)**
TEST_F(CPUTest, LoadHL_H) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x0000, 0x74); // LD (HL), H
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x74

    EXPECT_EQ(memory.readByte(0x1234), 0x12);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD (HL), L (0x75 opcode)**
TEST_F(CPUTest, LoadHL_L) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x0000, 0x75); // LD (HL), L
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x75

    EXPECT_EQ(memory.readByte(0x1234), 0x34);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD (HL), A (0x77 opcode)**
TEST_F(CPUTest, LoadHL_A) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    cpu.A = 0x56;
    memory.writeByte(0x0000, 0x77); // LD (HL), A
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x77

    EXPECT_EQ(memory.readByte(0x1234), 0x56);
    EXPECT_EQ(cpu.PC, 1);
}

// ✅ **Test: LOAD (HL), n (0x36 opcode)**
TEST_F(CPUTest, LoadHL_n) {
    cpu.H = 0x12;
    cpu.L = 0x34;
    memory.writeByte(0x0000, 0x36); // LD (HL), n
    memory.writeByte(0x0001, 0x56); // Immediate value
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x36

    EXPECT_EQ(memory.readByte(0x1234), 0x56);
    EXPECT_EQ(cpu.PC, 2);
}

// ✅ **Test: LOAD A, (BC) (0x0A opcode)**
TEST_F(CPUTest, LoadA_BC) {
    cpu.A = 0x0;
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
    cpu.A = 0x0;
    cpu.D = 0x12;
    cpu.E = 0x34;
    memory.writeByte(0x1234, 0x56); // Value at address DE
    memory.writeByte(0x0000, 0x1A); // LD A, (DE)
    cpu.PC = 0;

    cpu.executeOpcode(); // Execute opcode 0x1A

    EXPECT_EQ(cpu.A, 0x56);
    EXPECT_EQ(cpu.PC, 1);
}