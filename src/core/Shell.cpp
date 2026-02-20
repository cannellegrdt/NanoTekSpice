/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Shell implementation
*/

#include "nts/Shell.hpp"

#include <csignal>
#include <iostream>
#include <string>

#include "nts/Circuit.hpp"
#include "nts/Errors.hpp"

namespace nts {

volatile bool Shell::_loopInterrupted = false;

Shell::Shell(Circuit &circuit) : _circuit(circuit) {}

void Shell::signalHandler(int) { _loopInterrupted = true; }

void Shell::run() {
  _running = true;
  std::string line;

  while (_running) {
    std::cout << "> " << std::flush;
    if (!std::getline(std::cin, line)) {
      break;
    }
    if (line.empty()) {
      continue;
    }
    try {
      handleCommand(line);
    } catch (const NtsException &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
}

void Shell::handleCommand(const std::string &line) {
  if (line == "exit") {
    _running = false;
  } else if (line == "display") {
    cmdDisplay();
  } else if (line == "simulate") {
    cmdSimulate();
  } else if (line == "loop") {
    cmdLoop();
  } else if (line.find('=') != std::string::npos) {
    cmdSetInput(line);
  } else {
    throw NtsException("Unknown command: '" + line + "'");
  }
}

void Shell::cmdDisplay() { _circuit.display(); }

void Shell::cmdSimulate() {
  _circuit.simulate();
  _circuit.computeAllOutputs();
}

void Shell::cmdLoop() {
  _loopInterrupted = false;

  struct sigaction sa{};
  sa.sa_handler = signalHandler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, nullptr);

  while (!_loopInterrupted) {
    _circuit.simulate();
    _circuit.computeAllOutputs();
    _circuit.display();
  }

  sa.sa_handler = SIG_DFL;
  sigaction(SIGINT, &sa, nullptr);
}

void Shell::cmdSetInput(const std::string &line) {
  std::size_t eqPos = line.find('=');
  if (eqPos == std::string::npos || eqPos == 0 || eqPos + 1 >= line.size()) {
    throw NtsException("Invalid input assignment: '" + line + "'");
  }
  std::string name = line.substr(0, eqPos);
  std::string value = line.substr(eqPos + 1);
  _circuit.setInputValue(name, value);
}

} // namespace nts
