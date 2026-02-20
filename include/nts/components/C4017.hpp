/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4017 chipset declaration
*/

#ifndef NTS_COMPONENTS_C4017_HPP_
#define NTS_COMPONENTS_C4017_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief C4017: Johnson Decade Counter (16-pin DIP).
     *
     * Counts from 0 to 9, activating one output at a time.
     *
     * Inputs:
     *   Clock=14, ClockInhibit=13, Reset=15
     * Outputs (one active high at a time):
     *   Q0=3, Q1=2, Q2=4, Q3=7, Q4=10,
     *   Q5=1, Q6=5, Q7=6, Q8=9, Q9=11
     *   CarryOut=12  (high for counts 0–4, low for 5–9)
     * Pins 8 (VSS) and 16 (VDD) are power pins and are ignored.
     *
     * The counter increments on the rising edge of Clock,
     * unless ClockInhibit is high. Reset (high) asynchronously
     * resets the counter to 0.
     */
    class C4017 : public AComponent {
    private:
        int _counter;
        int _counter_next;
        Tristate _lastClock;

    public:
        /**
         * @brief Constructs a C4017 and initializes the counter to 0.
         * @param name The name of the component.
         */
        explicit C4017(const std::string &name);
        ~C4017() override = default;

        /**
         * @brief Advances the decade counter based on clock, inhibit and reset.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Returns the decoded output value for the requested pin.
         * @param pin The chipset pin number to evaluate.
         * @return The Tristate value at that pin.
         * @throws NtsException if the pin is 8 (VSS), 16 (VDD), or invalid.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_C4017_HPP_ */
