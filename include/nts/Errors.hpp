/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Error classes declaration
*/

#ifndef NTS_ERRORS_HPP_
#define NTS_ERRORS_HPP_

#include <stdexcept>
#include <string>

namespace nts {

/**
 * @brief Base exception class for nanoTekSpice errors
 */
class NtsException : public std::runtime_error {
public:
  /**
   * @brief Construct a new Nts Exception object
   *
   * @param msg The error message
   */
  explicit NtsException(const std::string &msg);
  ~NtsException() override = default;
};

/**
 * @brief Exception thrown when a parsing error occurs
 */
class ParseError : public NtsException {
public:
  /**
   * @brief Construct a new Parse Error object
   *
   * @param msg The parsing error message details
   */
  explicit ParseError(const std::string &msg);
  ~ParseError() override = default;
};

} // namespace nts

#endif /* !NTS_ERRORS_HPP_ */
