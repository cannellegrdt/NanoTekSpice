/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C2716 chipset implementation
*/

#include <fstream>
#include "nts/components/C2716.hpp"
#include "nts/Errors.hpp"

namespace nts {

    void C2716::loadFromFile(const std::string &path)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open())
            return;
        file.read(reinterpret_cast<char *>(_data.data()), 2048);
        std::streamsize bytesRead = file.gcount();
        for (std::streamsize i = bytesRead; i < 2048; i++)
            _data[i] = 0xFF;
    }

    C2716::C2716(const std::string &name)
        : _data(2048, 0xFF)
    {
        _name = name;
        loadFromFile("./rom.bin");
    }

    void C2716::simulate(std::size_t tick)
    {
        _tick = tick;
    }

    Tristate C2716::compute(std::size_t pin)
    {
        if (pin == 12 || pin == 21 || pin == 24)
            throw NtsException("C2716: pin " + std::to_string(pin) + " is a power pin");

        static const std::size_t inputPins[] = {18, 20, 8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19};
        for (std::size_t p : inputPins) {
            if (pin == p)
                return getLinkValue(pin);
        }

        static const std::size_t outputPins[] = {9, 10, 11, 13, 14, 15, 16, 17};
        for (std::size_t p : outputPins) {
            if (pin != p)
                continue;

            if (getLinkValue(18) != False)
                return Undefined;
            if (getLinkValue(20) != False)
                return Undefined;

            static const std::size_t addrPins[] = {8, 7, 6, 5, 4, 3, 2, 1, 23, 22, 19};
            std::size_t address = 0;
            for (int i = 0; i < 11; i++) {
                Tristate bit = getLinkValue(addrPins[i]);
                if (bit == Undefined)
                    return Undefined;
                if (bit == True)
                    address |= (1u << i);
            }

            uint8_t byte = _data[address];

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

        throw NtsException("C2716: invalid pin " + std::to_string(pin));
    }

}
