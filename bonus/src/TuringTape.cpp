/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** TuringTape implementation
*/

#include "bonus/TuringTape.hpp"

namespace nts::bonus {

TuringTape::TuringTape(char blank)
    : _head(0), _blank(blank)
{}

char TuringTape::read() const
{
    auto it = _tape.find(_head);
    if (it == _tape.end())
        return _blank;
    return it->second;
}

void TuringTape::write(char symbol)
{
    if (symbol == _blank)
        _tape.erase(_head);
    else
        _tape[_head] = symbol;
}

void TuringTape::moveLeft()
{
    --_head;
}

void TuringTape::moveRight()
{
    ++_head;
}

int TuringTape::headPosition() const
{
    return _head;
}

void TuringTape::reset()
{
    _tape.clear();
    _head = 0;
}

void TuringTape::loadInput(const std::string &input)
{
    reset();
    for (int i = 0; i < static_cast<int>(input.size()); ++i)
        if (input[i] != _blank)
            _tape[i] = input[i];
}

void TuringTape::dump(std::ostream &os) const
{
    if (_tape.empty()) {
        os << "[empty tape, head at " << _head << "]\n";
        return;
    }
    int lo = _tape.begin()->first;
    int hi = _tape.rbegin()->first;
    lo = std::min(lo, _head);
    hi = std::max(hi, _head);

    for (int i = lo; i <= hi; ++i) {
        auto it = _tape.find(i);
        char c = (it == _tape.end()) ? _blank : it->second;
        if (i == _head)
            os << '[' << c << ']';
        else
            os << ' ' << c << ' ';
    }
    os << '\n';
}

} // namespace nts::bonus
