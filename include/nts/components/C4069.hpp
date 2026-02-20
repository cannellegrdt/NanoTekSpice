/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4069 chipset declaration
*/

#ifndef NTS_COMPONENTS_C4069_HPP_
#define NTS_COMPONENTS_C4069_HPP_

#include "nts/components/AGateComponent.hpp"

namespace nts {

    /**
     * @brief C4069: Hex inverter / 6x NOT gate (14-pin DIP).
     *
     * Contains 6 internal NotGate instances arranged as follows:
     *   Gate 1: pin 1  (input) → pin 2  (output)
     *   Gate 2: pin 3  (input) → pin 4  (output)
     *   Gate 3: pin 5  (input) → pin 6  (output)
     *   Gate 4: pin 9  (input) → pin 8  (output)
     *   Gate 5: pin 11 (input) → pin 10 (output)
     *   Gate 6: pin 13 (input) → pin 12 (output)
     * Pins 7 (VSS) and 14 (VDD) are power pins and are ignored.
     */
    class C4069 : public AGateComponent {
    protected:
        /**
         * @brief Maps a C4069 chipset pin to the corresponding internal
         *        NotGate and its pin.
         *
         * @param pin The chipset pin number (1–14).
         * @return A pair { pointer to NotGate, NotGate pin number }.
         * @throws NtsException if the pin is 7 (VSS), 14 (VDD), or invalid.
         */
        std::pair<IComponent *, std::size_t> mapPinToGate(
            std::size_t pin) const override;

    public:
        /**
         * @brief Constructs a C4069 and initializes the 6 internal NotGates.
         * @param name The name of the component.
         */
        explicit C4069(const std::string &name);
        ~C4069() override = default;
    };

}

#endif /* !NTS_COMPONENTS_C4069_HPP_ */
