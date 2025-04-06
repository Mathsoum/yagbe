#include "decompiler.h"

std::vector<Decompiler::Instruction> Decompiler::decompile(const std::vector<std::byte>& rom_bytes)
{
    if (!rom_bytes.empty())
        return {Decompiler::Instruction::NOOP};
    return {};
}
