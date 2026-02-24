/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Circuit class declaration
*/

#ifndef NTS_CIRCUIT_HPP_
#define NTS_CIRCUIT_HPP_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "nts/IComponent.hpp"

namespace nts {

/**
 * @brief Represents a logical circuit containing components and their
 * connections
 */
class Circuit {
public:
  /**
   * @brief Construct a new Circuit object
   */
  Circuit() = default;

  /**
   * @brief Destroy the Circuit object
   */
  ~Circuit() = default;

  Circuit(const Circuit &) = delete;
  Circuit &operator=(const Circuit &) = delete;

  Circuit(Circuit &&) noexcept = default;
  Circuit &operator=(Circuit &&) noexcept = default;

  /**
   * @brief Add a component to the circuit
   *
   * @param name The name of the component
   * @param component Unique pointer to the component
   */
  void addComponent(const std::string &name,
                    std::unique_ptr<IComponent> component);

  /**
   * @brief Check if a component exists in the circuit
   *
   * @param name The name of the component
   * @return true If the component exists
   * @return false Otherwise
   */
  [[nodiscard]] bool hasComponent(const std::string &name) const noexcept;

  /**
   * @brief Get a reference to a component
   *
   * @param name The name of the component
   * @return IComponent& Reference to the component
   */
  IComponent &getComponent(const std::string &name);

  /**
   * @brief Get a const reference to a component
   *
   * @param name The name of the component
   * @return const IComponent& Const reference to the component
   */
  const IComponent &getComponent(const std::string &name) const;

  /**
   * @brief Get all components in the circuit
   *
   * @return const std::map<std::string, std::unique_ptr<IComponent>>& Map of
   * components
   */
  [[nodiscard]] const std::map<std::string, std::unique_ptr<IComponent>> &
  components() const noexcept;

  /**
   * @brief Register an input component's name
   *
   * @param name Name of the input component
   */
  void addInputName(const std::string &name);

  /**
   * @brief Register an output component's name
   *
   * @param name Name of the output component
   */
  void addOutputName(const std::string &name);

  /**
   * @brief Register a clock component's name
   *
   * @param name Name of the clock component
   */
  void addClockName(const std::string &name);

  /**
   * @brief Simulate one tick of the circuit
   */
  void simulate();

  /**
   * @brief Compute the state of all outputs in the circuit
   */
  void computeAllOutputs();

  /**
   * @brief Display the current state of the circuit
   */
  void display() const;

  /**
   * @brief Set the value of an input component
   *
   * @param name The name of the input
   * @param value The value to set (e.g., "1", "0", "U")
   */
  void setInputValue(const std::string &name, const std::string &value);

  /**
   * @brief Get the list of input names
   *
   * @return const std::vector<std::string>& The input names
   */
  [[nodiscard]] const std::vector<std::string> &inputNames() const noexcept;

  /**
   * @brief Get the list of output names
   *
   * @return const std::vector<std::string>& The output names
   */
  [[nodiscard]] const std::vector<std::string> &outputNames() const noexcept;

  /**
   * @brief Get the current simulation tick
   *
   * @return std::size_t The current tick
   */
  [[nodiscard]] std::size_t tick() const noexcept;

private:
  std::map<std::string, std::unique_ptr<IComponent>> _components;
  std::vector<std::string> _inputNames;
  std::vector<std::string> _outputNames;
  std::vector<std::string> _clockNames;
  std::size_t _tick = 0;
};

} // namespace nts

#endif /* !NTS_CIRCUIT_HPP_ */
