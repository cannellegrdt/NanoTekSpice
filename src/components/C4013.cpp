/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4013 chipset implementation
*/

#include "nts/components/C4013.hpp"
#include "nts/Errors.hpp"
#include "nts/TristateLogic.hpp"

namespace nts {

C4013::C4013(const std::string &name)
    : _q1(Tristate::False), _q1_next(Tristate::False), _q2(Tristate::False),
      _q2_next(Tristate::False), _lastClock1(Tristate::True),
      _lastClock2(Tristate::True) {
  _name = name;
}

void C4013::simulate(std::size_t tick) {
  _tick = tick;

  Tristate reset1 = getLinkValue(4);
  Tristate set1 = getLinkValue(6);
  Tristate clock1 = getLinkValue(3);
  Tristate reset2 = getLinkValue(10);
  Tristate set2 = getLinkValue(8);
  Tristate clock2 = getLinkValue(11);

  if (set1 == True)
    _q1_next = True;
  else if (reset1 == True)
    _q1_next = False;
  else if (_lastClock1 == False && clock1 == True)
    _q1_next = getLinkValue(5);

  if (set2 == True)
    _q2_next = True;
  else if (reset2 == True)
    _q2_next = False;
  else if (_lastClock2 == False && clock2 == True)
    _q2_next = getLinkValue(9);

  _q1 = _q1_next;
  _q2 = _q2_next;
  _lastClock1 = clock1;
  _lastClock2 = clock2;

  _pins[1] = _q1;
  _pins[2] = TristateLogic::notGate(_q1);
  _pins[13] = _q2;
  _pins[12] = TristateLogic::notGate(_q2);
}

Tristate C4013::compute(std::size_t pin) {
  if (pin == 7 || pin == 14)
    throw NtsException("C4013: pin " + std::to_string(pin) + " is a power pin");

  switch (pin) {
  case 1:
    return _q1;
  case 2:
    return TristateLogic::notGate(_q1);
  case 13:
    return _q2;
  case 12:
    return TristateLogic::notGate(_q2);
  case 3:
  case 4:
  case 5:
  case 6:
  case 8:
  case 9:
  case 10:
  case 11:
    return getLinkValue(pin);
  default:
    throw NtsException("C4013: invalid pin " + std::to_string(pin));
  }
}

} // namespace nts
