/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4514 chipset declaration
*/

#ifndef NTS_COMPONENTS_C4514_HPP_
#define NTS_COMPONENTS_C4514_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief C4514: 4-to-16 Line Decoder/Demultiplexer with Latch (24-pin DIP).
     *
     * Decodes a 4-bit address into one of 16 active-high outputs.
     * The address is latched while Strobe is high (transparent latch).
     * All outputs are forced to False when Inhibit is high.
     *
     * Address inputs: A0=2, A1=3, A2=21, A3=22
     * Control:        Strobe=1, Inhibit=23
     * Outputs:
     *   Y0=11, Y1=9,  Y2=10, Y3=8,  Y4=7,  Y5=6,  Y6=5,  Y7=4,
     *   Y8=18, Y9=17, Y10=20, Y11=19, Y12=14, Y13=13, Y14=16, Y15=15
     * Pins 12, 24 are power pins and are ignored.
     */
    class C4514 : public AComponent {
    private:
        int _latchedAddress;
        int _nextAddress;
        Tristate _lastStrobe;

    public:
        /**
         * @brief Constructs a C4514 and initializes the latched address to 0.
         * @param name The name of the component.
         */
        explicit C4514(const std::string &name);
        ~C4514() override = default;

        /**
         * @brief Reads address inputs and updates the latch when Strobe is high.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Returns True for the active output matching the latched address,
         *        False otherwise. Returns False for all outputs when Inhibit is high.
         * @param pin The chipset pin number to evaluate.
         * @return The Tristate value at that pin.
         * @throws NtsException if the pin is 12, 24 (power), or invalid.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_C4514_HPP_ */
