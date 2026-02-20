/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** False component declaration
*/

#ifndef NTS_COMPONENTS_FALSE_HPP_
#define NTS_COMPONENTS_FALSE_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief Constant component that always outputs False.
     *
     * A single-pin component (pin 1). compute() unconditionally returns
     * Tristate::False regardless of any links or simulation state.
     */
    class FalseComp : public AComponent {
    public:
        /**
         * @brief Constructs a FalseComp component.
         * @param name The name of the component.
         */
        explicit FalseComp(const std::string &name);
        ~FalseComp() override = default;

        /**
         * @brief Updates the internal tick counter. No logic to evaluate.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Always returns Tristate::False regardless of simulation state.
         * @param pin Must be 1.
         * @return Tristate::False unconditionally.
         * @throws NtsException if pin != 1.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_FALSE_HPP_ */
