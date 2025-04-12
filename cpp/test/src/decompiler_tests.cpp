
#include "gtest/gtest.h"
#include <fstream>
#include "decompiler.h"

namespace {

TEST(DecompilerTest, empty_binary) {
    auto instructions = Decompiler::decompile({});
    EXPECT_TRUE(instructions.empty());
}

TEST(DecompilerTest, noop) {
    auto instructions = Decompiler::decompile({std::byte{0x00}});
    EXPECT_EQ(instructions.size(), 1);
    EXPECT_EQ(instructions.at(0).code, Decompiler::InstructionCode::NOOP);
}

TEST(DecompilerTest, increment_single_bytes) {
    auto instructions = Decompiler::decompile({std::byte{0x04}, std::byte{0x14}, std::byte{0x24}, std::byte{0x0C}, std::byte{0x1C}, std::byte{0x2C}, std::byte{0x3C}});
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
    auto instructions = Decompiler::decompile({std::byte{0x05}, std::byte{0x15}, std::byte{0x25}, std::byte{0x0D}, std::byte{0x1D}, std::byte{0x2D}, std::byte{0x3D}});
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
        std::byte{0x03},
        std::byte{0x13},
        std::byte{0x23},
        std::byte{0x33},
        std::byte{0x0B},
        std::byte{0x1B},
        std::byte{0x2B},
        std::byte{0x3B}
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
        std::byte byte;
        ifs.read(reinterpret_cast<char*>(&byte), sizeof(std::byte));
        //TODO More tests
    }
}

TEST(DecompilerTest, LD_16bytes_instructions) {
    auto instructions = Decompiler::decompile({
        std::byte{0x01}, std::byte{0x01}, std::byte{0x23},
        std::byte{0x11}, std::byte{0x12}, std::byte{0x34},
        std::byte{0x21}, std::byte{0x23}, std::byte{0x45},
        std::byte{0x31}, std::byte{0x34}, std::byte{0x56},
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

}
