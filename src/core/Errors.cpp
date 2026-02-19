/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Error classes implementation (skeleton)
*/

#include "nts/Errors.hpp"

namespace nts {

    NtsException::NtsException(const std::string &msg)
        : std::runtime_error(msg)
    {
    }

    ParseError::ParseError(const std::string &msg)
        : NtsException(msg)
    {
    }

}


