
#include "gtest/gtest.h"
#include "emulator.h"

namespace {

TEST(EmulatorTest, test_PC) {
    auto emulator = Emulator{};
    EXPECT_EQ(emulator.pc(), 0);
    EXPECT_EQ(emulator.sp(), 0);
}

TEST(EmulatorTest, load_binary_in_emulator) {
    auto emulator = Emulator{};
    emulator.loadROMFromFile("Tetris.gb");
    EXPECT_EQ(emulator.pc(), 0);
}

TEST(EmulatorTest, get_rom_data) {
    auto emulator = Emulator{};
    emulator.loadROMFromFile("Tetris.gb");
    EXPECT_EQ(emulator.pc(), 0);
    EXPECT_EQ(emulator.memory()[0x0100], 0x00);
    EXPECT_EQ(emulator.memory()[0x0101], 0xc3);
    EXPECT_EQ(emulator.memory()[0x0102], 0x50);
    EXPECT_EQ(emulator.memory()[0x0103], 0x01);
}

TEST(EmulatorTest, boot_rom) {
    auto emulator = Emulator{};
    emulator.loadROMFromFile("Tetris.gb");
    EXPECT_EQ(emulator.pc(), 0);
    EXPECT_EQ(emulator.memory()[0x0000], 0x31);
    EXPECT_EQ(emulator.memory()[0x0001], 0xfe);
    EXPECT_EQ(emulator.memory()[0x0002], 0xff);
    EXPECT_EQ(emulator.memory()[0x0003], 0xaf);

    EXPECT_EQ(emulator.memory()[0x0040], 0x3e);
    EXPECT_EQ(emulator.memory()[0x0041], 0x19);
    EXPECT_EQ(emulator.memory()[0x0042], 0xea);
    EXPECT_EQ(emulator.memory()[0x0043], 0x10);

    EXPECT_EQ(emulator.memory()[0x00f0], 0xf5);
    EXPECT_EQ(emulator.memory()[0x00f1], 0x06);
    EXPECT_EQ(emulator.memory()[0x00f2], 0x19);
    EXPECT_EQ(emulator.memory()[0x00f3], 0x78);
}

TEST(EmulatorTest, memory_init) {
    auto emulator = Emulator{};
    EXPECT_EQ(emulator.memory().size(), 0xFFFF);
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
    emulator.runThis({
        0x01, 0x12, 0x34,   /* LD BC,d16 */
        0x11, 0x56, 0x78,   /* LD DE,d16 */
        0x21, 0x9A, 0xBC,   /* LD HL,d16 */
        0x31, 0xDE, 0xF0,   /* LD SP,d16 */

        0x3E, 0x01,         /* LD A,d8 */
        0x3E, 0x23,         /* LD A,d8 */
        0x0E, 0xAA,         /* LD C,d8 */
    });
    EXPECT_EQ(emulator.pc(), 0x0000);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0003);
    EXPECT_EQ(emulator.reg_bc(), 0x3412);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0006);
    EXPECT_EQ(emulator.reg_de(), 0x7856);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0009);
    EXPECT_EQ(emulator.reg_hl(), 0xBC9A);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x000C);
    EXPECT_EQ(emulator.sp(), 0xF0DE);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x000E);
    EXPECT_EQ(emulator.reg_a(), 0x01);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0010);
    EXPECT_EQ(emulator.reg_a(), 0x23);
    EXPECT_EQ(emulator.reg_c(), 0x12);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0012);
    EXPECT_EQ(emulator.reg_c(), 0xAA);
}

TEST(EmulatorTest, execute_indirect_ld) {
    auto emulator = Emulator{};
    emulator.runThis({
        0x01, 0x12, 0x34,   /* LD BC,d16  */
        0x3E, 0xBB,         /* LD A,d8    */
        0x02,               /* LD (BC),A  */
        0x11, 0x56, 0x78,   /* LD DE,d16  */
        0x3E, 0xCC,         /* LD A,d8    */
        0x12,               /* LD (DE),A  */
        0x21, 0x9A, 0xBC,   /* LD HL,d16  */
        0x3E, 0xDD,         /* LD A,d8    */
        0x22,               /* LD (HL+),A */
        0x3E, 0xEE,         /* LD A,d8    */
        0x32,               /* LD (HL-),A */
        0xE2,               /* LD (C),A   */
        0x77,               /* LD (HL),A  */
        0xE0, 0x90,         /* LD (a8),A  */
        0x1A,               /* LD A,(DE)  */
    });
    EXPECT_EQ(emulator.pc(), 0x0000);
    EXPECT_EQ(emulator.reg_a(), 0x00);

    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0003);
    EXPECT_EQ(emulator.reg_bc(), 0x3412);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0005);
    EXPECT_EQ(emulator.reg_a(), 0xBB);
    EXPECT_EQ(emulator.memory().at(0x3412), 0x00);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0006);
    EXPECT_EQ(emulator.memory().at(0x3412), 0xBB);

    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0009);
    EXPECT_EQ(emulator.reg_de(), 0x7856);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x000B);
    EXPECT_EQ(emulator.reg_a(), 0xCC);
    EXPECT_EQ(emulator.memory().at(0x7856), 0x00);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x000C);
    EXPECT_EQ(emulator.memory().at(0x7856), 0xCC);

    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x000F);
    EXPECT_EQ(emulator.reg_hl(), 0xBC9A);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0011);
    EXPECT_EQ(emulator.reg_a(), 0xDD);
    EXPECT_EQ(emulator.memory().at(0xBC9A), 0x00);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0012);
    EXPECT_EQ(emulator.memory().at(0xBC9A), 0xDD);
    EXPECT_EQ(emulator.reg_hl(), 0xBC9B);

    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0014);
    EXPECT_EQ(emulator.reg_a(), 0xEE);
    EXPECT_EQ(emulator.memory().at(0xBC9B), 0x00);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0015);
    EXPECT_EQ(emulator.memory().at(0xBC9B), 0xEE);
    EXPECT_EQ(emulator.reg_hl(), 0xBC9A);

    EXPECT_EQ(emulator.reg_a(), 0xEE);
    EXPECT_EQ(emulator.memory().at(0xFF12), 0x00);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0016);
    EXPECT_EQ(emulator.memory().at(0xFF12), 0xEE);

    EXPECT_EQ(emulator.reg_a(), 0xEE);
    EXPECT_EQ(emulator.memory().at(0xBC9A), 0xDD);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0017);
    EXPECT_EQ(emulator.memory().at(0xBC9A), 0xEE);

    EXPECT_EQ(emulator.reg_a(), 0xEE);
    EXPECT_EQ(emulator.memory().at(0xFF90), 0x00);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0019);
    EXPECT_EQ(emulator.memory().at(0xFF90), 0xEE);

    EXPECT_EQ(emulator.reg_a(), 0xEE);
    EXPECT_EQ(emulator.memory().at(0x7856), 0xCC);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x001A);
    EXPECT_EQ(emulator.reg_a(), 0xCC);
}

