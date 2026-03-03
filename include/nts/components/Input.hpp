/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Input component declaration
*/

#ifndef NTS_COMPONENTS_INPUT_HPP_
#define NTS_COMPONENTS_INPUT_HPP_

#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief Input component representing a user-controlled signal source.
     *
     * A single-pin component (pin 1). Its value is set via setValue() and
     * applied to pin 1 only when simulate() is called (double-buffering pattern).
     * The initial value is Undefined.
     */
    class Input : public AComponent {
    public:
        /**
         * @brief Constructs an Input component.
         * @param name The name of the component.
         */
        explicit Input(const std::string &name);
        ~Input() override = default;

        /**
         * @brief Applies the pending value (_nextValue) to pin 1 and updates the tick counter.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Returns the current value stored at pin 1.
         * @param pin Must be 1 (the only valid pin for Input).
         * @return The Tristate value at pin 1.
         * @throws NtsException if pin != 1.
         */
        Tristate compute(std::size_t pin) override;

        /**
         * @brief Schedules a new value to be applied on the next simulate() call.
         * @param val The Tristate value to schedule (True, False, or Undefined).
         */
        void setValue(Tristate val);

        /**
         * @brief IComponent hook: injects an external value (delegates to setValue).
         */
        void setExternalValue(Tristate value) override;

    protected:
        Tristate _nextValue;
    };

}

#endif /* !NTS_COMPONENTS_INPUT_HPP_ */
