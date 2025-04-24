
#include "gtest/gtest.h"
#include "emulator.h"

namespace {

TEST(EmulatorTest, test_PC) {
    auto emulator = Emulator{};
    EXPECT_EQ(emulator.pc(), 0);
    EXPECT_EQ(emulator.romSize(), 0);
}

TEST(EmulatorTest, load_binary_in_emulator) {
    auto emulator = Emulator{};
    emulator.loadROMFromFile("Tetris.gb");
    EXPECT_EQ(emulator.pc(), 0);
    EXPECT_EQ(emulator.romSize(), 32768);
}

TEST(EmulatorTest, get_rom_data) {
    auto emulator = Emulator{};
    emulator.loadROMFromFile("Tetris.gb");
    EXPECT_EQ(emulator.pc(), 0);
    EXPECT_EQ(emulator.romSize(), 32768);
    EXPECT_EQ(emulator.rom()[0], 0xc3);
    EXPECT_EQ(emulator.rom()[1], 0x0c);
    EXPECT_EQ(emulator.rom()[2], 0x02);
    EXPECT_EQ(emulator.rom()[3], 0x00);
}

TEST(EmulatorTest, advance_pc_and_current_instruction) {
    auto emulator = Emulator{};
    emulator.loadROMFromFile("Tetris.gb");
    EXPECT_EQ(emulator.romSize(), 32768);
    EXPECT_EQ(emulator.pc(), 0x0000);
    EXPECT_EQ(emulator.currentInstruction(), 0xc3);

    emulator.nextInstruction();
    EXPECT_EQ(emulator.pc(), 0x0001);
    EXPECT_EQ(emulator.currentInstruction(), 0x0c);
}


}
