#include <vector>

namespace Decompiler {

enum class Instruction {
    NOOP,
    INC_B,
    INC_D,
};

std::vector<Instruction> decompile(const std::vector<std::byte>& rom_bytes);

}
