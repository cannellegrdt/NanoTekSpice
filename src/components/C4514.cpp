/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4514 chipset implementation
*/

#include "nts/components/C4514.hpp"
#include "nts/Errors.hpp"

namespace nts {

    C4514::C4514(const std::string &name)
        : _latchedAddress(0), _nextAddress(0),
          _lastStrobe(Tristate::Undefined)
    {
        _name = name;
    }

    void C4514::simulate(std::size_t tick)
    {
        _tick = tick;

        Tristate a0 = getLinkValue(2);
        Tristate a1 = getLinkValue(3);
        Tristate a2 = getLinkValue(21);
        Tristate a3 = getLinkValue(22);

        if (a0 == Undefined || a1 == Undefined || a2 == Undefined || a3 == Undefined) {
            _nextAddress = -1;
        } else {
            _nextAddress = (a3 == True ? 8 : 0) + (a2 == True ? 4 : 0)
                         + (a1 == True ? 2 : 0) + (a0 == True ? 1 : 0);
        }

        Tristate strobe = getLinkValue(1);
        if (strobe == True)
            _latchedAddress = _nextAddress;

        _lastStrobe = strobe;
    }

    Tristate C4514::compute(std::size_t pin)
    {
        if (pin == 12 || pin == 24)
            throw NtsException("C4514: pin " + std::to_string(pin) + " is a power pin");

        if (pin == 1 || pin == 2 || pin == 3 || pin == 21 || pin == 22 || pin == 23)
            return getLinkValue(pin);

        static const std::size_t outPins[] = {
            11, 9, 10, 8, 7, 6, 5, 4,
            18, 17, 20, 19, 14, 13, 16, 15
        };

        for (int i = 0; i < 16; i++) {
            if (pin == outPins[i]) {
                if (getLinkValue(23) == True)
                    return False;
                if (_latchedAddress == -1)
                    return Undefined;
                return (_latchedAddress == i) ? True : False;
            }
        }

        throw NtsException("C4514: invalid pin " + std::to_string(pin));
    }

}
