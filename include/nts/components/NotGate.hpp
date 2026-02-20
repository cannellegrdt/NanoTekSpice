/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Not gate component declaration
*/

#ifndef NTS_COMPONENTS_NOTGATE_HPP_
#define NTS_COMPONENTS_NOTGATE_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief Single-input NOT gate (pin 1: input — pin 2: output).
     *
     * Computes TristateLogic::notGate(A) on the value linked to pin 1.
     * Undefined input yields Undefined output.
     */
    class NotGate : public AComponent {
    public:
        /**
         * @brief Constructs a NotGate and initializes pins 1 and 2 to Undefined.
         * @param name The name of the component.
         */
        explicit NotGate(const std::string &name);
        ~NotGate() override = default;

        /**
         * @brief Updates the internal tick counter. No combinatorial state to flush.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Computes the value at the requested pin.
         *
         * - Pin 1 (input): returns the value propagated from the linked component.
         * - Pin 2 (output): returns TristateLogic::notGate(A) where A = pin 1.
         *
         * @param pin The pin number to evaluate (1 or 2).
         * @return The Tristate value at the given pin.
         * @throws NtsException if pin is not 1 or 2.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_NOTGATE_HPP_ */
