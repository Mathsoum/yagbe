#include <cstdint>
#include <string>
#include <vector>

class Emulator {

    static constexpr std::uint8_t LD16_BC = 0x01;
    static constexpr std::uint8_t LD16_DE = 0x11;
    static constexpr std::uint8_t LD16_HL = 0x21;
    static constexpr std::uint8_t LD16_SP = 0x31;

    static constexpr std::uint8_t LD8_A = 0x3E;

    static constexpr std::uint8_t LDaBC_A = 0x02;
    static constexpr std::uint8_t LDaDE_A = 0x12;

    static constexpr std::uint8_t LDHLp = 0x22;
    static constexpr std::uint8_t LDHLm = 0x32;

    public:
        Emulator() : _memory(0xFFFF) {}

        void loadROMFromFile(const std::string& filename);
        void loadROM(const std::vector<std::uint8_t>& rom);

        const std::vector<std::uint8_t>& rom() const;
        size_t romSize() const;

        void execute();

        void nextInstruction();
        std::uint8_t currentInstruction() const;
        const std::vector<std::uint8_t>& memory() const;

        std::uint16_t pc() const;
        std::uint16_t sp() const;

        std::uint8_t reg_a() const;
        std::uint8_t reg_b() const;
        std::uint8_t reg_c() const;
        std::uint8_t reg_d() const;
        std::uint8_t reg_e() const;
        std::uint8_t reg_h() const;
        std::uint8_t reg_l() const;
        std::uint8_t reg_flags() const;

        std::uint16_t reg_af() const;
        std::uint16_t reg_bc() const;
        std::uint16_t reg_de() const;
        std::uint16_t reg_hl() const;

        void set_reg_a(std::uint8_t value);
        void set_reg_b(std::uint8_t value);
        void set_reg_c(std::uint8_t value);
        void set_reg_d(std::uint8_t value);
        void set_reg_e(std::uint8_t value);
        void set_reg_h(std::uint8_t value);
        void set_reg_l(std::uint8_t value);
        void set_reg_flags(std::uint8_t value);

    private:
        std::uint16_t _pc = 0;
        std::uint16_t _sp = 0;

        std::vector<std::uint8_t> _rom;
        std::vector<std::uint8_t> _memory;

        std::uint16_t _reg_af = 0;
        std::uint16_t _reg_bc = 0;
        std::uint16_t _reg_de = 0;
        std::uint16_t _reg_hl = 0;
};
