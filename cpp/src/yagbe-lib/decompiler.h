#include <vector>

namespace Decompiler {

enum class InstructionCode {
    NOOP,
    INC_B,
    INC_D,
    INC_H,
    INC_C,
    INC_E,
    INC_L,
    INC_A,
    INC_BC,
    INC_DE,
    INC_HL,
    INC_SP,
    DEC_B,
    DEC_D,
    DEC_H,
    DEC_C,
    DEC_E,
    DEC_L,
    DEC_A,
    DEC_BC,
    DEC_DE,
    DEC_HL,
    DEC_SP,
    LD16_BC,
    LD16_DE,
    LD16_HL,
    LD16_SP,
};

struct Instruction {
    InstructionCode code;
    std::vector<std::byte> operands;
};

std::vector<Instruction> decompile(const std::vector<std::byte>& rom_bytes);

}
