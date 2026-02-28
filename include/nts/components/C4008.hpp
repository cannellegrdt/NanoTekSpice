/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4008 chipset declaration
*/

#ifndef NTS_COMPONENTS_C4008_HPP_
#define NTS_COMPONENTS_C4008_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief C4008: 4-bit Full Adder (16-pin DIP).
     *
     * Inputs:
     *   A1=7, A2=5, A3=3, A4=1   (bit 0 to 3 of operand A)
     *   B1=6, B2=4, B3=2, B4=15  (bit 0 to 3 of operand B)
     *   Cin=9                     (carry in)
     * Outputs:
     *   Sum0=10, Sum1=11, Sum2=12, Sum3=13  (4-bit result)
     *   Cout=14                             (carry out)
     * Pins 8 (VSS) and 16 (VDD) are power pins and are ignored.
     */
    class C4008 : public AComponent {
    public:
        /**
         * @brief Constructs a C4008 and initializes internal state.
         * @param name The name of the component.
         */
        explicit C4008(const std::string &name);
        ~C4008() override = default;

        /**
         * @brief Reads all inputs, computes the 4-bit sum and carry out,
         *        and stores the results in the output pins cache.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Returns the pre-computed value at the requested output pin.
         * @param pin The chipset pin number to evaluate.
         * @return The Tristate value at that pin.
         * @throws NtsException if the pin is 8 (VSS), 16 (VDD), or invalid.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_C4008_HPP_ */
