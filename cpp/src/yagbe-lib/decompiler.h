#include <vector>

namespace Decompiler {

enum class Instruction {
    NOOP
};

std::vector<Instruction> decompile(const std::vector<std::byte>& rom_bytes);

}