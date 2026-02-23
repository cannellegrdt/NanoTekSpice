/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** SevenSeg — 4-pin input graphic component displaying a hex digit
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "nts/AComponent.hpp"

namespace gui {

/*
** 7-segment display component.
** Pins 1-4: binary inputs (pin 1 = LSB, pin 4 = MSB).
** Displays the hexadecimal digit (0-F) matching the 4-bit value.
** If any pin is Undefined, all segments are dimmed.
*/
class SevenSeg : public nts::AComponent {
public:
    static constexpr float WIDTH  = 60.f;
    static constexpr float HEIGHT = 100.f;

    explicit SevenSeg(const std::string &name);
    ~SevenSeg() override = default;

    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;

    void draw(sf::RenderWindow &window, sf::Vector2f position,
              sf::Font &font) const;

private:
    static const bool SEGMENTS[16][7];

    int getCurrentValue() const;

    void drawSegment(sf::RenderWindow &window, sf::Vector2f origin,
                     bool horizontal, float offset, bool active) const;
};

}
