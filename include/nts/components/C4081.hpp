/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4081 chipset declaration
*/

#ifndef NTS_COMPONENTS_C4081_HPP_
#define NTS_COMPONENTS_C4081_HPP_

#include "nts/components/AGateComponent.hpp"

namespace nts {

    /**
     * @brief C4081: Quad 2-input AND gate (14-pin DIP).
     *
     * Contains 4 internal AndGate instances arranged as follows:
     *   Gate 1: pins 1, 2 (inputs) → pin 3  (output)
     *   Gate 2: pins 5, 6 (inputs) → pin 4  (output)
     *   Gate 3: pins 8, 9 (inputs) → pin 10 (output)
     *   Gate 4: pins 12,13 (inputs) → pin 11 (output)
     * Pins 7 (VSS) and 14 (VDD) are power pins and are ignored.
     */
    class C4081 : public AGateComponent {
    protected:
        /**
         * @brief Maps a C4081 chipset pin to the corresponding internal
         *        AndGate and its pin.
         *
         * @param pin The chipset pin number (1–14).
         * @return A pair { pointer to AndGate, AndGate pin number }.
         * @throws NtsException if the pin is 7 (VSS), 14 (VDD), or invalid.
         */
        std::pair<IComponent *, std::size_t> mapPinToGate(
            std::size_t pin) const override;

    public:
        /**
         * @brief Constructs a C4081 and initializes the 4 internal AndGates.
         * @param name The name of the component.
         */
        explicit C4081(const std::string &name);
        ~C4081() override = default;
    };

}

#endif /* !NTS_COMPONENTS_C4081_HPP_ */
