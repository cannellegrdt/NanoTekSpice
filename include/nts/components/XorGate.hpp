/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Xor gate component declaration
*/

#ifndef NTS_COMPONENTS_XORGATE_HPP_
#define NTS_COMPONENTS_XORGATE_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief Two-input XOR gate (pins 1, 2: inputs — pin 3: output).
     *
     * Computes TristateLogic::xorGate(A, B) on the values linked to pins 1 and 2.
     * Any Undefined input always yields Undefined output (no absorbing element).
     */
    class XorGate : public AComponent {
    public:
        /**
         * @brief Constructs a XorGate and initializes all pins to Undefined.
         * @param name The name of the component.
         */
        explicit XorGate(const std::string &name);
        ~XorGate() override = default;

        /**
         * @brief Updates the internal tick counter. No combinatorial state to flush.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Computes the value at the requested pin.
         *
         * - Pin 1 or 2 (inputs): returns the value propagated from the linked component.
         * - Pin 3 (output): returns TristateLogic::xorGate(A, B).
         *
         * @param pin The pin number to evaluate (1, 2, or 3).
         * @return The Tristate value at the given pin.
         * @throws NtsException if pin is not 1, 2, or 3.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_XORGATE_HPP_ */
