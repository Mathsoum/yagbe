#include <vector>

namespace Decompiler {

enum class Instruction {

};

std::vector<Instruction> decompile(const std::vector<std::byte>& rom_bytes);

}