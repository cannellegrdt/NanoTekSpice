/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** GUIFactory — factory extended with 7seg and matrix graphic components
*/

#pragma once

#include "nts/Factory.hpp"

namespace gui {

class GUIFactory : public nts::IComponentFactory {
public:
    GUIFactory() = default;
    ~GUIFactory() override = default;

    std::unique_ptr<nts::IComponent>
    createComponent(const std::string &type,
                    const std::string &name) const override;
};

}
