/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Factory interfaces
*/

#ifndef NTS_FACTORY_HPP_
#define NTS_FACTORY_HPP_

#include <memory>
#include <string>

namespace nts {

class IComponent;

/**
 * @brief Interface for a component factory
 */
class IComponentFactory {
public:
  /**
   * @brief Destroy the IComponentFactory object
   */
  virtual ~IComponentFactory() = default;

  /**
   * @brief Create a component of a specific type
   *
   * @param type The type of the component to create
   * @param name The name to assign to the component
   * @return std::unique_ptr<IComponent> A unique pointer to the created
   * component
   */
  virtual std::unique_ptr<IComponent>
  createComponent(const std::string &type, const std::string &name) const = 0;
};

} // namespace nts

#endif /* !NTS_FACTORY_HPP_ */
