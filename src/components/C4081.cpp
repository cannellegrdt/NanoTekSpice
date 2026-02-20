/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4081 chipset implementation
*/

#include "nts/components/C4081.hpp"
#include "nts/components/AndGate.hpp"
#include "nts/Errors.hpp"

namespace nts {

    C4081::C4081(const std::string &name) : AGateComponent(name)
    {
        _gates.push_back(std::make_unique<AndGate>(name + "_gate0"));
        _gates.push_back(std::make_unique<AndGate>(name + "_gate1"));
        _gates.push_back(std::make_unique<AndGate>(name + "_gate2"));
        _gates.push_back(std::make_unique<AndGate>(name + "_gate3"));
    }

    std::pair<IComponent *, std::size_t> C4081::mapPinToGate(
        std::size_t pin) const
    {
        if (pin == 7 || pin == 14)
            throw NtsException("C4081: pin " + std::to_string(pin) + " is a power pin");
        switch (pin) {
            case 1: return { _gates[0].get(), 1 };
            case 2: return { _gates[0].get(), 2 };
            case 3: return { _gates[0].get(), 3 };
            case 5: return { _gates[1].get(), 1 };
            case 6: return { _gates[1].get(), 2 };
            case 4: return { _gates[1].get(), 3 };
            case 8: return { _gates[2].get(), 1 };
            case 9: return { _gates[2].get(), 2 };
            case 10: return { _gates[2].get(), 3 };
            case 12: return { _gates[3].get(), 1 };
            case 13: return { _gates[3].get(), 2 };
            case 11: return { _gates[3].get(), 3 };
            default:
                throw NtsException("C4081: invalid pin " + std::to_string(pin));
        }
    }

}
