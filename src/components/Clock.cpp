/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Clock component implementation
*/

#include "nts/components/Clock.hpp"

namespace nts {

Clock::Clock(const std::string &name) : Input(name) {
  _nextValue = Tristate::Undefined;
}

void Clock::simulate(std::size_t tick) {
  Input::simulate(tick);

  if (_nextValue == Tristate::True)
    _nextValue = Tristate::False;
  else if (_nextValue == Tristate::False)
    _nextValue = Tristate::True;
}

} // namespace nts
