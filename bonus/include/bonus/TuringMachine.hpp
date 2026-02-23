/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** TuringMachine
*/

#ifndef BONUS_TURINGMACHINE_HPP_
#define BONUS_TURINGMACHINE_HPP_

#include <array>
#include <string>

#include "nts/AComponent.hpp"
#include "bonus/TuringParser.hpp"
#include "bonus/TuringTape.hpp"

namespace nts::bonus {

/*
** Pin map:
**  1  IN   CLK    — rising edge triggers one step
**  2  IN   RST    — high level resets the machine
**  3  OUT  HALT   — True when machine has stopped
**  4  OUT  ACCEPT — True when halted in an accepting state
**  5–12  OUT  STATE[0..7]   — current state index (binary, LSB=5)
**  13–20 OUT  SYMBOL[0..7]  — ASCII value of current tape symbol (LSB=13)
**  21    OUT  HEAD_SIGN     — 0 if head >= 0, 1 if head < 0
**  22–29 OUT  HEAD_POS[0..7]— absolute head position (LSB=22)
*/
class TuringMachine : public AComponent {
public:
    TuringMachine(const std::string &name,
                  const std::string &programFile,
                  const std::string &input = "");

    void     simulate(std::size_t tick) override;
    Tristate compute(std::size_t pin)   override;

    void     stepOnce();
    bool     isHalted()   const { return _halted; }
    bool     isAccepted() const { return _accepted; }
    void     dumpTape(std::ostream &os) const { _tape.dump(os); }

private:
    TuringProgram _program;
    TuringTape    _tape;
    std::string   _initialInput;

    std::string   _currentState;
    bool          _halted   = false;
    bool          _accepted = false;

    Tristate      _prevClk = Tristate::Undefined;

    Tristate                _haltPin   = Tristate::False;
    Tristate                _acceptPin = Tristate::False;
    std::array<Tristate, 8> _stateBits{};
    std::array<Tristate, 8> _symbolBits{};
    Tristate                _headSign  = Tristate::False;
    std::array<Tristate, 8> _headBits{};

    void doReset();
    void step();
    void updateOutputPins();

    static std::array<Tristate, 8> toBits(unsigned int value);
    std::size_t stateIndex(const std::string &state) const;
};

} // namespace nts::bonus

#endif /* !BONUS_TURINGMACHINE_HPP_ */
