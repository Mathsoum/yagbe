#include "emulator.h"
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>

std::uint16_t Emulator::pc() const {
    return _pc;
}

std::vector<std::uint8_t> Emulator::rom() const {
    return _rom;
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
