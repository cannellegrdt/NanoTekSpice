/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4801 chipset implementation
*/

#include "nts/components/C4801.hpp"
#include "nts/Errors.hpp"

namespace nts {

    C4801::C4801(const std::string &name)
        : _memory(1024, 0x00)
    {
        _name = name;
    }

    void C4801::simulate(std::size_t tick)
    {
        _tick = tick;

        for (auto &entry : _nextMemory)
            _memory[entry.first] = entry.second;
        _nextMemory.clear();

        if (getLinkValue(18) != True)
            return;

        Tristate we = getLinkValue(21);
        if (we != True)
            return;
        
        static const std::size_t addrPins[] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
        std::size_t address = 0;
        for (int i = 0; i < 10; i++) {
            Tristate bit = getLinkValue(addrPins[i]);
            if (bit == Undefined)
                return;
            if (bit == True)
                address |= (1u << i);
        }

        static const std:: size_t dataPins[] = {9, 10, 11, 13, 14, 15, 16, 17};
        uint8_t byte = 0;
        for (int i = 0; i < 8; i++) {
            Tristate bit = getLinkValue(dataPins[i]);
            if (bit == True)
                byte |= (1u << i);
        }

        _nextMemory[address]= byte;
    }

    Tristate C4801::compute(std::size_t pin)
    {
        if (pin == 12 || pin == 19 || pin == 24)
            throw NtsException("C4801: pin " + std::to_string(pin) + " is a power pin");
        
        static const std::size_t inputPins[] = {18, 21, 20, 8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
        for (std::size_t p : inputPins) {
            if (pin == p)
                return getLinkValue(pin);
        }

        static const std::size_t dataPins[] = {9, 10, 11, 13, 14, 15, 16, 17};
        for (std::size_t p : dataPins) {
            if (pin != p)
                continue;

            if (getLinkValue(18) != True)
                return Undefined;
            if (getLinkValue(20) != True)
                return Undefined;

            static const std::size_t addrPins[] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22};
            std::size_t address = 0;
            for (int i = 0; i < 10; ++i) {
                Tristate bit = getLinkValue(addrPins[i]);
                if (bit == Undefined)
                    return Undefined;
                if (bit == True)
                    address |= (1u << i);
            }

            uint8_t byte = _memory[address];

            int bitIndex = -1;
            switch (pin) {
                case 9:  bitIndex = 0; break;
                case 10: bitIndex = 1; break;
                case 11: bitIndex = 2; break;
                case 13: bitIndex = 3; break;
                case 14: bitIndex = 4; break;
                case 15: bitIndex = 5; break;
                case 16: bitIndex = 6; break;
                case 17: bitIndex = 7; break;
            }
            return (byte >> bitIndex) & 1 ? True : False;
        }

        throw NtsException("C4801: invalid pin " + std::to_string(pin));
    }

}
