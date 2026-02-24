/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Parser class declaration
*/

#ifndef NTS_PARSER_HPP_
#define NTS_PARSER_HPP_

#include <iosfwd>
#include <string>

#include "nts/Lexer.hpp"

namespace nts {

class Circuit;
class IComponentFactory;

/**
 * @brief Parser class for parsing .nts files and creating circuits
 */
class Parser {
public:
  /**
   * @brief Construct a new Parser object
   *
   * @param factory The component factory used to create components
   */
  explicit Parser(IComponentFactory &factory);

  /**
   * @brief Destroy the Parser object
   */
  ~Parser() = default;

  Parser(const Parser &) = delete;
  Parser &operator=(const Parser &) = delete;

  Parser(Parser &&) noexcept = default;
  Parser &operator=(Parser &&) noexcept = delete;

  /**
   * @brief Parse a circuit from a file
   *
   * @param filepath The path to the file to parse
   * @return Circuit The parsed circuit
   */
  Circuit parse(const std::string &filepath) const;

  /**
   * @brief Parse a circuit from an input stream
   *
   * @param input The input stream to parse from
   * @return Circuit The parsed circuit
   */
  Circuit parse(std::istream &input) const;

private:
  IComponentFactory &_factory;

  mutable Lexer *_lexer = nullptr;
  mutable Token _currentToken;

  /**
   * @brief Advance the lexer to the next token
   */
  void advance() const;

  /**
   * @brief Get the current token without consuming it
   *
   * @return const Token& The current token
   */
  const Token &peek() const;

  /**
   * @brief Consume the current token if it matches the expected type
   *
   * @param expectedType The expected type of the token
   * @return Token The consumed token
   */
  Token eat(TokenType expectedType) const;

  /**
   * @brief Parse the chipsets section of the file
   *
   * @param circuit The circuit to add the chipsets to
   */
  void parseChipsets(Circuit &circuit) const;

  /**
   * @brief Parse the links section of the file
   *
   * @param circuit The circuit to add the links to
   */
  void parseLinks(Circuit &circuit) const;

  /**
   * @brief Parse a single chipset line
   *
   * @param circuit The circuit to add the chipset to
   */
  void parseChipsetLine(Circuit &circuit) const;

  /**
   * @brief Parse a single link line
   *
   * @param circuit The circuit to add the link to
   */
  void parseLinkLine(Circuit &circuit) const;

  /**
   * @brief Consume tokens until a newline is reached
   */
  void eatUntilNewline() const;
};

} // namespace nts

#endif /* !NTS_PARSER_HPP_ */
