/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** AGateComponent abstract base class implementation
*/

#include "nts/components/AGateComponent.hpp"
#include "nts/Errors.hpp"

namespace nts {

    AGateComponent::AGateComponent(const std::string &name)
    {
        _name = name;
    }

    void AGateComponent::simulate(std::size_t tick)
    {
        _tick = tick;
        for (auto &gate : _gates)
            gate->simulate(tick);
    }

    Tristate AGateComponent::compute(std::size_t pin)
    {
        auto [gate, gatePin] = mapPinToGate(pin);
        return gate->compute(gatePin);
    }

    void AGateComponent::setLink(
        std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        auto [gate, gatePin] = mapPinToGate(pin);
        gate->setLink(gatePin, other, otherPin);
    }

}
