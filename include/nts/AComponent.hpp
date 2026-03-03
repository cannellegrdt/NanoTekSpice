/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** AComponent abstract base class declaration
*/

#ifndef NTS_ACOMPONENT_HPP_
#define NTS_ACOMPONENT_HPP_

#include <map>
#include <string>

#include "nts/IComponent.hpp"

namespace nts {

/**
 * @brief Abstract base class for all components
 *
 * Provides default implementation for common component functionalities
 * such as name management, ticketing, links, and pin states.
 */
class AComponent : public IComponent {
protected:
  std::string _name;
  std::size_t _tick = 0;
  std::size_t _lastComputedTick = 0;
  std::map<std::size_t, std::pair<IComponent *, std::size_t>> _links;
  std::map<std::size_t, Tristate> _pins;
  bool _computing = false;

public:
  /**
   * @brief Destroy the AComponent object
   */
  ~AComponent() override = default;

  /**
   * @brief Get the name of the component
   *
   * @return const std::string& The component's name
   */
  const std::string &getName() const;

  /**
   * @brief Set the name of the component
   *
   * @param name The new name for the component
   */
  void setName(const std::string &name);

  /**
   * @brief Set a link between this component and another
   *
   * @param pin The pin on this component
   * @param other The other component to link to
   * @param otherPin The pin on the other component
   */
  void setLink(std::size_t pin, IComponent &other,
               std::size_t otherPin) override;

  /**
   * @brief Establish a reverse link on this component when another component
   *        links to us.
   *
   * Ensures symmetric wiring between components while avoiding infinite
   * recursion.
   *
   * @param pin The pin on this component
   * @param other The other component participating in the link
   * @param otherPin The pin on the other component
   */
  void setBackLink(std::size_t pin, IComponent &other,
                   std::size_t otherPin) override;

  /**
   * @brief Set the state of a specific pin
   *
   * @param pin The pin number
   * @param val The state to set
   */
  void setPin(std::size_t pin, Tristate val);

  /**
   * @brief Get the state of a specific pin
   *
   * @param pin The pin number
   * @return Tristate The state of the pin
   */
  Tristate getPin(std::size_t pin) const;

protected:
  /**
   * @brief Get the value from the linked component's pin
   *
   * @param pin The local pin number that is linked
   * @return Tristate The value from the linked component
   */
  Tristate getLinkValue(std::size_t pin);
};

} // namespace nts

#endif /* !NTS_ACOMPONENT_HPP_ */
