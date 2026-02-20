/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4030 chipset declaration
*/

#ifndef NTS_COMPONENTS_C4030_HPP_
#define NTS_COMPONENTS_C4030_HPP_

#include "nts/components/AGateComponent.hpp"

namespace nts {

    /**
     * @brief C4030: Quad 2-input XOR gate (14-pin DIP).
     *
     * Contains 4 internal XorGate instances arranged as follows:
     *   Gate 1: pins 1, 2 (inputs) → pin 3  (output)
     *   Gate 2: pins 5, 6 (inputs) → pin 4  (output)
     *   Gate 3: pins 8, 9 (inputs) → pin 10 (output)
     *   Gate 4: pins 12,13 (inputs) → pin 11 (output)
     * Pins 7 (VSS) and 14 (VDD) are power pins and are ignored.
     */
    class C4030 : public AGateComponent {
    protected:
        /**
         * @brief Maps a C4030 chipset pin to the corresponding internal
         *        XorGate and its pin.
         *
         * @param pin The chipset pin number (1–14).
         * @return A pair { pointer to XorGate, XorGate pin number }.
         * @throws NtsException if the pin is 7 (VSS), 14 (VDD), or invalid.
         */
        std::pair<IComponent *, std::size_t> mapPinToGate(
            std::size_t pin) const override;

    public:
        /**
         * @brief Constructs a C4030 and initializes the 4 internal XorGates.
         * @param name The name of the component.
         */
        explicit C4030(const std::string &name);
        ~C4030() override = default;
    };

}

#endif /* !NTS_COMPONENTS_C4030_HPP_ */
