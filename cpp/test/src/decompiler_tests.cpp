
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

TEST(DecompilerTest, increment_B) {
    auto instructions = Decompiler::decompile({std::byte{0x04}});
    EXPECT_EQ(instructions.size(), 1);
    EXPECT_EQ(instructions.at(0), Decompiler::Instruction::INC_B);
}

TEST(DecompilerTest, increment_D) {
    auto instructions = Decompiler::decompile({std::byte{0x14}});
    EXPECT_EQ(instructions.size(), 1);
    EXPECT_EQ(instructions.at(0), Decompiler::Instruction::INC_D);
}

TEST(DecompilerTest, increment_H) {
    auto instructions = Decompiler::decompile({std::byte{0x24}});
    EXPECT_EQ(instructions.size(), 1);
    EXPECT_EQ(instructions.at(0), Decompiler::Instruction::INC_H);
}

TEST(DecompilerTest, increment_C) {
    auto instructions = Decompiler::decompile({std::byte{0x0C}});
    EXPECT_EQ(instructions.size(), 1);
    EXPECT_EQ(instructions.at(0), Decompiler::Instruction::INC_C);
}

TEST(DecompilerTest, increment_E) {
    auto instructions = Decompiler::decompile({std::byte{0x1C}});
    EXPECT_EQ(instructions.size(), 1);
    EXPECT_EQ(instructions.at(0), Decompiler::Instruction::INC_E);
}

TEST(DecompilerTest, increment_L) {
    auto instructions = Decompiler::decompile({std::byte{0x2C}});
    EXPECT_EQ(instructions.size(), 1);
    EXPECT_EQ(instructions.at(0), Decompiler::Instruction::INC_L);
}

TEST(DecompilerTest, several_instructions) {
    auto instructions = Decompiler::decompile({std::byte{0x24}, std::byte{0x14}, std::byte{0x04}});
    EXPECT_EQ(instructions.size(), 3);
    EXPECT_EQ(instructions.at(0), Decompiler::Instruction::INC_H);
    EXPECT_EQ(instructions.at(1), Decompiler::Instruction::INC_D);
    EXPECT_EQ(instructions.at(2), Decompiler::Instruction::INC_B);
}

}
