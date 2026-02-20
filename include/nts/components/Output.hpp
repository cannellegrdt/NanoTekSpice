/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Output component declaration
*/

#ifndef NTS_COMPONENTS_OUTPUT_HPP_
#define NTS_COMPONENTS_OUTPUT_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief Output component used as a circuit result probe.
     *
     * A single-pin component (pin 1). Its value is determined at compute time
     * by reading the value of the component linked to its pin 1.
     */
    class Output : public AComponent {
    public:
        /**
         * @brief Constructs an Output component.
         * @param name The name of the component.
         */
        explicit Output(const std::string &name);
        ~Output() override = default;

        /**
         * @brief Updates the internal tick counter.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Reads and returns the value from the component linked to pin 1.
         * @param pin Must be 1 (the only valid pin for Output).
         * @return The Tristate value from the linked component, or Undefined if unlinked.
         * @throws NtsException if pin != 1.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_OUTPUT_HPP_ */
