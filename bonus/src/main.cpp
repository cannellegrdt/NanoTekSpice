/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Turing machine simulator — standalone entry point
**
** Usage: ./turing_simulator <program.tm> [tape_input] [--verbose]
*/

#include <iostream>
#include <string>

#include "bonus/TuringMachine.hpp"

static void printHelp(const char *prog)
{
    std::cerr << "Usage: " << prog
              << " <program.tm> [tape_input] [--verbose]\n"
              << "  program.tm   path to the .tm program file\n"
              << "  tape_input   initial content of the tape (default: empty)\n"
              << "  --verbose    print tape after every step\n";
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printHelp(argv[0]);
        return 84;
    }

    std::string programFile = argv[1];
    std::string tapeInput;
    bool        verbose = false;

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--verbose")
            verbose = true;
        else
            tapeInput = arg;
    }

    try {
        nts::bonus::TuringMachine tm("machine", programFile, tapeInput);

        std::size_t step = 0;
        const std::size_t limit = 1'000'000;

        while (!tm.isHalted() && step < limit) {
            tm.stepOnce();
            ++step;

            if (verbose) {
                std::cout << "Step " << step << ": ";
                tm.dumpTape(std::cout);
            }
        }

        if (!tm.isHalted()) {
            std::cerr << "Limit of " << limit
                      << " steps reached — machine may not halt.\n";
            return 84;
        }

        std::cout << "Halted after " << step << " step(s).\n";
        std::cout << "Result: " << (tm.isAccepted() ? "ACCEPT" : "REJECT") << "\n";

        if (verbose) {
            std::cout << "Final tape: ";
            tm.dumpTape(std::cout);
        }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 84;
    }

    return 0;
}
