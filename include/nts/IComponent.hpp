/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** IComponent interface declaration
*/

#ifndef NTS_ICOMPONENT_HPP_
#define NTS_ICOMPONENT_HPP_

#include <cstddef>

#include "nts/Tristate.hpp"

namespace nts {

/**
 * @brief Interface for all electronic components
 */
class IComponent {
public:
  /**
   * @brief Destroy the IComponent object
   */
  virtual ~IComponent() = default;

  /**
   * @brief Simulate the component's state for the given tick
   *
   * @param tick The current simulation tick
   */
  virtual void simulate(std::size_t tick) = 0;

  /**
   * @brief Compute the value of a specific pin
   *
   * @param pin The pin to compute
   * @return Tristate The computed state of the pin
   */
  virtual Tristate compute(std::size_t pin) = 0;

  /**
   * @brief Link a pin of this component to a pin of another component
   *
   * @param pin The pin on this component
   * @param other The other component to link to
   * @param otherPin The pin on the other component
   */
  virtual void setLink(std::size_t pin, IComponent &other,
                       std::size_t otherPin) = 0;

  /**
   * @brief Optional hook to establish a reverse link on the target component.
   *
   * Default implementation does nothing. Components that need symmetric
   * connections can override this.
   *
   * @param pin The pin on this component
   * @param other The other component participating in the link
   * @param otherPin The pin on the other component
   */
  virtual void setBackLink(std::size_t pin, IComponent &other,
                           std::size_t otherPin)
  {
    (void)pin;
    (void)other;
    (void)otherPin;
  }

  /**
   * @brief Optional hook to inject an external value into a component.
   *
   * Default implementation does nothing. Components that represent
   * user-controlled sources (inputs, clocks, etc.) can override this.
   *
   * @param value The tristate value to inject.
   */
  virtual void setExternalValue(Tristate value)
  {
    (void)value;
  }
};

} // namespace nts

#endif /* !NTS_ICOMPONENT_HPP_ */