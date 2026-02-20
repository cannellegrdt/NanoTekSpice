/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4069 chipset implementation
*/

#include "nts/components/C4069.hpp"
#include "nts/components/NotGate.hpp"
#include "nts/Errors.hpp"

namespace nts {

    C4069::C4069(const std::string &name) : AGateComponent(name)
    {
        _gates.push_back(std::make_unique<NotGate>(name + "_gate0"));
        _gates.push_back(std::make_unique<NotGate>(name + "_gate1"));
        _gates.push_back(std::make_unique<NotGate>(name + "_gate2"));
        _gates.push_back(std::make_unique<NotGate>(name + "_gate3"));
        _gates.push_back(std::make_unique<NotGate>(name + "_gate4"));
        _gates.push_back(std::make_unique<NotGate>(name + "_gate5"));
    }

    std::pair<IComponent *, std::size_t> C4069::mapPinToGate(
        std::size_t pin) const
    {
        if (pin == 7 || pin == 14)
            throw NtsException("C4069: pin " + std::to_string(pin) + " is a power pin");
        switch (pin) {
            case 1: return { _gates[0].get(), 1 };
            case 2: return { _gates[0].get(), 2 };
            case 3: return { _gates[1].get(), 1 };
            case 4: return { _gates[1].get(), 2 };
            case 5: return { _gates[2].get(), 1 };
            case 6: return { _gates[2].get(), 2 };
            case 9: return { _gates[3].get(), 1 };
            case 8: return { _gates[3].get(), 2 };
            case 11: return { _gates[4].get(), 1 };
            case 10: return { _gates[4].get(), 2 };
            case 13: return { _gates[5].get(), 1 };
            case 12: return { _gates[5].get(), 2 };
            default:
                throw NtsException("C4069: invalid pin " + std::to_string(pin));
        }
    }

}
