/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Shell interface / class declaration
*/

#ifndef NTS_SHELL_HPP_
#define NTS_SHELL_HPP_

#include <string>

namespace nts {

class Circuit;

/**
 * @brief Interactive shell for controlling the NanoTekSpice simulation
 */
class Shell {
public:
  /**
   * @brief Construct a new Shell object
   *
   * @param circuit The circuit to control
   */
  explicit Shell(Circuit &circuit);

  /**
   * @brief Destroy the Shell object
   */
  ~Shell() = default;

  Shell(const Shell &) = delete;
  Shell &operator=(const Shell &) = delete;

  /**
   * @brief Start the interactive shell loop
   */
  void run();

private:
  Circuit &_circuit;
  bool _running = true;

  void handleCommand(const std::string &line);
  void cmdDisplay();
  void cmdSimulate();
  void cmdLoop();
  void cmdSetInput(const std::string &line);

  static volatile bool _loopInterrupted;
  static void signalHandler(int signum);
};

} // namespace nts

#endif /* !NTS_SHELL_HPP_ */
