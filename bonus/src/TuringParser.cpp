/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** TuringParser implementation
*/

#include "bonus/TuringParser.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace nts::bonus {

static std::string trim(const std::string &s)
{
    std::size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return {};
    std::size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

static std::vector<std::string> split(const std::string &s)
{
    std::vector<std::string> tokens;
    std::istringstream       ss(s);
    std::string              tok;
    while (ss >> tok)
        tokens.push_back(tok);
    return tokens;
}

TuringProgram TuringParser::parse(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("TuringParser: cannot open file: " + filepath);

    TuringProgram prog;
    Section       section = Section::None;
    std::string   line;

    while (std::getline(file, line)) {
        auto hash = line.find('#');
        if (hash != std::string::npos)
            line = line.substr(0, hash);
        line = trim(line);
        if (line.empty())
            continue;
        parseLine(line, prog, section);
    }

    if (prog.initialState.empty())
        throw std::runtime_error("TuringParser: missing 'initial:' directive");

    return prog;
}

void TuringParser::parseLine(const std::string &line,
                             TuringProgram     &prog,
                             Section           &section)
{
    if (line == "transitions:") {
        section = Section::Transitions;
        return;
    }

    auto colon = line.find(':');
    if (section != Section::Transitions && colon != std::string::npos) {
        std::string key   = trim(line.substr(0, colon));
        std::string value = trim(line.substr(colon + 1));
        parseHeader(key, value, prog);
        return;
    }

    if (section == Section::Transitions)
        parseTransition(line, prog);
}

void TuringParser::parseHeader(const std::string &key,
                               const std::string &value,
                               TuringProgram     &prog)
{
    auto tokens = split(value);

    if (key == "states") {
        prog.states = tokens;
    } else if (key == "alphabet") {
        // informational only — we accept any char seen in transitions
    } else if (key == "blank") {
        if (tokens.size() != 1 || tokens[0].size() != 1)
            throw std::runtime_error("TuringParser: 'blank' must be a single character");
        prog.blank = tokens[0][0];
    } else if (key == "initial") {
        if (tokens.size() != 1)
            throw std::runtime_error("TuringParser: 'initial' must name exactly one state");
        prog.initialState = tokens[0];
    } else if (key == "accepting") {
        prog.acceptingStates.insert(tokens.begin(), tokens.end());
    } else if (key == "rejecting") {
        prog.rejectingStates.insert(tokens.begin(), tokens.end());
    }
}

void TuringParser::parseTransition(const std::string &line,
                                   TuringProgram     &prog)
{
    auto tokens = split(line);
    if (tokens.size() != 5)
        throw std::runtime_error(
            "TuringParser: transition must have 5 fields: "
            "state read next_state write direction — got: " + line);

    if (tokens[1].size() != 1)
        throw std::runtime_error(
            "TuringParser: read symbol must be a single char: " + tokens[1]);
    if (tokens[3].size() != 1)
        throw std::runtime_error(
            "TuringParser: write symbol must be a single char: " + tokens[3]);
    if (tokens[4] != "L" && tokens[4] != "R")
        throw std::runtime_error(
            "TuringParser: direction must be 'L' or 'R', got: " + tokens[4]);

    Transition t;
    t.currentState = tokens[0];
    t.readSymbol   = tokens[1][0];
    t.nextState    = tokens[2];
    t.writeSymbol  = tokens[3][0];
    t.direction    = tokens[4][0];

    auto key = std::make_pair(t.currentState, t.readSymbol);
    if (prog.transitions.count(key))
        throw std::runtime_error(
            "TuringParser: duplicate transition for state=" +
            t.currentState + " symbol=" + t.readSymbol);

    prog.transitions[key] = t;
}

} // namespace nts::bonus
