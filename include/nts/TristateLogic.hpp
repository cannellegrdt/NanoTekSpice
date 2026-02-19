/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** TristateLogic helper class (static methods only)
*/

#ifndef NTS_TRISTATELOGIC_HPP_
#define NTS_TRISTATELOGIC_HPP_

#include "nts/Tristate.hpp"

namespace nts {

    class TristateLogic {
    public:
        TristateLogic() = delete;
        ~TristateLogic() = delete;

        static Tristate andGate(Tristate a, Tristate b) noexcept;
        static Tristate orGate(Tristate a, Tristate b) noexcept;
        static Tristate xorGate(Tristate a, Tristate b) noexcept;
        static Tristate notGate(Tristate a) noexcept;
        static Tristate nandGate(Tristate a, Tristate b) noexcept;
        static Tristate norGate(Tristate a, Tristate b) noexcept;
        static Tristate xnorGate(Tristate a, Tristate b) noexcept;
    };

}

#endif /* !NTS_TRISTATELOGIC_HPP_ */
