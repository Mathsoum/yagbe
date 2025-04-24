#include <cstdint>
#include <string>
#include <vector>

class Emulator {
    public:
        std::uint16_t pc() const;
        std::vector<std::uint8_t> rom() const;
        void loadROMFromFile(const std::string& filename);
        size_t romSize() const;
        void nextInstruction();
        std::uint8_t currentInstruction() const;

    private:
        std::uint16_t _pc = 0;
        std::vector<std::uint8_t> _rom;
};
