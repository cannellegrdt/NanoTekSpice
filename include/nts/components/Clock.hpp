/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Clock component declaration
*/

#ifndef NTS_COMPONENTS_CLOCK_HPP_
#define NTS_COMPONENTS_CLOCK_HPP_

#include "nts/components/Input.hpp"

namespace nts {

    /**
     * @brief Clock component that automatically toggles its output each simulation tick.
     *
     * Inherits from Input. On each simulate(), the current _nextValue is first applied
     * to pin 1 (via Input::simulate), then toggled (True <-> False) for the next tick.
     * If _nextValue is Undefined, no toggle occurs.
     *
     * Initial value: Undefined. Must be set via setValue() before toggling begins.
     */
    class Clock : public Input {
    public:
        /**
         * @brief Constructs a Clock component.
         * @param name The name of the component.
         */
        explicit Clock(const std::string &name);
        ~Clock() override = default;

        /**
         * @brief Applies the current value to pin 1, then toggles _nextValue for the next tick.
         *
         * Calls Input::simulate(tick) to apply _nextValue to pin 1, then flips _nextValue:
         * - True  -> False
         * - False -> True
         * - Undefined -> Undefined (no toggle until a value is explicitly set)
         *
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;
    };

}

#endif /* !NTS_COMPONENTS_CLOCK_HPP_ */
