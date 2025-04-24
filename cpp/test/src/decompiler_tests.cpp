
#include "gtest/gtest.h"
#include <cstdint>
#include <fstream>
#include "decompiler.h"
#include "emulator.h"

namespace {

TEST(DecompilerTest, empty_binary) {
    auto instructions = Decompiler::decompile({});
    EXPECT_TRUE(instructions.empty());
}

TEST(DecompilerTest, noop) {
    auto instructions = Decompiler::decompile({0x00});
    EXPECT_EQ(instructions.size(), 1);
    EXPECT_EQ(instructions.at(0).code, Decompiler::InstructionCode::NOOP);
}

TEST(DecompilerTest, increment_single_bytes) {
    auto instructions = Decompiler::decompile({0x04, 0x14, 0x24, 0x0C, 0x1C, 0x2C, 0x3C});
    EXPECT_EQ(instructions.size(), 7);
    EXPECT_EQ(instructions.at(0).code, Decompiler::InstructionCode::INC_B);
    EXPECT_EQ(instructions.at(1).code, Decompiler::InstructionCode::INC_D);
    EXPECT_EQ(instructions.at(2).code, Decompiler::InstructionCode::INC_H);
    EXPECT_EQ(instructions.at(3).code, Decompiler::InstructionCode::INC_C);
    EXPECT_EQ(instructions.at(4).code, Decompiler::InstructionCode::INC_E);
    EXPECT_EQ(instructions.at(5).code, Decompiler::InstructionCode::INC_L);
    EXPECT_EQ(instructions.at(6).code, Decompiler::InstructionCode::INC_A);
}

TEST(DecompilerTest, decrement_single_bytes) {
    auto instructions = Decompiler::decompile({0x05, 0x15, 0x25, 0x0D, 0x1D, 0x2D, 0x3D});
    EXPECT_EQ(instructions.size(), 7);
    EXPECT_EQ(instructions.at(0).code, Decompiler::InstructionCode::DEC_B);
    EXPECT_EQ(instructions.at(1).code, Decompiler::InstructionCode::DEC_D);
    EXPECT_EQ(instructions.at(2).code, Decompiler::InstructionCode::DEC_H);
    EXPECT_EQ(instructions.at(3).code, Decompiler::InstructionCode::DEC_C);
    EXPECT_EQ(instructions.at(4).code, Decompiler::InstructionCode::DEC_E);
    EXPECT_EQ(instructions.at(5).code, Decompiler::InstructionCode::DEC_L);
    EXPECT_EQ(instructions.at(6).code, Decompiler::InstructionCode::DEC_A);
}

TEST(DecompilerTest, increment_decrement_single_and_multi_bytes) {
    auto instructions = Decompiler::decompile({
        0x03,
        0x13,
        0x23,
        0x33,
        0x0B,
        0x1B,
        0x2B,
        0x3B
    });

    EXPECT_EQ(instructions.size(), 8);
    EXPECT_EQ(instructions.at(0).code, Decompiler::InstructionCode::INC_BC);
    EXPECT_EQ(instructions.at(1).code, Decompiler::InstructionCode::INC_DE);
    EXPECT_EQ(instructions.at(2).code, Decompiler::InstructionCode::INC_HL);
    EXPECT_EQ(instructions.at(3).code, Decompiler::InstructionCode::INC_SP);
    EXPECT_EQ(instructions.at(4).code, Decompiler::InstructionCode::DEC_BC);
    EXPECT_EQ(instructions.at(5).code, Decompiler::InstructionCode::DEC_DE);
    EXPECT_EQ(instructions.at(6).code, Decompiler::InstructionCode::DEC_HL);
    EXPECT_EQ(instructions.at(7).code, Decompiler::InstructionCode::DEC_SP);
}

TEST(DecompilerTest, read_from_file) {
    std::ifstream ifs("Tetris.gb", std::ios::binary);
    EXPECT_TRUE(ifs.is_open());
    while(ifs.good()) {
        std::uint8_t byte;
        ifs.read(reinterpret_cast<char*>(&byte), sizeof(std::uint8_t));
        //TODO More tests
    }
}

TEST(DecompilerTest, LD_16bytes_instructions) {
    auto instructions = Decompiler::decompile({
        0x01, 0x01, 0x23,
        0x11, 0x12, 0x34,
        0x21, 0x23, 0x45,
        0x31, 0x34, 0x56,
    });

    EXPECT_EQ(instructions.size(), 4);
    EXPECT_EQ(instructions.at(0).code, Decompiler::InstructionCode::LD16_BC);
    EXPECT_EQ(instructions.at(0).operands.size(), 2);
    EXPECT_EQ(instructions.at(1).code, Decompiler::InstructionCode::LD16_DE);
    EXPECT_EQ(instructions.at(1).operands.size(), 2);
    EXPECT_EQ(instructions.at(2).code, Decompiler::InstructionCode::LD16_HL);
    EXPECT_EQ(instructions.at(2).operands.size(), 2);
    EXPECT_EQ(instructions.at(3).code, Decompiler::InstructionCode::LD16_SP);
    EXPECT_EQ(instructions.at(3).operands.size(), 2);
}

TEST(DecompilerTest, LD_8bytes_instructions) {
    auto instructions = Decompiler::decompile({
        0x06, 0x01,
        0x16, 0x12,
        0x26, 0x23,
    });

    EXPECT_EQ(instructions.size(), 3);
    EXPECT_EQ(instructions.at(0).code, Decompiler::InstructionCode::LD8_B);
    EXPECT_EQ(instructions.at(0).operands.size(), 1);
    EXPECT_EQ(instructions.at(1).code, Decompiler::InstructionCode::LD8_D);
    EXPECT_EQ(instructions.at(1).operands.size(), 1);
    EXPECT_EQ(instructions.at(2).code, Decompiler::InstructionCode::LD8_H);
    EXPECT_EQ(instructions.at(2).operands.size(), 1);
}

TEST(DecompilerTest, Tetris_first_row) {
    //0cc3 0002 0000 0000 0cc3 ff02 ffff ffff
    auto instructions = Decompiler::decompile({
        0x0c, 0xc3,
        0x00, 0x02,
        0x00, 0x00,
        0x00, 0x00,
        0x0C, 0xc3,
        0xff, 0x02,
        0xff, 0xff,
        0xff, 0xff,
    });

    EXPECT_EQ(instructions.size(), 12);
    EXPECT_EQ(instructions.at(0).code, Decompiler::InstructionCode::INC_C);
    EXPECT_TRUE(instructions.at(0).operands.empty());
    EXPECT_EQ(instructions.at(1).code, Decompiler::InstructionCode::JP_A16);
    EXPECT_EQ(instructions.at(1).operands.size(), 2);
}

}
