/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** C4801 chipset declaration
*/

#ifndef NTS_COMPONENTS_C4801_HPP_
#define NTS_COMPONENTS_C4801_HPP_

#include <cstdint>
#include <map>
#include <vector>
#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief C4801: 1024 x 8-bit Static RAM (24-pin DIP).
     *
     * Stores 1024 bytes. Writes are committed on simulate() (double-buffering).
     * Reads are available immediately in compute() when CE and OE are active.
     *
     * Control:
     *   CE=18 (Chip Enable, active high), WE=21 (Write Enable, active high),
     *   OE=20 (Output Enable, active high)
     * Address (10 bits):
     *   A0=8, A1=7, A2=6, A3=5, A4=4, A5=3, A6=2, A7=1, A8=23, A9=22
     * Data I/O (bidirectional):
     *   D0=9, D1=10, D2=11, D3=13, D4=14, D5=15, D6=16, D7=17
     * Pins 12, 19, 24 are power pins and are ignored.
     */
    class C4801 : public AComponent {
    private:
        std::vector<uint8_t> _memory;
        std::map<std::size_t, uint8_t> _nextMemory;

    public:
        /**
         * @brief Constructs a C4801 and zero-initializes the 1024-byte memory.
         * @param name The name of the component.
         */
        explicit C4801(const std::string &name);
        ~C4801() override = default;

        /**
         * @brief Commits any pending writes to memory, then checks for new
         *        write requests for the current tick.
         * @param tick The current simulation tick.
         */
        void simulate(std::size_t tick) override;

        /**
         * @brief Returns the bit value at the requested data pin when reading,
         *        or Undefined when the chip is disabled or in write mode.
         * @param pin The chipset pin number to evaluate.
         * @return The Tristate value at that pin.
         * @throws NtsException if the pin is 12, 19, 24 (power), or invalid.
         */
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_C4801_HPP_ */
