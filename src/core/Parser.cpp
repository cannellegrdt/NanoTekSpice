/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Parser implementation
*/

#include "nts/Parser.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "nts/AComponent.hpp"
#include "nts/Circuit.hpp"
#include "nts/Errors.hpp"
#include "nts/Factory.hpp"
#include "nts/IComponent.hpp"

namespace nts {

Parser::Parser(IComponentFactory &factory) : _factory(factory) {}

void Parser::advance() const {
  if (_lexer) {
    _currentToken = _lexer->nextToken();
  }
}

Token Parser::peek() const {
  return _currentToken;
}

Token Parser::eat(TokenType expectedType) const {
  if (_currentToken.type != expectedType) {
    std::ostringstream oss;
    oss << "Parse error at line " << _currentToken.line << ", col "
        << _currentToken.col << ": expected token type "
        << static_cast<int>(expectedType) << " but got "
        << static_cast<int>(_currentToken.type) << " ('" << _currentToken.value
        << "')";
    throw ParseError(oss.str());
  }
  Token t = _currentToken;
  advance();
  return t;
}

void Parser::eatUntilNewline() const {
  while (peek().type != TokenType::NEWLINE &&
         peek().type != TokenType::EOF_TOKEN) {
    advance();
  }
  if (peek().type == TokenType::NEWLINE) {
    eat(TokenType::NEWLINE);
  }
}

Circuit Parser::parse(const std::string &filepath) const {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw ParseError("Cannot open file: '" + filepath + "'");
  }
  return parse(file);
}

Circuit Parser::parse(std::istream &input) const {
  std::ostringstream ss;
  ss << input.rdbuf();
  Lexer lexer(ss.str());

  _lexer = &lexer;
  advance();

  Circuit circuit;
  bool inChipsets = false;
  bool inLinks = false;

  while (peek().type != TokenType::EOF_TOKEN) {
    if (peek().type == TokenType::NEWLINE) {
      eat(TokenType::NEWLINE);
      continue;
    }

    if (peek().type == TokenType::CHIPSETS_SECTION) {
      if (inChipsets || inLinks) {
        throw ParseError("Multiple or misplaced '.chipsets:' section");
      }
      eat(TokenType::CHIPSETS_SECTION);
      if (peek().type == TokenType::COLON) {
        eat(TokenType::COLON);
      }
      eatUntilNewline();
      inChipsets = true;
      continue;
    }

    if (peek().type == TokenType::LINKS_SECTION) {
      if (!inChipsets || inLinks) {
        throw ParseError("'.links:' section must appear after '.chipsets:'");
      }
      eat(TokenType::LINKS_SECTION);
      if (peek().type == TokenType::COLON) {
        eat(TokenType::COLON);
      }
      eatUntilNewline();
      inLinks = true;
      continue;
    }

    if (!inChipsets && !inLinks) {
      throw ParseError("Content outside of any section");
    }

    if (inChipsets && !inLinks) {
      parseChipsetLine(circuit);
    } else if (inLinks) {
      parseLinkLine(circuit);
    }
  }

  _lexer = nullptr;

  if (circuit.components().empty()) {
    throw ParseError("No chipsets defined in circuit");
  }

  return circuit;
}

void Parser::parseChipsets(Circuit &circuit) const {
  while (peek().type != TokenType::EOF_TOKEN &&
         peek().type != TokenType::LINKS_SECTION) {
    if (peek().type == TokenType::NEWLINE) {
      eat(TokenType::NEWLINE);
      continue;
    }
    if (peek().type == TokenType::EOF_TOKEN) {
      break;
    }
    parseChipsetLine(circuit);
  }
}

void Parser::parseLinks(Circuit &circuit) const {
  while (peek().type != TokenType::EOF_TOKEN) {
    if (peek().type == TokenType::NEWLINE) {
      eat(TokenType::NEWLINE);
      continue;
    }
    if (peek().type == TokenType::EOF_TOKEN) {
      break;
    }
    parseLinkLine(circuit);
  }
}

void Parser::parseChipsetLine(Circuit &circuit) const {
  auto parseTypeOrName = [&]() -> Token {
    Token t = peek();
    if (t.type == TokenType::IDENTIFIER || t.type == TokenType::NUMBER) {
      advance();
      return t;
    }
    std::ostringstream oss;
    oss << "Parse error at line " << t.line << ", col " << t.col
        << ": expected IDENTIFIER or NUMBER but got "
        << static_cast<int>(t.type) << " ('" << t.value << "')";
    throw ParseError(oss.str());
  };

  Token typeToken = parseTypeOrName();
  Token nameToken = parseTypeOrName();

  if (peek().type != TokenType::NEWLINE &&
      peek().type != TokenType::EOF_TOKEN) {
    throw ParseError("Invalid extra characters at end of chipset line");
  }
  eatUntilNewline();

  std::string type = typeToken.value;
  std::string name = nameToken.value;

  std::unique_ptr<IComponent> component = _factory.createComponent(type);

  if (AComponent *acomp = dynamic_cast<AComponent *>(component.get())) {
    acomp->setName(name);
  }

  circuit.addComponent(name, std::move(component));

  if (type == "input")
    circuit.addInputName(name);
  else if (type == "output")
    circuit.addOutputName(name);
  else if (type == "clock")
    circuit.addClockName(name);
}

void Parser::parseLinkLine(Circuit &circuit) const {
  auto parseEndpoint = [&]() -> std::pair<std::string, std::size_t> {
    Token nameToken = peek();
    if (nameToken.type == TokenType::IDENTIFIER ||
        nameToken.type == TokenType::NUMBER) {
      advance();
    } else {
      std::ostringstream oss;
      oss << "Parse error at line " << nameToken.line << ", col "
          << nameToken.col << ": expected IDENTIFIER or NUMBER but got "
          << static_cast<int>(nameToken.type) << " ('" << nameToken.value
          << "')";
      throw ParseError(oss.str());
    }

    eat(TokenType::COLON);
    Token pinToken = eat(TokenType::NUMBER);

    std::string name = nameToken.value;
    std::size_t pin = 0;
    try {
      pin = static_cast<std::size_t>(std::stoul(pinToken.value));
    } catch (const std::exception &) {
      throw ParseError("Invalid pin number: '" + pinToken.value + "'");
    }
    if (pin == 0) {
      throw ParseError("Pin numbers must be >= 1");
    }
    return {name, pin};
  };

  auto [leftName, leftPin] = parseEndpoint();
  auto [rightName, rightPin] = parseEndpoint();

  if (peek().type != TokenType::NEWLINE &&
      peek().type != TokenType::EOF_TOKEN) {
    throw ParseError("Invalid extra characters at end of link line");
  }
  eatUntilNewline();

  IComponent &leftComp = circuit.getComponent(leftName);
  IComponent &rightComp = circuit.getComponent(rightName);

  leftComp.setLink(leftPin, rightComp, rightPin);
}

}
