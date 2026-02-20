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

class Parser {
public:
  explicit Parser(IComponentFactory &factory);
  ~Parser() = default;

  Parser(const Parser &) = delete;
  Parser &operator=(const Parser &) = delete;

  Parser(Parser &&) noexcept = default;
  Parser &operator=(Parser &&) noexcept = default;

  Circuit parse(const std::string &filepath) const;
  Circuit parse(std::istream &input) const;

private:
  IComponentFactory &_factory;

  mutable Lexer *_lexer = nullptr;
  mutable Token _currentToken;

  void advance() const;
  const Token &peek() const;
  Token eat(TokenType expectedType) const;

  void parseChipsets(Circuit &circuit) const;
  void parseLinks(Circuit &circuit) const;

  void parseChipsetLine(Circuit &circuit) const;
  void parseLinkLine(Circuit &circuit) const;

  void eatUntilNewline() const;
};

}

#endif /* !NTS_PARSER_HPP_ */
