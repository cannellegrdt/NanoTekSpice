/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Concrete factory implementation
*/

#include "nts/ComponentFactory.hpp"

#include <functional>
#include <unordered_map>

#include "nts/Errors.hpp"
#include "nts/components/Input.hpp"
#include "nts/components/Output.hpp"
#include "nts/components/True.hpp"
#include "nts/components/False.hpp"
#include "nts/components/Clock.hpp"
#include "nts/components/AndGate.hpp"
#include "nts/components/OrGate.hpp"
#include "nts/components/XorGate.hpp"
#include "nts/components/NotGate.hpp"
#include "nts/components/NorGate.hpp"
#include "nts/components/NandGate.hpp"
#include "nts/components/C4001.hpp"
#include "nts/components/C4011.hpp"
#include "nts/components/C4030.hpp"
#include "nts/components/C4069.hpp"
#include "nts/components/C4071.hpp"
#include "nts/components/C4081.hpp"
#include "nts/components/C4008.hpp"
#include "nts/components/C4013.hpp"
#include "nts/components/C4017.hpp"
#include "nts/components/C4040.hpp"
#include "nts/components/C4094.hpp"
#include "nts/components/C4512.hpp"
#include "nts/components/C4514.hpp"
#include "nts/components/C4801.hpp"
#include "nts/components/C2716.hpp"
#include "nts/components/Logger.hpp"

namespace nts {

std::unique_ptr<IComponent>
ComponentFactory::createComponent(const std::string &type,
                                  const std::string &name) const
{
    using Creator = std::function<std::unique_ptr<IComponent>(const std::string &)>;

    static const std::unordered_map<std::string, Creator> creators = {
        {"input",  [](const std::string &n) { return std::make_unique<Input>(n); }},
        {"output", [](const std::string &n) { return std::make_unique<Output>(n); }},
        {"true",   [](const std::string &n) { return std::make_unique<TrueComp>(n); }},
        {"false",  [](const std::string &n) { return std::make_unique<FalseComp>(n); }},
        {"clock",  [](const std::string &n) { return std::make_unique<Clock>(n); }},
        {"and",    [](const std::string &n) { return std::make_unique<AndGate>(n); }},
        {"or",     [](const std::string &n) { return std::make_unique<OrGate>(n); }},
        {"xor",    [](const std::string &n) { return std::make_unique<XorGate>(n); }},
        {"not",    [](const std::string &n) { return std::make_unique<NotGate>(n); }},
        {"nor",    [](const std::string &n) { return std::make_unique<NorGate>(n); }},
        {"nand",   [](const std::string &n) { return std::make_unique<NandGate>(n); }},
        {"4001",   [](const std::string &n) { return std::make_unique<C4001>(n); }},
        {"4011",   [](const std::string &n) { return std::make_unique<C4011>(n); }},
        {"4030",   [](const std::string &n) { return std::make_unique<C4030>(n); }},
        {"4069",   [](const std::string &n) { return std::make_unique<C4069>(n); }},
        {"4071",   [](const std::string &n) { return std::make_unique<C4071>(n); }},
        {"4081",   [](const std::string &n) { return std::make_unique<C4081>(n); }},
        {"4008",   [](const std::string &n) { return std::make_unique<C4008>(n); }},
        {"4013",   [](const std::string &n) { return std::make_unique<C4013>(n); }},
        {"4017",   [](const std::string &n) { return std::make_unique<C4017>(n); }},
        {"4040",   [](const std::string &n) { return std::make_unique<C4040>(n); }},
        {"4094",   [](const std::string &n) { return std::make_unique<C4094>(n); }},
        {"4512",   [](const std::string &n) { return std::make_unique<C4512>(n); }},
        {"4514",   [](const std::string &n) { return std::make_unique<C4514>(n); }},
        {"4801",   [](const std::string &n) { return std::make_unique<C4801>(n); }},
        {"2716",   [](const std::string &n) { return std::make_unique<C2716>(n); }},
        {"logger", [](const std::string &n) { return std::make_unique<Logger>(n); }},
    };

    auto it = creators.find(type);
    if (it == creators.end())
        throw NtsException("Unknown component type: " + type);

    return it->second(name);
}

} // namespace nts
