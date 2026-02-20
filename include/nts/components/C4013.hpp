/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4013 chipset declaration
*/

#ifndef NTS_COMPONENTS_C4013_HPP_
#define NTS_COMPONENTS_C4013_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief C4013: Dual D-Type Flip-Flop (14-pin DIP).
     *
     * Contains two independent edge-triggered D flip-flops with
     * asynchronous Set and Reset.
     *
     * Flip-Flop 1:
     *   Clock=3, Data=5, Set=6, Reset=4
     *   Q=1, Qbar=2
     * Flip-Flop 2:
     *   Clock=11, Data=9, Set=8, Reset=10
     *   Q=13, Qbar=12
     *
     * Set and Reset are asynchronous (active high).
     * Q is captured from D on the rising edge of Clock.
     */
    class C4013 : public AComponent {
    private:
        Tristate _q1;
        Tristate _q1_next;
        Tristate _q2;
        Tristate _q2_next;
        Tristate _lastClock1;
        Tristate _lastClock2;

    public:
        /**
         * @brief Constructs a C4013 and initializes both flip-flops to Undefined.
         * @param name The name of the component.
         */
        explicit C4013(const std::string &name);
        ~C4013() override = default;

        /**
         * @brief Updates both flip-flops by detecting rising clock edges
         *        and applying asynchronous Set/Reset signals.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Returns the current Q or Qbar value of the requested flip-flop.
         * @param pin The chipset pin number to evaluate.
         * @return The Tristate value at that pin.
         * @throws NtsException if the pin is 7 (VSS), 14 (VDD), or invalid.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_C4013_HPP_ */
