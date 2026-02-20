/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Not gate component implementation
*/

#include "nts/components/NotGate.hpp"
#include "nts/TristateLogic.hpp"
#include "nts/Errors.hpp"

namespace nts {

    NotGate::NotGate(const std::string &name)
    {
        _name = name;
        setPin(1, Tristate::Undefined);
        setPin(2, Tristate::Undefined);
    }

    void NotGate::simulate(std::size_t tick)
    {
        _tick = tick;
    }

    Tristate NotGate::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 2)
            throw NtsException("NotGate: invalid pin " + std::to_string(pin));
        
        if (pin == 1)
            return getLinkValue(1);
        Tristate a = getLinkValue(1);
        return TristateLogic::notGate(a);
    }

}
