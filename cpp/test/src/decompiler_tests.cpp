
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

}