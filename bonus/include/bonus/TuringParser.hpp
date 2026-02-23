/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** TuringParser
*/

#ifndef BONUS_TURINGPARSER_HPP_
#define BONUS_TURINGPARSER_HPP_

#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace nts::bonus {

struct Transition {
    std::string currentState;
    char        readSymbol;
    std::string nextState;
    char        writeSymbol;
    char        direction;
};

struct TuringProgram {
    std::vector<std::string>                           states;
    std::string                                        initialState;
    std::set<std::string>                              acceptingStates;
    std::set<std::string>                              rejectingStates;
    char                                               blank = '_';
    std::map<std::pair<std::string, char>, Transition> transitions;
};

class TuringParser {
public:
    TuringProgram parse(const std::string &filepath);

private:
    enum class Section { None, Transitions };

    void parseLine(const std::string &raw, TuringProgram &prog, Section &section);
    void parseHeader(const std::string &key, const std::string &value, TuringProgram &prog);
    void parseTransition(const std::string &line, TuringProgram &prog);
};

} // namespace nts::bonus

#endif /* !BONUS_TURINGPARSER_HPP_ */
