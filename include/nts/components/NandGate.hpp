/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** NandGate component declaration
*/

#ifndef NTS_COMPONENTS_NANDGATE_HPP_
#define NTS_COMPONENTS_NANDGATE_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief Two-input NAND gate (pins 1, 2: inputs — pin 3: output).
     *
     * Computes TristateLogic::nandGate(A, B) on the values linked to pins 1
     * and 2. Primarily intended for internal use inside AGateComponent
     * subclasses (e.g. C4011).
     */
    class NandGate : public AComponent {
    public:
        /**
         * @brief Constructs a NandGate and initializes all pins to Undefined.
         * @param name The name of the component.
         */
        explicit NandGate(const std::string &name);
        ~NandGate() override = default;

        /**
         * @brief Updates the internal tick counter. No combinatorial state to
         *        flush.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Computes the value at the requested pin.
         *
         * - Pin 1 or 2 (inputs): returns the value propagated from the linked
         *   component.
         * - Pin 3 (output): returns TristateLogic::nandGate(A, B).
         *
         * @param pin The pin number to evaluate (1, 2, or 3).
         * @return The Tristate value at the given pin.
         * @throws NtsException if pin is not 1, 2, or 3.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_NANDGATE_HPP_ */
