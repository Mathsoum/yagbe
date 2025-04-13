#include <cstdint>
#include <string>
#include <vector>

class Emulator {
    public:
        std::uint16_t pc() const;
        void loadROMFromFile(const std::string& filename);
        size_t romSize() const;

    private:
        std::uint16_t _pc = 0;
        std::vector<std::uint8_t> _rom;
};
