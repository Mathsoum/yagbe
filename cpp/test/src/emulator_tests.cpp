
#include "gtest/gtest.h"
#include "emulator.h"

namespace {

TEST(EmulatorTest, test_PC) {
    auto emulator = Emulator{};
    EXPECT_EQ(emulator.pc(), 0);
    EXPECT_EQ(emulator.sp(), 0);
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

TEST(EmulatorTest, memory_init) {
    auto emulator = Emulator{};
    EXPECT_EQ(emulator.memory().capacity(), 0xFFFF);
}

TEST(EmulatorTest, memory_load_rom) {
    auto emulator = Emulator{};
    emulator.loadROMFromFile("Tetris.gb");
    EXPECT_EQ(emulator.memory().at(0x0000), 0xc3);
    EXPECT_EQ(emulator.memory().at(0x1FFF), 0x05);
    EXPECT_EQ(emulator.memory().at(0x2FFF), 0xfd);
    EXPECT_EQ(emulator.memory().at(0x3FFF), 0x2f);
    EXPECT_EQ(emulator.memory().at(0x4FFF), 0x15);
    EXPECT_EQ(emulator.memory().at(0x5FFF), 0x4c);
    EXPECT_EQ(emulator.memory().at(0x6FFF), 0x70);
    EXPECT_EQ(emulator.memory().at(0x7FFF), 0x00);
}

TEST(EmulatorTest, registers_init) {
    auto emulator = Emulator{};
    EXPECT_EQ(emulator.reg_a(), 0x00);
    EXPECT_EQ(emulator.reg_b(), 0x00);
    EXPECT_EQ(emulator.reg_c(), 0x00);
    EXPECT_EQ(emulator.reg_d(), 0x00);
    EXPECT_EQ(emulator.reg_e(), 0x00);
    EXPECT_EQ(emulator.reg_h(), 0x00);
    EXPECT_EQ(emulator.reg_l(), 0x00);
    EXPECT_EQ(emulator.reg_flags(), 0x00);

    emulator.set_reg_a(0x12);
    emulator.set_reg_b(0x34);
    emulator.set_reg_c(0x56);
    emulator.set_reg_d(0x78);
    emulator.set_reg_e(0x9A);
    emulator.set_reg_h(0xBC);
    emulator.set_reg_l(0xDE);
    emulator.set_reg_flags(0xF0);

    EXPECT_EQ(emulator.reg_a(), 0x12);
    EXPECT_EQ(emulator.reg_b(), 0x34);
    EXPECT_EQ(emulator.reg_c(), 0x56);
    EXPECT_EQ(emulator.reg_d(), 0x78);
    EXPECT_EQ(emulator.reg_e(), 0x9A);
    EXPECT_EQ(emulator.reg_h(), 0xBC);
    EXPECT_EQ(emulator.reg_l(), 0xDE);
    EXPECT_EQ(emulator.reg_flags(), 0xF0);

    EXPECT_EQ(emulator.reg_af(), 0x12F0);
    EXPECT_EQ(emulator.reg_bc(), 0x3456);
    EXPECT_EQ(emulator.reg_de(), 0x789A);
    EXPECT_EQ(emulator.reg_hl(), 0xBCDE);
}

TEST(EmulatorTest, execute_ld) {
    auto emulator = Emulator{};
    emulator.loadROM({
        0x01, 0x12, 0x34,   /* LD BC,d16 */
        0x11, 0x56, 0x78,   /* LD DE,d16 */
        0x21, 0x9A, 0xBC,   /* LD HL,d16 */
        0x31, 0xDE, 0xF0,   /* LD SP,d16 */
    });
    EXPECT_EQ(emulator.pc(), 0x0000);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0003);
    EXPECT_EQ(emulator.reg_bc(), 0x1234);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0006);
    EXPECT_EQ(emulator.reg_de(), 0x5678);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0009);
    EXPECT_EQ(emulator.reg_hl(), 0x9ABC);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x000C);
    EXPECT_EQ(emulator.sp(), 0xDEF0);
}

}
