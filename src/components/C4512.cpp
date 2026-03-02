/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4512 chipset implementation
*/

#include "nts/components/C4512.hpp"
#include "nts/Errors.hpp"

namespace nts {

    C4512::C4512(const std::string &name)
    {
        _name = name;
    }

    void C4512::simulate(std::size_t tick)
    {
        _tick = tick;
    }

    Tristate C4512::compute(std::size_t pin)
    {
        if (pin == 8 || pin == 16)
            throw NtsException("C4512: pin " + std::to_string(pin) + " is a power pin");

        static const std::size_t inputPins[] = {1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 15};
        for (std::size_t p : inputPins) {
            if (pin == p)
                return getLinkValue(pin);
        }

        if (pin == 14) {
            if (getLinkValue(15) != True)
                return Undefined;
            if (getLinkValue(10) == True)
                return False;
            Tristate a = getLinkValue(11);
            Tristate b = getLinkValue(12);
            Tristate c = getLinkValue(13);
            if (a == Undefined || b == Undefined || c == Undefined)
                return Undefined;
            int channel = (c == True ? 4 : 0) + (b == True ? 2 : 0) + (a == True ? 1 : 0);
            static const std::size_t dataPins[] = {1, 2, 3, 4, 5, 6, 7, 9};
            return getLinkValue(dataPins[channel]);
        }

        throw NtsException("C4512: invalid pin " + std::to_string(pin));
    }

}
