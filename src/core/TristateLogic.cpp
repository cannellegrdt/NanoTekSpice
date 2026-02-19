/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** TristateLogic implementation
*/

#include "nts/TristateLogic.hpp"

namespace nts {

    Tristate TristateLogic::andGate(Tristate a, Tristate b) noexcept
    {
        if (a == False || b == False)
            return False;
        if (a == True && b == True)
            return True;
        return Undefined;
    }

    Tristate TristateLogic::orGate(Tristate a, Tristate b) noexcept
    {
        if (a == True || b == True)
            return True;
        if (a == False && b == False)
            return False;
        return Undefined;
    }

    Tristate TristateLogic::xorGate(Tristate a, Tristate b) noexcept
    {
        if (a == Undefined || b == Undefined)
            return Undefined;
        if (a == b)
            return False;
        return True;
    }

    Tristate TristateLogic::notGate(Tristate a) noexcept
    {
        if (a == True)
            return False;
        if (a == False)
            return True;
        return Undefined;
    }

    Tristate TristateLogic::nandGate(Tristate a, Tristate b) noexcept
    {
        return notGate(andGate(a, b));
    }

    Tristate TristateLogic::norGate(Tristate a, Tristate b) noexcept
    {
        return notGate(orGate(a, b));
    }

    Tristate TristateLogic::xnorGate(Tristate a, Tristate b) noexcept
    {
        return notGate(xorGate(a, b));
    }

}
