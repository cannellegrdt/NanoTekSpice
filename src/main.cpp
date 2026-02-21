/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** main.cpp
*/

#include <iostream>

#include "nts/Circuit.hpp"
#include "nts/Errors.hpp"
#include "nts/Parser.hpp"
#include "nts/Shell.hpp"
#include "nts/ComponentFactory.hpp"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << (argv[0] ? argv[0] : "nanotekspice")
                  << " <file.nts>" << std::endl;
        return 84;
    }
    try {
        nts::ComponentFactory factory;
        nts::Parser parser(factory);
        nts::Circuit circuit = parser.parse(argv[1]);

        nts::Shell shell(circuit);
        shell.run();
        return 0;
    } catch (const nts::NtsException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
}
