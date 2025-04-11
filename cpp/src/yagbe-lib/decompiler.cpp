#include "decompiler.h"
#include <map>

const std::map<std::byte, Decompiler::Instruction> instruction_map = {
    {std::byte(0x00), Decompiler::Instruction::NOOP},
    {std::byte(0x04), Decompiler::Instruction::INC_B},
    {std::byte(0x14), Decompiler::Instruction::INC_D},
    {std::byte(0x24), Decompiler::Instruction::INC_H}
};

std::vector<Decompiler::Instruction> Decompiler::decompile(const std::vector<std::byte>& rom_bytes)
{
    std::vector<Decompiler::Instruction> instructions;
    if (!rom_bytes.empty())
    {
        for (const auto& byte : rom_bytes)
        {
            if (instruction_map.find(byte) != instruction_map.end())
                instructions.push_back(instruction_map.at(byte));
        }
    }
    return instructions;
}
