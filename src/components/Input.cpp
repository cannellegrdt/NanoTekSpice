/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Input component implementation
*/

#include "nts/components/Input.hpp"
#include "nts/Errors.hpp"

namespace nts {

    Input::Input(const std::string &name)
    {
        _name = name;
        _nextValue = Tristate::Undefined;
        setPin(1, Tristate::Undefined);
    }

    void Input::simulate(std::size_t tick)
    {
        _tick = tick;
        setPin(1, _nextValue);
    }

    Tristate Input::compute(std::size_t pin)
    {
        if (pin != 1)
            throw NtsException("Input: invalid pin " + std::to_string(pin));
        return getPin(1);
    }

    void Input::setValue(Tristate val)
    {
        _nextValue = val;
    }

}
