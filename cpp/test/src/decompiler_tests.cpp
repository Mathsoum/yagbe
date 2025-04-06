
#include "gtest/gtest.h"
#include "decompiler.h"

namespace {

TEST(DecompilerTest, empty_binary) {
    auto instructions = Decompiler::decompile({});
    EXPECT_TRUE(instructions.empty());
}

}