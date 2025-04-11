#include <vector>

namespace Decompiler {

enum class Instruction {
    NOOP,
    INC_B,
    INC_D,
    INC_H,
};

std::vector<Instruction> decompile(const std::vector<std::byte>& rom_bytes);

}
