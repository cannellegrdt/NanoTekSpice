/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** TuringMachine implementation
*/

#include "bonus/TuringMachine.hpp"
#include "nts/Errors.hpp"

#include <algorithm>
#include <cstdlib>

namespace nts::bonus {

TuringMachine::TuringMachine(const std::string &name,
                             const std::string &programFile,
                             const std::string &input)
    : _tape('_')
{
    _name         = name;
    _initialInput = input;
    _program      = TuringParser().parse(programFile);
    _tape         = TuringTape(_program.blank);

    doReset();
    updateOutputPins();
}

void TuringMachine::simulate(std::size_t tick)
{
    _tick = tick;

    Tristate rst = getLinkValue(2);
    if (rst == Tristate::True) {
        doReset();
        updateOutputPins();
        _prevClk = Tristate::Undefined;
        return;
    }

    Tristate clk = getLinkValue(1);

    if (!_halted && _prevClk != Tristate::True && clk == Tristate::True)
        step();

    _prevClk = clk;
    updateOutputPins();
}

Tristate TuringMachine::compute(std::size_t pin)
{
    if (pin == 1 || pin == 2)
        return getLinkValue(pin);

    if (pin == 3)  return _haltPin;
    if (pin == 4)  return _acceptPin;

    if (pin >= 5  && pin <= 12)  return _stateBits[pin - 5];
    if (pin >= 13 && pin <= 20)  return _symbolBits[pin - 13];

    if (pin == 21) return _headSign;
    if (pin >= 22 && pin <= 29)  return _headBits[pin - 22];

    throw nts::NtsException("TuringMachine: invalid pin " + std::to_string(pin));
}

void TuringMachine::doReset()
{
    _currentState = _program.initialState;
    _halted       = false;
    _accepted     = false;
    _tape.reset();
    if (!_initialInput.empty())
        _tape.loadInput(_initialInput);
    _stateBits.fill(Tristate::Undefined);
    _symbolBits.fill(Tristate::Undefined);
    _headBits.fill(Tristate::False);
    _haltPin   = Tristate::False;
    _acceptPin = Tristate::False;
    _headSign  = Tristate::False;
}

void TuringMachine::step()
{
    char symbol = _tape.read();
    auto key    = std::make_pair(_currentState, symbol);
    auto it     = _program.transitions.find(key);

    if (it == _program.transitions.end()) {
        _halted   = true;
        _accepted = false;
        return;
    }

    const Transition &t = it->second;
    _tape.write(t.writeSymbol);

    if (t.direction == 'L')
        _tape.moveLeft();
    else
        _tape.moveRight();

    _currentState = t.nextState;

    if (_program.acceptingStates.count(_currentState)) {
        _halted   = true;
        _accepted = true;
    } else if (_program.rejectingStates.count(_currentState)) {
        _halted   = true;
        _accepted = false;
    }
}

void TuringMachine::stepOnce()
{
    if (!_halted) {
        step();
        updateOutputPins();
    }
}

void TuringMachine::updateOutputPins()
{
    _haltPin   = _halted   ? Tristate::True : Tristate::False;
    _acceptPin = _accepted ? Tristate::True : Tristate::False;

    std::size_t idx = stateIndex(_currentState);
    _stateBits = toBits(static_cast<unsigned int>(idx));

    unsigned int sym = static_cast<unsigned char>(_tape.read());
    _symbolBits = toBits(sym);

    int pos = _tape.headPosition();
    _headSign = (pos < 0) ? Tristate::True : Tristate::False;
    _headBits = toBits(static_cast<unsigned int>(std::abs(pos)));
}

std::array<Tristate, 8> TuringMachine::toBits(unsigned int value)
{
    std::array<Tristate, 8> bits{};
    for (int i = 0; i < 8; ++i)
        bits[i] = ((value >> i) & 1u) ? Tristate::True : Tristate::False;
    return bits;
}

std::size_t TuringMachine::stateIndex(const std::string &state) const
{
    const auto &v = _program.states;
    auto it = std::find(v.begin(), v.end(), state);
    if (it == v.end())
        return 0;
    return static_cast<std::size_t>(it - v.begin());
}

} // namespace nts::bonus
