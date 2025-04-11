#include <vector>

namespace Decompiler {

enum class Instruction {
    NOOP,
    INC_B,
    INC_D,
    INC_H,
    INC_C,
    INC_E,
    INC_L,
    INC_A,
    DEC_B,
    DEC_D,
    DEC_H,
    DEC_C,
    DEC_E,
    DEC_L,
    DEC_A,
};

std::vector<Instruction> decompile(const std::vector<std::byte>& rom_bytes);

}
