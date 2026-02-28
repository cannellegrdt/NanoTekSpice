/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4008 chipset implementation
*/

#include "nts/components/C4008.hpp"
#include "nts/TristateLogic.hpp"
#include "nts/Errors.hpp"

namespace nts {

    C4008::C4008(const std::string &name)
    {
        _name = name;
    }

    void C4008::simulate(std::size_t tick)
    {
        _tick = tick;
    }

    Tristate C4008::compute(std::size_t pin)
    {
        if (pin == 8 || pin == 16)
            throw NtsException("C4008: pin " + std::to_string(pin) + " is a power pin");

        switch (pin) {
            case 1: case 2: case 3: case 4:
            case 5: case 6: case 7: case 9: case 15:
                return getLinkValue(pin);
            default: break;
        }

        static const std::size_t aPins[]   = {7, 5, 3, 1};
        static const std::size_t bPins[]   = {6, 4, 2, 15};
        static const std::size_t sumPins[] = {10, 11, 12, 13};

        Tristate carry = getLinkValue(9);
        Tristate sums[4];

        for (int i = 0; i < 4; i++) {
            Tristate a = getLinkValue(aPins[i]);
            Tristate b = getLinkValue(bPins[i]);
            Tristate axorb = TristateLogic::xorGate(a, b);
            sums[i] = TristateLogic::xorGate(axorb, carry);
            carry = TristateLogic::orGate(
                TristateLogic::andGate(a, b),
                TristateLogic::andGate(carry, axorb)
            );
        }

        for (int i = 0; i < 4; i++)
            if (pin == sumPins[i])
                return sums[i];

        if (pin == 14)
            return carry;

        throw NtsException("C4008: invalid pin " + std::to_string(pin));
    }

}
