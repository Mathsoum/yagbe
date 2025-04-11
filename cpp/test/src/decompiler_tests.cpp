
#include "gtest/gtest.h"
#include "decompiler.h"

namespace {

TEST(DecompilerTest, empty_binary) {
    std::vector<Decompiler::Instruction> instructions = Decompiler::decompile({});
    EXPECT_TRUE(instructions.empty());
}

TEST(DecompilerTest, noop) {
    auto instructions = Decompiler::decompile({std::byte{0x00}});
    EXPECT_EQ(instructions.size(), 1);
    EXPECT_EQ(instructions.at(0), Decompiler::Instruction::NOOP);
}

TEST(DecompilerTest, increment_single_bytes) {
    auto instructions = Decompiler::decompile({std::byte{0x04}, std::byte{0x14}, std::byte{0x24}, std::byte{0x0C}, std::byte{0x1C}, std::byte{0x2C}, std::byte{0x3C}});
    EXPECT_EQ(instructions.size(), 7);
    EXPECT_EQ(instructions.at(0), Decompiler::Instruction::INC_B);
    EXPECT_EQ(instructions.at(1), Decompiler::Instruction::INC_D);
    EXPECT_EQ(instructions.at(2), Decompiler::Instruction::INC_H);
    EXPECT_EQ(instructions.at(3), Decompiler::Instruction::INC_C);
    EXPECT_EQ(instructions.at(4), Decompiler::Instruction::INC_E);
    EXPECT_EQ(instructions.at(5), Decompiler::Instruction::INC_L);
    EXPECT_EQ(instructions.at(6), Decompiler::Instruction::INC_A);
}

TEST(DecompilerTest, decrement_single_bytes) {
    auto instructions = Decompiler::decompile({std::byte{0x05}, std::byte{0x15}, std::byte{0x25}, std::byte{0x0D}, std::byte{0x1D}, std::byte{0x2D}, std::byte{0x3D}});
    EXPECT_EQ(instructions.size(), 7);
    EXPECT_EQ(instructions.at(0), Decompiler::Instruction::DEC_B);
    EXPECT_EQ(instructions.at(1), Decompiler::Instruction::DEC_D);
    EXPECT_EQ(instructions.at(2), Decompiler::Instruction::DEC_H);
    EXPECT_EQ(instructions.at(3), Decompiler::Instruction::DEC_C);
    EXPECT_EQ(instructions.at(4), Decompiler::Instruction::DEC_E);
    EXPECT_EQ(instructions.at(5), Decompiler::Instruction::DEC_L);
    EXPECT_EQ(instructions.at(6), Decompiler::Instruction::DEC_A);
}

}
