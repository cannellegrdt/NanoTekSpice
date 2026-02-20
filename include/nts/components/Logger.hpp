/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Logger component declaration
*/

#ifndef NTS_COMPONENTS_LOGGER_HPP_
#define NTS_COMPONENTS_LOGGER_HPP_

#include <fstream>
#include "nts/AComponent.hpp"

namespace nts {

    /**
     * @brief Logger: writes 8-bit characters to a binary file on rising clock edge.
     *
     * Inputs:
     *   D0-D7 (pins 1-8): 8-bit character data (D0 = LSB, D7 = MSB)
     *   CLK   (pin 9)   : write is triggered on rising edge
     *   INH   (pin 10)  : when True, suppresses any write
     *
     * Output file: "./log.bin" (opened in binary append mode at construction).
     */
    class Logger : public AComponent {
    private:
        std::ofstream _fileStream;
        Tristate _lastClock;

    public:
        explicit Logger(const std::string &name);
        ~Logger() override = default;

        void simulate(std::size_t tick) override;
        Tristate compute(std::size_t pin) override;
    };

}

#endif /* !NTS_COMPONENTS_LOGGER_HPP_ */
