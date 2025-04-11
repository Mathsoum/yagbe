#include "decompiler.h"
#include <map>

const std::map<std::byte, Decompiler::Instruction> instruction_map = {
    {std::byte(0x00), Decompiler::Instruction::NOOP},
    {std::byte(0x04), Decompiler::Instruction::INC_B},
    {std::byte(0x14), Decompiler::Instruction::INC_D},
    {std::byte(0x24), Decompiler::Instruction::INC_H},
    {std::byte(0x0C), Decompiler::Instruction::INC_C},
    {std::byte(0x1C), Decompiler::Instruction::INC_E},
    {std::byte(0x2C), Decompiler::Instruction::INC_L},
    {std::byte(0x3C), Decompiler::Instruction::INC_A},
    {std::byte(0x05), Decompiler::Instruction::DEC_B},
    {std::byte(0x15), Decompiler::Instruction::DEC_D},
    {std::byte(0x25), Decompiler::Instruction::DEC_H},
    {std::byte(0x0D), Decompiler::Instruction::DEC_C},
    {std::byte(0x1D), Decompiler::Instruction::DEC_E},
    {std::byte(0x2D), Decompiler::Instruction::DEC_L},
    {std::byte(0x3D), Decompiler::Instruction::DEC_A},
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
