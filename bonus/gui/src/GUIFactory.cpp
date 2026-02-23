/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** GUIFactory implementation
*/

#include "gui/GUIFactory.hpp"
#include "gui/components/SevenSeg.hpp"
#include "gui/components/Matrix.hpp"
#include "nts/ComponentFactory.hpp"

namespace gui {

std::unique_ptr<nts::IComponent>
GUIFactory::createComponent(const std::string &type,
                             const std::string &name) const
{
    if (type == "7seg")
        return std::make_unique<SevenSeg>(name);
    if (type == "matrix")
        return std::make_unique<Matrix>(name);

    nts::ComponentFactory base;
    return base.createComponent(type, name);
}

}
