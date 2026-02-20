/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** NorGate component implementation
*/

#include "nts/components/NorGate.hpp"
#include "nts/Errors.hpp"
#include "nts/TristateLogic.hpp"

namespace nts {

    NorGate::NorGate(const std::string &name)
    {
        _name = name;
        setPin(1, Tristate::Undefined);
        setPin(2, Tristate::Undefined);
        setPin(3, Tristate::Undefined);
    }

    void NorGate::simulate(std::size_t tick)
    {
        _tick = tick;
    }

    Tristate NorGate::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 3)
            throw NtsException("NorGate: invalid pin " + std::to_string(pin));
        
        if (pin == 1 || pin == 2)
            return getLinkValue(pin);
        Tristate a = getLinkValue(1);
        Tristate b = getLinkValue(2);
        return TristateLogic::norGate(a, b);
    }

}
