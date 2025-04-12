#include "decompiler.h"
#include <map>

const std::map<std::byte, Decompiler::InstructionCode> single_byte_instruction_map = {
    {std::byte(0x00), Decompiler::InstructionCode::NOOP},
    {std::byte(0x04), Decompiler::InstructionCode::INC_B},
    {std::byte(0x14), Decompiler::InstructionCode::INC_D},
    {std::byte(0x24), Decompiler::InstructionCode::INC_H},
    {std::byte(0x0C), Decompiler::InstructionCode::INC_C},
    {std::byte(0x1C), Decompiler::InstructionCode::INC_E},
    {std::byte(0x2C), Decompiler::InstructionCode::INC_L},
    {std::byte(0x3C), Decompiler::InstructionCode::INC_A},
    {std::byte(0x03), Decompiler::InstructionCode::INC_BC},
    {std::byte(0x13), Decompiler::InstructionCode::INC_DE},
    {std::byte(0x23), Decompiler::InstructionCode::INC_HL},
    {std::byte(0x33), Decompiler::InstructionCode::INC_SP},
    {std::byte(0x05), Decompiler::InstructionCode::DEC_B},
    {std::byte(0x15), Decompiler::InstructionCode::DEC_D},
    {std::byte(0x25), Decompiler::InstructionCode::DEC_H},
    {std::byte(0x0D), Decompiler::InstructionCode::DEC_C},
    {std::byte(0x1D), Decompiler::InstructionCode::DEC_E},
    {std::byte(0x2D), Decompiler::InstructionCode::DEC_L},
    {std::byte(0x3D), Decompiler::InstructionCode::DEC_A},
    {std::byte(0x0B), Decompiler::InstructionCode::DEC_BC},
    {std::byte(0x1B), Decompiler::InstructionCode::DEC_DE},
    {std::byte(0x2B), Decompiler::InstructionCode::DEC_HL},
    {std::byte(0x3B), Decompiler::InstructionCode::DEC_SP},
};

const std::map<std::byte, Decompiler::InstructionCode> triple_byte_instruction_map = {
    {std::byte(0x01), Decompiler::InstructionCode::LD16_BC},
    {std::byte(0x11), Decompiler::InstructionCode::LD16_DE},
    {std::byte(0x21), Decompiler::InstructionCode::LD16_HL},
    {std::byte(0x31), Decompiler::InstructionCode::LD16_SP}
};

std::vector<Decompiler::Instruction> Decompiler::decompile(const std::vector<std::byte>& rom_bytes)
{
    std::vector<Decompiler::Instruction> instructions;
    if (!rom_bytes.empty())
    {
        for (size_t index = 0 ; index < rom_bytes.size(); index++)
        {
            auto byte = rom_bytes[index];
            if (single_byte_instruction_map.find(byte) != single_byte_instruction_map.end())
            {
                auto instruction = Instruction{
                    .code = single_byte_instruction_map.at(byte)
                };
                instructions.push_back(instruction);
            }
            else if (triple_byte_instruction_map.find(byte) != triple_byte_instruction_map.end())
            {
                auto instruction = Instruction{
                    .code = triple_byte_instruction_map.at(byte)
                };
                instruction.operands = {rom_bytes[index + 1], rom_bytes[index + 2]};
                instructions.push_back(instruction);
                index += 2;
            }
        }
    }
    return instructions;
}
