#include "emulator.h"
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>

std::uint16_t Emulator::pc() const {
    return _pc;
}

const std::vector<std::uint8_t>& Emulator::rom() const {
    return _rom;
}

const std::vector<std::uint8_t>& Emulator::memory() const {
    return _memory;
}

void Emulator::loadROMFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open ROM file");
    }

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    _rom.resize(fileSize);
    file.read(reinterpret_cast<char*>(_rom.data()), fileSize);
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(_memory.data()), fileSize);
}

size_t Emulator::romSize() const {
    return _rom.size();
}

void Emulator::nextInstruction() {
    ++_pc;
}

std::uint8_t Emulator::currentInstruction() const {
    std::cout << std::hex << (int)_rom[0] << (int)_rom[1] << std::endl;
    return _rom[_pc];
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
