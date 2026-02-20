/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** And gate component implementation
*/

#include "nts/components/AndGate.hpp"
#include "nts/TristateLogic.hpp"
#include "nts/Errors.hpp"

namespace nts {

    AndGate::AndGate(const std::string &name)
    {
        _name = name;
        setPin(1, Tristate::Undefined);
        setPin(2, Tristate::Undefined);
        setPin(3, Tristate::Undefined);
    }

    void AndGate::simulate(std::size_t tick)
    {
        _tick = tick;
    }

    Tristate AndGate::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 3)
            throw NtsException("AndGate: invalid pin " + std::to_string(pin));
        
        if (pin == 1 || pin == 2)
            return getLinkValue(pin);
        Tristate a = getLinkValue(1);
        Tristate b = getLinkValue(2);
        return TristateLogic::andGate(a, b);
    }

}
