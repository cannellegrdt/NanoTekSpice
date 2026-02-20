/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** TrueComp component implementation
*/

#include "nts/components/True.hpp"
#include "nts/Errors.hpp"

namespace nts {

    TrueComp::TrueComp(const std::string &name)
    {
        _name = name;
    }

    void TrueComp::simulate(std::size_t tick)
    {
        _tick = tick;
    }

    Tristate TrueComp::compute(std::size_t pin)
    {
        if (pin != 1)
            throw NtsException("TrueComp: invalid pin " + std::to_string(pin));
        return Tristate::True;
    }

}
