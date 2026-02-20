/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Stub factory implementation
*/

#include "nts/StubFactory.hpp"

#include <iostream>

#include "nts/AComponent.hpp"
#include "nts/Tristate.hpp"

namespace nts {

namespace {

class StubComponent : public AComponent {
public:
  void simulate(std::size_t) override {}
  Tristate compute(std::size_t) override { return Undefined; }
};

}

std::unique_ptr<IComponent>
StubFactory::createComponent(const std::string &type,
                             const std::string &name) const {
  std::cout << type << std::endl;
  auto component = std::make_unique<StubComponent>();
  component->setName(name);
  return component;
}

}
