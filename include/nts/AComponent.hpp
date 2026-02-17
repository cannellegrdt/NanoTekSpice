/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** AComponent abstract base class declaration
*/

#ifndef NTS_ACOMPONENT_HPP_
#define NTS_ACOMPONENT_HPP_

#include <map>
#include <string>

#include "nts/IComponent.hpp"

namespace nts {

    class AComponent : public IComponent {
    protected:
        std::string _name;
        std::map<std::size_t, std::pair<IComponent *, std::size_t>> _links;
        bool _computing = false;

    public:
        ~AComponent() override = default;

        std::string getName() const;
        void setName(const std::string &name);

        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) override;

    protected:
        Tristate getLinkValue(std::size_t pin);
    };

}

#endif /* !NTS_ACOMPONENT_HPP_ */

