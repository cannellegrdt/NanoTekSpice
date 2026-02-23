/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** nanotekspice-gui entry point
*/

#include <iostream>
#include <sstream>

#include "nts/Parser.hpp"
#include "gui/GUIFactory.hpp"
#include "gui/GraphtcParser.hpp"
#include "gui/GUIShell.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <circuit.nts>" << std::endl;
        return 84;
    }

    try {
        const std::string filepath = argv[1];

        auto positions = gui::GraphtcParser::parsePositions(filepath);
        auto links = gui::GraphtcParser::parseLinks(filepath);

        std::string cleanContent = gui::GraphtcParser::stripGraphtc(filepath);
        std::istringstream stream(cleanContent);

        gui::GUIFactory factory;
        nts::Parser parser(factory);
        nts::Circuit circuit = parser.parse(stream);

        gui::GUIShell shell(circuit, positions, links);
        shell.run();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}
