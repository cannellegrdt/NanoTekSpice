/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Logger component implementation
*/

#include "nts/components/Logger.hpp"
#include "nts/Errors.hpp"

namespace nts {

    Logger::Logger(const std::string &name)
        : _lastClock(Tristate::Undefined)
    {
        _name = name;
        _fileStream.open("./log.bin", std::ios::binary | std::ios::trunc);
        if (!_fileStream.is_open()) throw NtsException("Logger: cannot open log file './log.bin'");
    }

    void Logger::simulate(std::size_t tick)
    {
        _tick = tick;

        Tristate clock = getLinkValue(9);
        Tristate inhibit = getLinkValue(10);

        if (_lastClock == False && clock == True && inhibit != True) {
            unsigned char byte = 0;
            for (std::size_t i = 0; i < 8; i++) {
                if (getLinkValue(i + 1) == True)
                    byte |= static_cast<unsigned char>(1 << i);
            }
            _fileStream.write(reinterpret_cast<const char *>(&byte), 1);
            _fileStream.flush();
        }
        _lastClock = clock;
    }

    Tristate Logger::compute(std::size_t pin)
    {
        if (pin < 1 || pin > 10)
            throw NtsException("Logger: invalid pin " + std::to_string(pin));
        return getLinkValue(pin);
    }

}
