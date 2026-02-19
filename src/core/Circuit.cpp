/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Circuit implementation
*/

#include "nts/Circuit.hpp"

#include <algorithm>
#include <iostream>

#include "nts/AComponent.hpp"
#include "nts/Errors.hpp"
#include "nts/IComponent.hpp"

namespace nts {

    void Circuit::addComponent(const std::string &name,
                               std::unique_ptr<IComponent> component)
    {
        if (!component) {
            throw ParseError("Cannot add null component '" + name + "'");
        }
        auto [it, inserted] = _components.emplace(name, std::move(component));
        if (!inserted) {
            throw ParseError("Duplicate component name: '" + name + "'");
        }
    }

    bool Circuit::hasComponent(const std::string &name) const noexcept
    {
        return _components.find(name) != _components.end();
    }

    IComponent &Circuit::getComponent(const std::string &name)
    {
        auto it = _components.find(name);
        if (it == _components.end()) {
            throw ParseError("Unknown component: '" + name + "'");
        }
        return *it->second;
    }

    const IComponent &Circuit::getComponent(const std::string &name) const
    {
        auto it = _components.find(name);
        if (it == _components.end()) {
            throw ParseError("Unknown component: '" + name + "'");
        }
        return *it->second;
    }

    const std::map<std::string, std::unique_ptr<IComponent>> &Circuit::components() const noexcept
    {
        return _components;
    }

    void Circuit::addInputName(const std::string &name)
    {
        _inputNames.push_back(name);
    }

    void Circuit::addOutputName(const std::string &name)
    {
        _outputNames.push_back(name);
    }

    void Circuit::addClockName(const std::string &name)
    {
        _clockNames.push_back(name);
    }

    void Circuit::simulate()
    {
        _tick++;
        for (auto &[name, comp] : _components) {
            comp->simulate(_tick);
        }
    }

    void Circuit::computeAllOutputs()
    {
        std::vector<std::string> sorted = _outputNames;
        std::sort(sorted.begin(), sorted.end());
        for (const auto &name : sorted) {
            auto it = _components.find(name);
            if (it != _components.end()) {
                it->second->compute(1);
            }
        }
    }

    void Circuit::display() const
    {
        std::vector<std::string> sortedInputs = _inputNames;
        std::sort(sortedInputs.begin(), sortedInputs.end());

        std::vector<std::string> sortedOutputs = _outputNames;
        std::sort(sortedOutputs.begin(), sortedOutputs.end());

        auto tristateToChar = [](Tristate t) -> char {
            if (t == True) return '1';
            if (t == False) return '0';
            return 'U';
        };

        std::cout << "tick: " << _tick << std::endl;

        std::cout << "input(s):" << std::endl;
        for (const auto &name : sortedInputs) {
            auto it = _components.find(name);
            if (it != _components.end()) {
                Tristate val = it->second->compute(1);
                std::cout << "  " << name << ": " << tristateToChar(val) << std::endl;
            }
        }

        std::cout << "output(s):" << std::endl;
        for (const auto &name : sortedOutputs) {
            auto it = _components.find(name);
            if (it != _components.end()) {
                Tristate val = it->second->compute(1);
                std::cout << "  " << name << ": " << tristateToChar(val) << std::endl;
            }
        }
    }

    void Circuit::setInputValue(const std::string &name, const std::string &value)
    {
        auto it = _components.find(name);
        if (it == _components.end()) {
            throw NtsException("Unknown input: '" + name + "'");
        }
        bool isInput = std::find(_inputNames.begin(), _inputNames.end(), name)
                       != _inputNames.end();
        bool isClock = std::find(_clockNames.begin(), _clockNames.end(), name)
                       != _clockNames.end();
        if (!isInput && !isClock) {
            throw NtsException("Component '" + name + "' is not an input or clock");
        }
        Tristate val = Undefined;
        if (value == "1")
            val = True;
        else if (value == "0")
            val = False;
        else if (value != "U")
            throw NtsException("Invalid value '" + value + "' (expected 0, 1 or U)");

        auto *acomp = dynamic_cast<AComponent *>(&(*it->second));
        if (acomp) {
            acomp->setPin(1, val);
        }
    }

    const std::vector<std::string> &Circuit::inputNames() const noexcept
    {
        return _inputNames;
    }

    const std::vector<std::string> &Circuit::outputNames() const noexcept
    {
        return _outputNames;
    }

    std::size_t Circuit::tick() const noexcept
    {
        return _tick;
    }

}
