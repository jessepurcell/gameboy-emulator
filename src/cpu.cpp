#include "../include/cpu.hpp"
#include <iostream> // For debugging/logging

CPU::CPU() {
    reset();
}

void CPU::reset() {
    // Initialize registers to boot values (based on real Game Boy CPU)
    registers[AF] = 0x01B0;  // A = 0x01, F = 0xB0 (Flags)
    registers[BC] = 0x0013;
    registers[DE] = 0x00D8;
    registers[HL] = 0x014D;
    SP = 0xFFFE;
    PC = 0x0100;  // Game Boy boot ROM jumps to 0x0100

    clearFlags(); // Reset flags
}

std::expected<bool, std::string> CPU::executeNextInstruction() {
    uint8_t opcode = readByte(PC++); // Fetch next opcode
    try {
        executeInstruction(opcode);
    } catch (const std::exception& e) {
        return std::unexpected(std::string("CPU Error: ") + e.what());
    }
    return true; // Continue execution
}

void CPU::executeInstruction(uint8_t opcode) {
    switch (opcode) {
        case 0x00: // NOP (No Operation)
            break;
        case 0x76: // HALT instruction (stops CPU until an interrupt occurs)
            throw std::runtime_error("HALT executed");
        default:
            throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
    }
}

// Memory Access (to be replaced with MMU later)
uint8_t CPU::readByte(uint16_t address) {
    std::cerr << "Memory read at " << std::hex << address << std::endl;
    return 0xFF; // Stub return value
}

void CPU::writeByte(uint16_t address, uint8_t value) {
    std::cerr << "Memory write at " << std::hex << address << " value: " << std::hex << (int)value << std::endl;
}
