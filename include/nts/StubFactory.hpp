/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Stub factory
*/

#ifndef NTS_STUBFACTORY_HPP_
#define NTS_STUBFACTORY_HPP_

#include "nts/Factory.hpp"

namespace nts {


    class StubFactory : public IComponentFactory {
    public:
        std::unique_ptr<IComponent> createComponent(
            const std::string &type) const override;
    };

}

#endif /* !NTS_STUBFACTORY_HPP_ */
