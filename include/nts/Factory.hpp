/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Factory interfaces
*/

#ifndef NTS_FACTORY_HPP_
#define NTS_FACTORY_HPP_

#include <memory>
#include <string>

namespace nts {

    class IComponent;


    class IComponentFactory {
    public:
        virtual ~IComponentFactory() = default;

        virtual std::unique_ptr<IComponent> createComponent(
            const std::string &type) const = 0;
    };

}

#endif /* !NTS_FACTORY_HPP_ */
