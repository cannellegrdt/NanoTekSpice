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


    class NtsException : public std::runtime_error {
    public:
        explicit NtsException(const std::string &msg);
        ~NtsException() override = default;
    };

    class ParseError : public NtsException {
    public:
        explicit ParseError(const std::string &msg);
        ~ParseError() override = default;
    };

}

#endif /* !NTS_ERRORS_HPP_ */


