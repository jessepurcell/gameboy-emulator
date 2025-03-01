#include <gtest/gtest.h>

#include "../include/memory.hpp"

class MemoryTest : public ::testing::Test {
 protected:
  Memory mem;

  void SetUp() override {
    mem = Memory();  // Reset memory before each test
  }
};

// Test: Read & Write Byte
TEST_F(MemoryTest, ReadWriteByte) {
  mem.writeByte(0x1234, 0xAB);
  EXPECT_EQ(mem.readByte(0x1234), 0xAB);
}

// Test: Read & Write Word (16-bit)
TEST_F(MemoryTest, ReadWriteWord) {
  mem.writeWord(0x2000, 0xDEAD);
  EXPECT_EQ(mem.readWord(0x2000), 0xDEAD);
}

// Test: Uninitialized Memory Defaults to 0
TEST_F(MemoryTest, DefaultMemoryZero) { EXPECT_EQ(mem.readByte(0x5000), 0x00); }

// Test: Writing to Echo RAM (`E000-FDFF`) should affect `C000-DDFF`
// TEST_F(MemoryTest, EchoRAM) {
//     mem.writeByte(0xC000, 0x77);
//     EXPECT_EQ(mem.readByte(0xE000), 0x77);
// }

// Test: High RAM (`FF80-FFFE`)
TEST_F(MemoryTest, HighRAM) {
  mem.writeByte(0xFF80, 0x55);
  EXPECT_EQ(mem.readByte(0xFF80), 0x55);
}