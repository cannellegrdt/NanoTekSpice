/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4017 chipset implementation
*/

#include "nts/components/C4017.hpp"
#include "nts/Errors.hpp"

namespace nts {

    C4017::C4017(const std::string &name)
        : _counter(0), _counter_next(0),
          _lastClock(Tristate::True)
    {
        _name = name;
    }

    void C4017::simulate(std::size_t tick)
    {
        _tick = tick;

        Tristate clock = getLinkValue(14);
        Tristate reset = getLinkValue(15);

        if (reset == True) {
            _counter_next = 0;
        } else {
            Tristate inhibit = getLinkValue(13);
            if (inhibit != True) {
                if (_lastClock == False && clock == True)
                    _counter_next = (_counter + 1) % 10;
            }
        }
        _lastClock = clock;
        _counter = _counter_next;
    }

    Tristate C4017::compute(std::size_t pin)
    {
        if (pin == 8 || pin == 16)
            throw NtsException("C4017: pin " + std::to_string(pin) + " is a power pin");

        static const std::size_t qPins[] = {3, 2, 4, 7, 10, 1, 5, 6, 9, 11};

        for (int i = 0; i < 10; i++) {
            if (pin == qPins[i])
                return (_counter == i) ? True : False;
        }

        if (pin == 12) {
            return (_counter < 5) ? True : False;
        }

        if (pin == 13 || pin == 14 || pin == 15)
            return getLinkValue(pin);

        throw NtsException("C4017: invalid pin " + std::to_string(pin));
    }

}
