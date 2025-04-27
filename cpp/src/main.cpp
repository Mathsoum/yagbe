#include <iomanip>
#include <iostream>

#include "emulator.h"

int main(int argc, const char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

    Emulator emulator;
    emulator.loadROMFromFile("Tetris.gb");
    std::cout << "Emulator loaded ROM successfully!" << std::endl;
    while (1)
    {
        emulator.execute();
        std::cout << "PC now at 0x" << std::hex << std::setw(2) << std::setfill('0') << (int)emulator.pc() << std::endl;
    }

    return 0;
}
