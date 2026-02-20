/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4512 chipset declaration
*/

#ifndef NTS_COMPONENTS_C4512_HPP_
#define NTS_COMPONENTS_C4512_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief C4512: 8-Channel Data Selector / Multiplexer (16-pin DIP).
     *
     * Selects one of 8 data inputs based on a 3-bit address.
     * Output is forced to False when Inhibit is high.
     * Output is Undefined when Enable is False (disabled).
     *
     * Address inputs:  A=11, B=12, C=13
     * Data inputs:     I0=1, I1=2, I2=3, I3=4, I4=5, I5=6, I6=7, I7=9
     * Control:         Inhibit=10, Enable=15
     * Output:          Z=14
     * Pins 8 (VSS) and 16 (VDD) are power pins and are ignored.
     *
     * Address decoding: A is LSB, C is MSB → channel = C*4 + B*2 + A
     */
    class C4512 : public AComponent {
    public:
        /**
         * @brief Constructs a C4512.
         * @param name The name of the component.
         */
        explicit C4512(const std::string &name);
        ~C4512() override = default;

        /**
         * @brief Updates the tick (purely combinational component).
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Evaluates the multiplexer output by reading address and data.
         * @param pin The chipset pin number to evaluate (must be 14).
         * @return The Tristate value of the selected data input.
         * @throws NtsException if the pin is 8 (VSS), 16 (VDD), or invalid.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_C4512_HPP_ */
