/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Parser implementation
*/

#include "nts/Parser.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "nts/AComponent.hpp"
#include "nts/Circuit.hpp"
#include "nts/Errors.hpp"
#include "nts/Factory.hpp"
#include "nts/IComponent.hpp"

namespace {

    std::string ltrim(const std::string &s)
    {
        std::size_t i = 0;
        while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) {
            ++i;
        }
        return s.substr(i);
    }

    std::string rtrim(const std::string &s)
    {
        if (s.empty()) {
            return s;
        }
        std::size_t i = s.size();
        while (i > 0 && std::isspace(static_cast<unsigned char>(s[i - 1]))) {
            --i;
        }
        return s.substr(0, i);
    }

    std::string trim(const std::string &s)
    {
        return rtrim(ltrim(s));
    }

    std::string strip_comment(const std::string &line)
    {
        std::size_t pos = line.find('#');
        if (pos == std::string::npos) {
            return line;
        }
        return line.substr(0, pos);
    }

}

namespace nts {

    Parser::Parser(IComponentFactory &factory)
        : _factory(factory)
    {
    }

    Circuit Parser::parse(const std::string &filepath) const
    {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw ParseError("Cannot open file: '" + filepath + "'");
        }
        return parse(file);
    }

    Circuit Parser::parse(std::istream &input) const
    {
        Circuit circuit;
        bool inChipsets = false;
        bool inLinks = false;

        std::string rawLine;
        while (std::getline(input, rawLine)) {
            std::string line = trim(strip_comment(rawLine));
            if (line.empty()) {
                continue;
            }

            if (line == ".chipsets:") {
                if (inChipsets || inLinks) {
                    throw ParseError("Multiple or misplaced '.chipsets:' section");
                }
                inChipsets = true;
                continue;
            }
            if (line == ".links:") {
                if (!inChipsets || inLinks) {
                    throw ParseError("'.links:' section must appear after '.chipsets:'");
                }
                inLinks = true;
                continue;
            }

            if (!inChipsets && !inLinks) {
                throw ParseError("Content outside of any section: '" + line + "'");
            }

            if (inChipsets && !inLinks) {
                parseChipsetLine(line, circuit);
            } else if (inLinks) {
                parseLinkLine(line, circuit);
            }
        }

        if (circuit.components().empty()) {
            throw ParseError("No chipsets defined in circuit");
        }

        return circuit;
    }

    void Parser::parseChipsets(std::istream &input, Circuit &circuit) const
    {
        std::string rawLine;
        while (std::getline(input, rawLine)) {
            std::string line = trim(strip_comment(rawLine));
            if (line.empty()) {
                continue;
            }
            if (line == ".links:") {
                input.seekg(-(static_cast<long>(rawLine.size()) + 1), std::ios_base::cur);
                break;
            }
            parseChipsetLine(line, circuit);
        }
    }

    void Parser::parseLinks(std::istream &input, Circuit &circuit) const
    {
        std::string rawLine;
        while (std::getline(input, rawLine)) {
            std::string line = trim(strip_comment(rawLine));
            if (line.empty()) {
                continue;
            }
            parseLinkLine(line, circuit);
        }
    }

    void Parser::parseChipsetLine(const std::string &line, Circuit &circuit) const
    {
        std::istringstream iss(line);
        std::string type;
        std::string name;
        if (!(iss >> type >> name) || (iss >> std::ws, !iss.eof())) {
            throw ParseError("Invalid chipset line: '" + line + "'");
        }

        std::unique_ptr<IComponent> component = _factory.createComponent(type);

        if (auto *acomp = dynamic_cast<AComponent *>(component.get())) {
            acomp->setName(name);
        }

        circuit.addComponent(name, std::move(component));

        if (type == "input")
            circuit.addInputName(name);
        else if (type == "output")
            circuit.addOutputName(name);
        else if (type == "clock")
            circuit.addClockName(name);
    }

    void Parser::parseLinkLine(const std::string &line, Circuit &circuit) const
    {
        std::istringstream iss(line);
        std::string left;
        std::string right;
        if (!(iss >> left >> right) || (iss >> std::ws, !iss.eof())) {
            throw ParseError("Invalid link line: '" + line + "'");
        }

        auto parseEndpoint = [](const std::string &token) -> std::pair<std::string, std::size_t> {
            std::size_t colon = token.find(':');
            if (colon == std::string::npos || colon == 0 || colon + 1 >= token.size()) {
                throw ParseError("Invalid link endpoint: '" + token + "'");
            }
            std::string name = token.substr(0, colon);
            std::string pinStr = token.substr(colon + 1);
            std::size_t pin = 0;
            try {
                pin = static_cast<std::size_t>(std::stoul(pinStr));
            } catch (const std::exception &) {
                throw ParseError("Invalid pin number: '" + pinStr + "'");
            }
            if (pin == 0) {
                throw ParseError("Pin numbers must be >= 1");
            }
            return {name, pin};
        };

        auto [leftName, leftPin] = parseEndpoint(left);
        auto [rightName, rightPin] = parseEndpoint(right);

        IComponent &leftComp = circuit.getComponent(leftName);
        IComponent &rightComp = circuit.getComponent(rightName);

        leftComp.setLink(leftPin, rightComp, rightPin);
    }

}
