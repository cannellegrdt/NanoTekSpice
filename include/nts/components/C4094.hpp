/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4094 chipset declaration
*/

#ifndef NTS_COMPONENTS_C4094_HPP_
#define NTS_COMPONENTS_C4094_HPP_

#include <vector>
#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief C4094: 8-bit Serial-Input/Parallel-Output Shift Register (16-pin DIP).
     *
     * Data is shifted in serially on each rising edge of Clock.
     * The shift register content is transparently latched to the parallel
     * outputs while Strobe is high, and held when Strobe goes low.
     * Outputs are enabled by Output Enable (pin 15, active high).
     *
     * Inputs:
     *   Strobe=1, Data=2, Clock=3, OutputEnable=15
     * Outputs (parallel, from latch):
     *   Q0=4, Q1=5, Q2=6, Q3=7, Q4=14, Q5=13, Q6=12, Q7=11
     * Serial outputs:
     *   Qs=9  (MSB of shift register, before latching)
     *   Qe=10 (MSB of output latch)
     * Pins 8 (VSS) and 16 (VDD) are power pins and are ignored.
     */
    class C4094 : public AComponent {
    private:
        std::vector<Tristate> _registers;
        std::vector<Tristate> _registers_next;
        Tristate _lastClock;

    public:
        /**
         * @brief Constructs a C4094 and initializes both shift and latch
         *        registers to Undefined.
         * @param name The name of the component.
         */
        explicit C4094(const std::string &name);
        ~C4094() override = default;

        /**
         * @brief Shifts data in on rising clock edge and updates the output
         *        latch according to the Strobe signal.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Returns the value at the requested output pin, gated by
         *        Output Enable.
         * @param pin The chipset pin number to evaluate.
         * @return The Tristate value at that pin.
         * @throws NtsException if the pin is 8 (VSS), 16 (VDD), or invalid.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_C4094_HPP_ */
