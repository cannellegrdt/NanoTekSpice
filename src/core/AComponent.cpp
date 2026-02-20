/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** AComponent abstract base class implementation
*/

#include "nts/AComponent.hpp"
#include "nts/Tristate.hpp"

namespace nts {

const std::string &AComponent::getName() const {
    return _name;
}

void AComponent::setName(const std::string &name) {
    _name = name;
}

void AComponent::setLink(std::size_t pin, IComponent &other, std::size_t otherPin) {
  _links[pin] = {&other, otherPin};

  if (AComponent *abstractOther = dynamic_cast<AComponent *>(&other)) {
    std::map<std::size_t, std::pair<IComponent *, std::size_t>>::iterator it =
        abstractOther->_links.find(otherPin);
    if (it == abstractOther->_links.end() || it->second.first != this ||
        it->second.second != pin) {
      abstractOther->_links[otherPin] = {this, pin};
    }
  }
}

Tristate AComponent::getLinkValue(std::size_t pin) {
  std::map<std::size_t, std::pair<IComponent *, std::size_t>>::iterator it = _links.find(pin);
  if (it == _links.end() || it->second.first == nullptr) {
    return Undefined;
  }
  if (_computing) {
    return Undefined;
  }
  _computing = true;
  IComponent *target = it->second.first;
  std::size_t targetPin = it->second.second;
  Tristate result = target->compute(targetPin);
  _computing = false;
  return result;
}

void AComponent::setPin(std::size_t pin, Tristate val) {
    _pins[pin] = val;
}

Tristate AComponent::getPin(std::size_t pin) const {
  std::map<std::size_t, Tristate>::const_iterator it = _pins.find(pin);
  if (it == _pins.end()) {
    return Undefined;
  }
  return it->second;
}

}
