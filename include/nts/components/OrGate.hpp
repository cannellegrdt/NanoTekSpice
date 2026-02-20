/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Or gate component declaration
*/

#ifndef NTS_COMPONENTS_ORGATE_HPP_
#define NTS_COMPONENTS_ORGATE_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief Two-input OR gate (pins 1, 2: inputs — pin 3: output).
     *
     * Computes TristateLogic::orGate(A, B) on the values linked to pins 1 and 2.
     * Undefined propagation follows the truth table defined in the project spec:
     * Undefined OR True = True, Undefined OR False = Undefined.
     */
    class OrGate : public AComponent {
    public:
        /**
         * @brief Constructs an OrGate and initializes all pins to Undefined.
         * @param name The name of the component.
         */
        explicit OrGate(const std::string &name);
        ~OrGate() override = default;

        /**
         * @brief Updates the internal tick counter. No combinatorial state to flush.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Computes the value at the requested pin.
         *
         * - Pin 1 or 2 (inputs): returns the value propagated from the linked component.
         * - Pin 3 (output): returns TristateLogic::orGate(A, B).
         *
         * @param pin The pin number to evaluate (1, 2, or 3).
         * @return The Tristate value at the given pin.
         * @throws NtsException if pin is not 1, 2, or 3.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_ORGATE_HPP_ */
