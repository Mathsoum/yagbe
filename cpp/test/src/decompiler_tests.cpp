
#include "gtest/gtest.h"
#include "decompiler.h"

namespace {

TEST(DecompilerTest, empty_binary) {
    std::vector<Decompiler::Instruction> instructions = Decompiler::decompile({});
    EXPECT_TRUE(instructions.empty());
}

}