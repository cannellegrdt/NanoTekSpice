/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Output component implementation
*/

#include "nts/components/Output.hpp"
#include "nts/Errors.hpp"

namespace nts {

    Output::Output(const std::string &name)
    {
        _name = name;
    }

    void Output::simulate(std::size_t tick)
    {
        _tick = tick;
    }

    Tristate Output::compute(std::size_t pin)
    {
        if (pin != 1)
            throw NtsException("Output: invalid pin " + std::to_string(pin));
        return getLinkValue(1);
    }

}
