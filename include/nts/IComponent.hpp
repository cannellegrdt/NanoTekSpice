/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** IComponent interface declaration
*/

#ifndef NTS_ICOMPONENT_HPP_
#define NTS_ICOMPONENT_HPP_

#include <cstddef>

namespace nts {

    enum Tristate;

    class IComponent {
    public:
        virtual ~IComponent() = default;
        virtual void simulate(std::size_t tick) = 0;
        virtual Tristate compute(std::size_t pin) = 0;
        virtual void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) = 0;
    };

}

#endif /* !NTS_ICOMPONENT_HPP_ */

