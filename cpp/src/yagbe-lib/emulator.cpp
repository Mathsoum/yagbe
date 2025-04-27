#include "emulator.h"
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>

void Emulator::runThis(const std::vector<std::uint8_t>& rom) {
    std::copy(rom.begin(), rom.end(), _memory.begin());
}

void Emulator::loadROMFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open ROM file");
    }

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    file.seekg(0x0100, std::ios::beg);
    file.read(reinterpret_cast<char*>(_memory.data()+0x0100), fileSize);

    std::copy(_boot_rom.begin(), _boot_rom.end(), _memory.begin());
}

std::uint16_t Emulator::pc() const {
    return _pc;
}

std::uint16_t Emulator::sp() const {
    return _sp;
}

const std::vector<std::uint8_t>& Emulator::memory() const {
    return _memory;
}

void Emulator::execute() {
    auto opcode = _memory.at(_pc);
    ++_pc;
    std::cout << "Executing opcode 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)opcode << " at PC 0x" << std::hex << std::setw(4) << std::setfill('0') << _pc << std::endl;
    if (opcode == LD16_BC) {
        auto op1 = _memory.at(_pc);
        ++_pc;
        auto op2 = _memory.at(_pc);
        ++_pc;
        auto d16 = op1 | (op2 << 8);
        _reg_bc = d16;
    } else if (opcode == LD16_DE) {
        auto op1 = _memory.at(_pc);
        ++_pc;
        auto op2 = _memory.at(_pc);
        ++_pc;
        auto d16 = op1 | (op2 << 8);
        _reg_de = d16;
    } else if (opcode == LD16_HL) {
        auto op1 = _memory.at(_pc);
        ++_pc;
        auto op2 = _memory.at(_pc);
        ++_pc;
        auto d16 = op1 | (op2 << 8);
        _reg_hl = d16;
    } else if (opcode == LD16_SP) {
        auto op1 = _memory.at(_pc);
        ++_pc;
        auto op2 = _memory.at(_pc);
        ++_pc;
        auto d16 = op1 | (op2 << 8);
        _sp = d16;
    } else if (opcode == LDHLi_A) {
        _memory.at(_reg_hl) = reg_a();
    } else if (opcode == LD8_A) {
        auto d8 = _memory.at(_pc);
        ++_pc;
        set_reg_a(d8);
    } else if (opcode == LD8_C) {
        auto d8 = _memory.at(_pc);
        ++_pc;
        set_reg_c(d8);
    } else if (opcode == INC_C) {
        if (reg_c() == 0x0F)
            set_reg_flags(reg_flags() | 0x20);
        else
            set_reg_flags(reg_flags() & ~0x20);

        set_reg_c(reg_c() + 1);

        if (reg_c() == 0)
            set_reg_flags(reg_flags() | 0x80);
    } else if (opcode == LDa8_A) {
        _memory.at((0xFF00 | _memory.at(_pc))) = reg_a();
        ++_pc;
    } else if (opcode == LDCi_A) {
        _memory.at((0xFF00 | reg_c())) = reg_a();
    } else if (opcode == LDaBC_A) {
        _memory.at(_reg_bc) = reg_a();
    } else if (opcode == LDaDE_A) {
        _memory.at(_reg_de) = reg_a();
    } else if (opcode == LDA_DEi) {
        set_reg_a(_memory.at(_reg_de));
        _reg_hl++;
    } else if (opcode == LDHLp) {
        _memory.at(_reg_hl) = reg_a();
        _reg_hl++;
    } else if (opcode == LDHLm) {
        _memory.at(_reg_hl) = reg_a();
        _reg_hl--;
    } else if (opcode == JPNZ_r8) {
        std::int8_t offset = _memory.at(_pc);
        ++_pc;
        if ((reg_flags() & 0x80) == 0)
            _pc += offset;
    } else if (opcode == XOR_A) {
        set_reg_a(0); // A ^ A will always result in A = 0;
        set_reg_flags(reg_flags() | 0x80);
    } else if (opcode == CB_PREFIX) {
        opcode = _memory.at(_pc);
        ++_pc;
        if (opcode == BIT7H) {
            auto bit = (reg_h() >> 7) & 1;
            if (bit)
                set_reg_flags(reg_flags() & 0x7F);
            else
                set_reg_flags(reg_flags() | 0x80);
            set_reg_flags(reg_flags() | 0x20);
        }
    } else {
        std::stringstream ss;
        ss << "Unknown opcode 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)opcode << " at PC 0x" << std::hex << std::setw(4) << std::setfill('0') << _pc;
        throw std::runtime_error(ss.str());
    }
}

void Emulator::set_reg_a(std::uint8_t value) {
    _reg_af = (value << 8) | (_reg_af & 0xFF);
}

void Emulator::set_reg_b(std::uint8_t value) {
    _reg_bc = (value << 8) | (_reg_bc & 0xFF);
}

void Emulator::set_reg_c(std::uint8_t value) {
    _reg_bc = (_reg_bc & 0xFF00) | value;
}

void Emulator::set_reg_d(std::uint8_t value) {
    _reg_de = (value << 8) | (_reg_de & 0xFF);
}

void Emulator::set_reg_e(std::uint8_t value) {
    _reg_de = (_reg_de & 0xFF00) | value;
}

void Emulator::set_reg_h(std::uint8_t value) {
    _reg_hl = (value << 8) | (_reg_hl & 0xFF);
}

void Emulator::set_reg_l(std::uint8_t value) {
    _reg_hl = (_reg_hl & 0xFF00) | value;
}

void Emulator::set_reg_flags(std::uint8_t value) {
    _reg_af = (_reg_af & 0xFF00) | value;
}

std::uint8_t Emulator::reg_a() const {
    return _reg_af >> 8;
}

std::uint8_t Emulator::reg_b() const {
    return _reg_bc >> 8;
}

std::uint8_t Emulator::reg_c() const {
    return _reg_bc & 0xFF;
}

std::uint8_t Emulator::reg_d() const {
    return _reg_de >> 8;
}

std::uint8_t Emulator::reg_e() const {
    return _reg_de & 0xFF;
}

std::uint8_t Emulator::reg_h() const {
    return _reg_hl >> 8;
}

std::uint8_t Emulator::reg_l() const {
    return _reg_hl & 0xFF;
}

std::uint8_t Emulator::reg_flags() const {
    return _reg_af & 0xFF;
}

std::uint16_t Emulator::reg_af() const {
    return _reg_af;
}

std::uint16_t Emulator::reg_bc() const {
    return _reg_bc;
}

std::uint16_t Emulator::reg_de() const {
    return _reg_de;
}

std::uint16_t Emulator::reg_hl() const {
    return _reg_hl;
}
