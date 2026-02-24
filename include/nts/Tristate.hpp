/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Tristate enum declaration
*/

#ifndef NTS_TRISTATE_HPP_
#define NTS_TRISTATE_HPP_

namespace nts {

/**
 * @brief Represents the three possible states of a pin or node
 */
enum Tristate {
  Undefined = -1, /*!< The state is undefined (U) */
  False = 0,      /*!< The logical state is false (0) */
  True = 1        /*!< The logical state is true (1) */
};

} // namespace nts

#endif /* !NTS_TRISTATE_HPP_ */
