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

    C4008::C4008(const std::string &name) : _carryOut(Tristate::Undefined)
    {
        _name = name;
        _pins[10] = Tristate::Undefined;
        _pins[11] = Tristate::Undefined;
        _pins[12] = Tristate::Undefined;
        _pins[13] = Tristate::Undefined;
        _pins[14] = Tristate::Undefined;
    }

    void C4008::simulate(std::size_t tick)
    {
        _tick = tick;

        static const std::size_t aPins[] = {1, 3, 5, 7};
        static const std::size_t bPins[] = {15, 2, 4, 6};
        static const std::size_t sumPins[] = {10, 11, 12, 13};

        Tristate carry = getLinkValue(9);

        for (int i = 0; i < 4; i++) {
            Tristate a = getLinkValue(aPins[i]);
            Tristate b = getLinkValue(bPins[i]);

            Tristate axorb = TristateLogic::xorGate(a, b);
            Tristate sum = TristateLogic::xorGate(axorb, carry);
            Tristate nextCarry = TristateLogic::orGate(
                TristateLogic::andGate(a, b),
                TristateLogic::andGate(carry, axorb)
            );

            _pins[sumPins[i]] = sum;
            carry = nextCarry;
        }

        _carryOut = carry;
        _pins[14] = _carryOut;
    }

    Tristate C4008::compute(std::size_t pin)
    {
        if (pin == 8 || pin == 16)
            throw NtsException("C4008: pin " + std::to_string(pin) + " is a power pin");

        switch (pin) {
            case 10: return _pins.at(10);
            case 11: return _pins.at(11);
            case 12: return _pins.at(12);
            case 13: return _pins.at(13);
            case 14: return _carryOut;
            case 1: case 2: case 3: case 4:
            case 5: case 6: case 7: case 9: case 15:
                return getLinkValue(pin);
            default:
                throw NtsException("C4008: invalid pin " + std::to_string(pin));
        }
    }

}
