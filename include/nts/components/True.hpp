/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** True component declaration
*/

#ifndef NTS_COMPONENTS_TRUE_HPP_
#define NTS_COMPONENTS_TRUE_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief Constant component that always outputs True.
     *
     * A single-pin component (pin 1). compute() unconditionally returns
     * Tristate::True regardless of any links or simulation state.
     */
    class TrueComp : public AComponent {
    public:
        /**
         * @brief Constructs a TrueComp component.
         * @param name The name of the component.
         */
        explicit TrueComp(const std::string &name);
        ~TrueComp() override = default;

        /**
         * @brief Updates the internal tick counter. No logic to evaluate.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Always returns Tristate::True regardless of simulation state.
         * @param pin Must be 1.
         * @return Tristate::True unconditionally.
         * @throws NtsException if pin != 1.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_TRUE_HPP_ */
