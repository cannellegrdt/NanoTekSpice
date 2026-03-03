/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4040 chipset implementation
*/

#include "nts/components/C4040.hpp"
#include "nts/Errors.hpp"

namespace nts {

    C4040::C4040(const std::string &name)
        : _counter(0), _counter_next(0),
          _lastClock(Tristate::False)
    {
        _name = name;
    }

    void C4040::simulate(std::size_t tick)
    {
        _tick = tick;

        Tristate clock = getLinkValue(10);
        Tristate reset = getLinkValue(11);

        if (reset == True) {
            _counter_next = 0;
        } else {
            if (_lastClock == True && clock == False)
                _counter_next = (_counter + 1) % 4096;
        }
        _lastClock = clock;
        _counter = _counter_next;
    }

    Tristate C4040::compute(std::size_t pin)
    {
        if (pin == 8 || pin == 16)
            throw NtsException("C4040: pin " + std::to_string(pin) + " is a power pin");

        static const std::size_t outPins[] = {9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1};

        for (int i = 0; i < 12; i++) {
            if (pin == outPins[i])
                return ((_counter >> i) & 1) ? True : False;
        }

        if (pin == 10 || pin == 11)
            return getLinkValue(pin);

        throw NtsException("C4040: invalid pin " + std::to_string(pin));
    }

}
