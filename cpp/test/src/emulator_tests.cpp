
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

}
