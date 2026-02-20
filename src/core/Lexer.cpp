/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Lexer implementation
*/

#include "nts/Lexer.hpp"
#include <cctype>

namespace nts {

Lexer::Lexer(const std::string &input)
    : _input(input), _pos(0), _line(1), _col(1) {}

char Lexer::peekChar() const {
  if (_pos >= _input.length()) {
    return '\0';
  }
  return _input[_pos];
}

char Lexer::advanceChar() {
  if (_pos >= _input.length()) {
    return '\0';
  }
  char c = _input[_pos];
  _pos++;
  if (c == '\n') {
    _line++;
    _col = 1;
  } else {
    _col++;
  }
  return c;
}

void Lexer::skipComment() {
  while (peekChar() != '\n' && peekChar() != '\0') {
    advanceChar();
  }
}

void Lexer::skipWhitespace() {
  while (true) {
    char c = peekChar();
    if (c == ' ' || c == '\t' || c == '\r') {
      advanceChar();
    } else if (c == '#') {
      skipComment();
    } else {
      break;
    }
  }
}

Token Lexer::nextToken() {
  skipWhitespace();

  std::size_t startLine = _line;
  std::size_t startCol = _col;
  char c = peekChar();

  switch (c) {
  case '\0':
    return Token(TokenType::EOF_TOKEN, "", startLine, startCol);
  case '\n':
    advanceChar();
    return Token(TokenType::NEWLINE, "\n", startLine, startCol);
  case ':':
    advanceChar();
    return Token(TokenType::COLON, ":", startLine, startCol);
  default:
    if (std::isalpha(c) || c == '.' || c == '_') {
      return parseIdentifierOrKeyword();
    }
    if (std::isdigit(c)) {
      std::size_t savePos = _pos;
      bool hasAlpha = false;
      while (savePos < _input.length() &&
             (std::isalnum(_input[savePos]) || _input[savePos] == '_')) {
        if (std::isalpha(_input[savePos]) || _input[savePos] == '_') {
          hasAlpha = true;
          break;
        }
        savePos++;
      }
      return hasAlpha ? parseIdentifierOrKeyword() : parseNumber();
    }
    advanceChar();
    return Token(TokenType::UNKNOWN, std::string(1, c), startLine, startCol);
  }
}

Token Lexer::parseIdentifierOrKeyword() {
  std::size_t startLine = _line;
  std::size_t startCol = _col;
  std::string value;

  while (std::isalnum(peekChar()) || peekChar() == '_' || peekChar() == '.') {
    value += advanceChar();
  }

  if (value == ".chipsets") {
    return Token(TokenType::CHIPSETS_SECTION, value, startLine, startCol);
  }
  if (value == ".links") {
    return Token(TokenType::LINKS_SECTION, value, startLine, startCol);
  }

  return Token(TokenType::IDENTIFIER, value, startLine, startCol);
}

Token Lexer::parseNumber() {
  std::size_t startLine = _line;
  std::size_t startCol = _col;
  std::string value;

  while (std::isdigit(peekChar())) {
    value += advanceChar();
  }

  return Token(TokenType::NUMBER, value, startLine, startCol);
}

}
