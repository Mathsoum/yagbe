#include "decompiler.h"
#include <map>

const std::map<std::byte, Decompiler::Instruction> instruction_map = {
    {std::byte(0x00), Decompiler::Instruction::NOOP},
    {std::byte(0x03), Decompiler::Instruction::INC_B}
};

std::vector<Decompiler::Instruction> Decompiler::decompile(const std::vector<std::byte>& rom_bytes)
{
    if (!rom_bytes.empty())
    {
        if (instruction_map.find(rom_bytes[0]) != instruction_map.end())
            return { instruction_map.at(rom_bytes[0]) };
    }
    return {};
}
