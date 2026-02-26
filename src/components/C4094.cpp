/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4094 chipset implementation
*/

#include "nts/components/C4094.hpp"
#include "nts/Errors.hpp"

namespace nts {

    C4094::C4094(const std::string &name)
        : _registers(8, Tristate::Undefined),
          _registers_next(8, Tristate::Undefined),
          _lastClock(Tristate::Undefined)
    {
        _name = name;
    }

    void C4094::simulate(std::size_t tick)
    {
        _tick = tick;

        Tristate clock = getLinkValue(3);

        if (_lastClock == False && clock == True) {
            for (int i = 7; i > 0; i--)
                _registers[i] = _registers[i - 1];
            _registers[0] = getLinkValue(2);
        }

        Tristate strobe = getLinkValue(1);
        if (strobe == True)
            _registers_next = _registers;

        _lastClock = clock;
    }

    Tristate C4094::compute(std::size_t pin)
    {
        if (pin == 8 || pin == 16)
            throw NtsException("C4094: pin " + std::to_string(pin) + " is a power pin");

        if (pin == 1 || pin == 2 || pin == 3 || pin == 15)
            return getLinkValue(pin);

        if (getLinkValue(15) != True)
            return Undefined;

        static const std::size_t outPins[] = {4, 5, 6, 7, 14, 13, 12, 11};

        for (int i = 0; i < 8; i++) {
            if (pin == outPins[i])
                return _registers_next[i];
        }

        if (pin == 9) return _registers[7];
        if (pin == 10) return _registers_next[7];

        throw NtsException("C4094: invalid pin " + std::to_string(pin));
    }

}
