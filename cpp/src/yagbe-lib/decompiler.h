#include <vector>

namespace Decompiler {

enum class Instruction {
    NOOP,
    INC_B
};

std::vector<Instruction> decompile(const std::vector<std::byte>& rom_bytes);

}
