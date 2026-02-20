/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4040 chipset declaration
*/

#ifndef NTS_COMPONENTS_C4040_HPP_
#define NTS_COMPONENTS_C4040_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief C4040: 12-bit Binary Ripple Counter (16-pin DIP).
     *
     * Counts from 0 to 4095, incrementing on each falling edge of the Clock.
     * Reset (high) asynchronously resets the counter to 0.
     *
     * Inputs:
     *   Clock=10, Reset=11
     * Outputs (bit 0 to bit 11):
     *   Q0=9,  Q1=7,  Q2=6,  Q3=5,  Q4=3,  Q5=2,
     *   Q6=4,  Q7=13, Q8=12, Q9=14, Q10=15, Q11=1
     * Pins 8 (VSS) and 16 (VDD) are power pins and are ignored.
     */
    class C4040 : public AComponent {
    private:
        int _counter;
        int _counter_next;
        Tristate _lastClock;

    public:
        /**
         * @brief Constructs a C4040 and initializes the counter to 0.
         * @param name The name of the component.
         */
        explicit C4040(const std::string &name);
        ~C4040() override = default;

        /**
         * @brief Advances the binary counter on falling clock edge or resets it.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Returns the bit value of the counter at the requested output pin.
         * @param pin The chipset pin number to evaluate.
         * @return The Tristate value at that pin.
         * @throws NtsException if the pin is 8 (VSS), 16 (VDD), or invalid.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_C4040_HPP_ */
