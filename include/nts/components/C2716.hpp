/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C2716 chipset declaration
*/

#ifndef NTS_COMPONENTS_C2716_HPP_
#define NTS_COMPONENTS_C2716_HPP_

#include <cstdint>
#include <string>
#include <vector>
#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief C2716: 2048 x 8-bit EPROM / ROM (24-pin DIP).
     *
     * Read-only memory, content is loaded from a binary file at construction.
     * Output is available when both CE and OE are active (high).
     *
     * Control:
     *   CE=18 (Chip Enable, active high), OE=20 (Output Enable, active high)
     * Address (11 bits):
     *   A0=8, A1=7, A2=6, A3=5, A4=4, A5=3, A6=2, A7=1,
     *   A8=23, A9=22, A10=19
     * Outputs:
     *   D0=9, D1=10, D2=11, D3=13, D4=14, D5=15, D6=16, D7=17
     * Pins 12, 21, 24 are power pins and are ignored.
     */
    class C2716 : public AComponent {
    private:
        std::vector<uint8_t> _data;

        /**
         * @brief Loads up to 2048 bytes from a binary file into _data.
         *        Pads with 0xFF if the file is smaller than 2048 bytes.
         * @param path Path to the binary ROM file.
         * @throws NtsException if the file cannot be opened.
         */
        void loadFromFile(const std::string &path);

    public:
        /**
         * @brief Constructs a C2716 and loads the ROM content from "./rom.bin".
         * @param name The name of the component.
         */
        explicit C2716(const std::string &name);
        ~C2716() override = default;

        /**
         * @brief Updates the tick (purely read-only component, no state change).
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Returns the bit value at the requested output pin when CE and
         *        OE are both active, Undefined otherwise.
         * @param pin The chipset pin number to evaluate.
         * @return The Tristate value at that pin.
         * @throws NtsException if the pin is 12, 21, 24 (power), or invalid.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_C2716_HPP_ */
