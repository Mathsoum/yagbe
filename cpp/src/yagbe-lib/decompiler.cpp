#include "decompiler.h"

#include <cstdint>
#include <map>

const std::map<std::uint8_t, Decompiler::InstructionCode> no_operands_instruction_map = {
    {0x00, Decompiler::InstructionCode::NOOP},
    {0x04, Decompiler::InstructionCode::INC_B},
    {0x14, Decompiler::InstructionCode::INC_D},
    {0x24, Decompiler::InstructionCode::INC_H},
    {0x0C, Decompiler::InstructionCode::INC_C},
    {0x1C, Decompiler::InstructionCode::INC_E},
    {0x2C, Decompiler::InstructionCode::INC_L},
    {0x3C, Decompiler::InstructionCode::INC_A},
    {0x03, Decompiler::InstructionCode::INC_BC},
    {0x13, Decompiler::InstructionCode::INC_DE},
    {0x23, Decompiler::InstructionCode::INC_HL},
    {0x33, Decompiler::InstructionCode::INC_SP},
    {0x05, Decompiler::InstructionCode::DEC_B},
    {0x15, Decompiler::InstructionCode::DEC_D},
    {0x25, Decompiler::InstructionCode::DEC_H},
    {0x0D, Decompiler::InstructionCode::DEC_C},
    {0x1D, Decompiler::InstructionCode::DEC_E},
    {0x2D, Decompiler::InstructionCode::DEC_L},
    {0x3D, Decompiler::InstructionCode::DEC_A},
    {0x0B, Decompiler::InstructionCode::DEC_BC},
    {0x1B, Decompiler::InstructionCode::DEC_DE},
    {0x2B, Decompiler::InstructionCode::DEC_HL},
    {0x3B, Decompiler::InstructionCode::DEC_SP},
    {0xFF, Decompiler::InstructionCode::RST_38H}
};

const std::map<std::uint8_t, Decompiler::InstructionCode> unary_instruction_map = {
    {0x06, Decompiler::InstructionCode::LD8_B},
    {0x16, Decompiler::InstructionCode::LD8_D},
    {0x26, Decompiler::InstructionCode::LD8_H},
    {0x26, Decompiler::InstructionCode::LD8_H},
    {0x26, Decompiler::InstructionCode::LD8_H},
    {0x26, Decompiler::InstructionCode::LD8_H},
    {0x26, Decompiler::InstructionCode::LD8_H}
};

const std::map<std::uint8_t, Decompiler::InstructionCode> binary_instruction_map = {
    {0x01, Decompiler::InstructionCode::LD16_BC},
    {0x11, Decompiler::InstructionCode::LD16_DE},
    {0x21, Decompiler::InstructionCode::LD16_HL},
    {0x31, Decompiler::InstructionCode::LD16_SP},
    {0xC3, Decompiler::InstructionCode::JP_A16}
};

std::vector<Decompiler::Instruction> Decompiler::decompile(const std::vector<std::uint8_t>& rom_bytes)
{
    std::vector<Decompiler::Instruction> instructions;
    if (!rom_bytes.empty())
    {
        for (size_t index = 0 ; index < rom_bytes.size(); index++)
        {
            auto byte = rom_bytes[index];
            if (no_operands_instruction_map.find(byte) != no_operands_instruction_map.end())
            {
                auto instruction = Instruction{
                    .code = no_operands_instruction_map.at(byte)
                };
                instructions.push_back(instruction);
            }
            else if (unary_instruction_map.find(byte) != unary_instruction_map.end())
            {
                auto instruction = Instruction{
                    .code = unary_instruction_map.at(byte)
                };
                instruction.operands = {rom_bytes[index + 1]};
                instructions.push_back(instruction);
                index += 1;
            }
            else if (binary_instruction_map.find(byte) != binary_instruction_map.end())
            {
                auto instruction = Instruction{
                    .code = binary_instruction_map.at(byte)
                };
                instruction.operands = {rom_bytes[index + 1], rom_bytes[index + 2]};
                instructions.push_back(instruction);
                index += 2;
            }
        }
    }
    return instructions;
}