TEST(EmulateurTests, increments)
{
    auto emulator = Emulator{};
    emulator.runThis({
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
        0x0C,   /* INC C */
    });
    EXPECT_EQ(emulator.pc(), 0x0000);
    EXPECT_EQ(emulator.reg_c(), 0x00);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0001);
    EXPECT_EQ(emulator.reg_c(), 0x01);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0002);
    EXPECT_EQ(emulator.reg_c(), 0x02);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0003);
    EXPECT_EQ(emulator.reg_c(), 0x03);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0004);
    EXPECT_EQ(emulator.reg_c(), 0x04);
    emulator.execute();
    emulator.execute();
    emulator.execute();
    emulator.execute();
    emulator.execute();
    emulator.execute();
    emulator.execute();
    emulator.execute();
    emulator.execute();
    emulator.execute();
    emulator.execute();
    EXPECT_TRUE((emulator.reg_flags() & 0x20) == 0);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x00010);
    EXPECT_EQ(emulator.reg_c(), 0x10);
    EXPECT_TRUE((emulator.reg_flags() & 0x20) > 0);
}

TEST(EmulateurTests, xor_a)
{
    auto emulator = Emulator{};
    emulator.runThis({
        0x3E, 0xAA,         /* LD A,d8   */
        0xAF,               /* LD (BC),A */
    });

    EXPECT_EQ(emulator.reg_a(), 0x00);
    EXPECT_EQ(emulator.reg_flags(), 0x00);
    EXPECT_EQ(emulator.pc(), 0x00);
    emulator.execute();
    EXPECT_EQ(emulator.reg_a(), 0xAA);
    EXPECT_EQ(emulator.reg_flags(), 0x00);
    EXPECT_EQ(emulator.pc(), 0x02);
    emulator.execute();
    EXPECT_EQ(emulator.reg_a(), 0x00);
    EXPECT_EQ(emulator.reg_flags(), 0x80);
    EXPECT_EQ(emulator.pc(), 0x03);
}

TEST(EmulateurTests, bit7_h)
{
    auto emulator = Emulator{};
    emulator.runThis({
        0xCB, 0x7C,    /* BIT 7, H (0xCB prefix) */
    });

    EXPECT_EQ(emulator.reg_h(), 0x00);
    EXPECT_EQ(emulator.reg_flags(), 0x00);
    EXPECT_EQ(emulator.pc(), 0x00);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x02);
    EXPECT_EQ(emulator.reg_flags() & 0x80, 0x80);
    EXPECT_EQ(emulator.reg_flags() & 0x40, 0x00);
    EXPECT_EQ(emulator.reg_flags() & 0x20, 0x20);
}

TEST(EmulateurTests, JRNZ)
{
    auto emulator = Emulator{};
    emulator.runThis({
        0x3E, 0x01,         /* LD A,d8   */
        0x3E, 0x23,         /* LD A,d8   */
        0x20, 0x02,         /* JR NZ,d8  */
        0x3E, 0x45,         /* LD A,d8   */
        0x20, 0xFA,         /* JR NZ,d8  */
        0x3E, 0x67,         /* LD A,d8   */
    });

    EXPECT_EQ(emulator.reg_flags(), 0x00);
    EXPECT_EQ(emulator.pc(), 0x0000);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0002);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0004);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0008);
    emulator.set_reg_flags(0x00);
    EXPECT_EQ(emulator.reg_flags(), 0x00);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0004);
    emulator.set_reg_flags(0x80);
    EXPECT_EQ(emulator.reg_flags(), 0x80);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0006);
    emulator.execute();
    EXPECT_EQ(emulator.pc(), 0x0008);
}

}
