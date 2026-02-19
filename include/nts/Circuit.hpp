/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Circuit class declaration
*/

#ifndef NTS_CIRCUIT_HPP_
#define NTS_CIRCUIT_HPP_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "nts/IComponent.hpp"

namespace nts {

    class Circuit {
    public:
        Circuit() = default;
        ~Circuit() = default;

        Circuit(const Circuit &) = delete;
        Circuit &operator=(const Circuit &) = delete;

        Circuit(Circuit &&) noexcept = default;
        Circuit &operator=(Circuit &&) noexcept = default;

        void addComponent(const std::string &name,
                          std::unique_ptr<IComponent> component);

        [[nodiscard]] bool hasComponent(const std::string &name) const noexcept;

        IComponent &getComponent(const std::string &name);
        const IComponent &getComponent(const std::string &name) const;

        [[nodiscard]] const std::map<std::string,
                                     std::unique_ptr<IComponent>> &components() const noexcept;

        void addInputName(const std::string &name);
        void addOutputName(const std::string &name);
        void addClockName(const std::string &name);

        void simulate();
        void computeAllOutputs();
        void display() const;
        void setInputValue(const std::string &name, const std::string &value);

        [[nodiscard]] const std::vector<std::string> &inputNames() const noexcept;
        [[nodiscard]] const std::vector<std::string> &outputNames() const noexcept;

        [[nodiscard]] std::size_t tick() const noexcept;

    private:
        std::map<std::string, std::unique_ptr<IComponent>> _components;
        std::vector<std::string> _inputNames;
        std::vector<std::string> _outputNames;
        std::vector<std::string> _clockNames;
        std::size_t _tick = 0;
    };

}

#endif /* !NTS_CIRCUIT_HPP_ */
