#include <vector>

namespace Decompiler {

enum class Instruction {
    NOOP,
    INC_B,
    INC_D,
    INC_H,
    INC_C,
    INC_E,
    INC_L
};

std::vector<Instruction> decompile(const std::vector<std::byte>& rom_bytes);

}
