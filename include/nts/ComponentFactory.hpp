/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Concrete factory implementation
*/

#ifndef NTS_COMPONENTFACTORY_HPP_
#define NTS_COMPONENTFACTORY_HPP_

#include "nts/Factory.hpp"

namespace nts {

/**
 * @brief Concrete factory that instantiates all built-in NanoTekSpice components.
 *
 * Implements IComponentFactory by maintaining a static map of type-string
 * to creator lambdas. Each lambda constructs the matching concrete class and
 * returns it as a unique_ptr<IComponent>.
 *
 * Supported types: input, output, true, false, clock, and, or, xor, not,
 * 4001, 4011, 4030, 4069, 4071, 4081, 4008, 4013, 4017, 4040, 4094,
 * 4512, 4514, 4801, 2716, logger.
 */
class ComponentFactory : public IComponentFactory {
public:
  /**
   * @brief Creates a component of the given type with the given name.
   * @param type  The component type string (e.g. "input", "4001").
   * @param name  The instance name assigned to the component.
   * @return A unique_ptr<IComponent> owning the newly created component.
   * @throws NtsException if @p type is not a known component type.
   */
  std::unique_ptr<IComponent>
  createComponent(const std::string &type,
                  const std::string &name) const override;
};

} // namespace nts

#endif /* !NTS_COMPONENTFACTORY_HPP_ */
