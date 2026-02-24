/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** TristateLogic helper class (static methods only)
*/

#ifndef NTS_TRISTATELOGIC_HPP_
#define NTS_TRISTATELOGIC_HPP_

#include "nts/Tristate.hpp"

namespace nts {

/**
 * @brief Helper class containing static methods for operations on Tristate
 * values
 */
class TristateLogic {
public:
  TristateLogic() = delete;
  ~TristateLogic() = delete;

  /**
   * @brief Perform a logical AND operation between two Tristates
   *
   * @param a First operand
   * @param b Second operand
   * @return Tristate The result of the AND operation
   */
  static Tristate andGate(Tristate a, Tristate b) noexcept;

  /**
   * @brief Perform a logical OR operation between two Tristates
   *
   * @param a First operand
   * @param b Second operand
   * @return Tristate The result of the OR operation
   */
  static Tristate orGate(Tristate a, Tristate b) noexcept;

  /**
   * @brief Perform a logical XOR (exclusive OR) operation between two Tristates
   *
   * @param a First operand
   * @param b Second operand
   * @return Tristate The result of the XOR operation
   */
  static Tristate xorGate(Tristate a, Tristate b) noexcept;

  /**
   * @brief Perform a logical NOT operation on a Tristate
   *
   * @param a The operand
   * @return Tristate The result of the NOT operation
   */
  static Tristate notGate(Tristate a) noexcept;

  /**
   * @brief Perform a logical NAND operation between two Tristates
   *
   * @param a First operand
   * @param b Second operand
   * @return Tristate The result of the NAND operation
   */
  static Tristate nandGate(Tristate a, Tristate b) noexcept;

  /**
   * @brief Perform a logical NOR operation between two Tristates
   *
   * @param a First operand
   * @param b Second operand
   * @return Tristate The result of the NOR operation
   */
  static Tristate norGate(Tristate a, Tristate b) noexcept;

  /**
   * @brief Perform a logical XNOR (exclusive NOR) operation between two
   * Tristates
   *
   * @param a First operand
   * @param b Second operand
   * @return Tristate The result of the XNOR operation
   */
  static Tristate xnorGate(Tristate a, Tristate b) noexcept;
};

} // namespace nts

#endif /* !NTS_TRISTATELOGIC_HPP_ */
