/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Lexer class declaration
*/

#ifndef NTS_LEXER_HPP_
#define NTS_LEXER_HPP_

#include <string>

namespace nts {

    enum class TokenType {
        CHIPSETS_SECTION,
        LINKS_SECTION,
        IDENTIFIER,
        NUMBER,
        COLON,
        NEWLINE,
        EOF_TOKEN,
        UNKNOWN
    };

    struct Token {
        TokenType type;
        std::string value;
        std::size_t line;
        std::size_t col;

        Token(TokenType t, const std::string& v, std::size_t l, std::size_t c)
            : type(t), value(v), line(l), col(c) {}
        Token() : type(TokenType::UNKNOWN), value(""), line(0), col(0) {}
    };

    class Lexer {
    public:
        explicit Lexer(const std::string& input);
        ~Lexer() = default;

        Lexer(const Lexer&) = delete;
        Lexer& operator=(const Lexer&) = delete;
        Lexer(Lexer&&) noexcept = default;
        Lexer& operator=(Lexer&&) noexcept = default;

        Token nextToken();

    private:
        std::string _input;
        std::size_t _pos;
        std::size_t _line;
        std::size_t _col;

        char peekChar() const;
        char advanceChar();
        void skipWhitespace();
        void skipComment();
        Token parseIdentifierOrKeyword();
        Token parseNumber();
    };

}

#endif /* !NTS_LEXER_HPP_ */
