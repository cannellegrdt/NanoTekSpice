/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** FalseComp component implementation
*/

#include "nts/components/False.hpp"
#include "nts/Errors.hpp"

namespace nts {

    FalseComp::FalseComp(const std::string &name)
    {
        _name = name;
    }

    void FalseComp::simulate(std::size_t tick)
    {
        _tick = tick;
    }

    Tristate FalseComp::compute(std::size_t pin)
    {
        if (pin != 1)
            throw NtsException("FalseComp: invalid pin " + std::to_string(pin));
        return Tristate::False;
    }

}
