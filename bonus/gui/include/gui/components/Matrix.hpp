/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Matrix — 20-pin graphic component displaying a 64x64 pixel image
*/

#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "nts/AComponent.hpp"

namespace gui {

/*
** Matrix graphic component.
**
** Pins 1-8  : color shade (8 bits, R3G3B2 encoding).
** Pins 9-14 : X coordinate (6 bits, LSB first → 0-63).
** Pins 15-20: Y coordinate (6 bits, LSB first → 0-63).
**
** On each simulate() call, if all pins are defined, the pixel at (x, y)
** is set to the color encoded by pins 1-8.
**
** Displayed as a 256x256 scaled texture (4× zoom).
*/
class Matrix : public nts::AComponent {
public:
    static constexpr int   PIXEL_SIZE = 64;
    static constexpr float DISPLAY_SCALE = 4.f;
    static constexpr float DISPLAY_SIZE  = PIXEL_SIZE * DISPLAY_SCALE;

    explicit Matrix(const std::string &name);
    ~Matrix() override = default;

    void simulate(std::size_t tick) override;
    nts::Tristate compute(std::size_t pin) override;

    void draw(sf::RenderWindow &window, sf::Vector2f position,
              sf::Font &font);

private:
    std::array<sf::Color, PIXEL_SIZE * PIXEL_SIZE> _pixels;
    sf::Image   _image;
    sf::Texture _texture;
    sf::Sprite  _sprite;
    bool        _dirty = false;

    int readBits(std::size_t startPin, std::size_t count);

    void updateTexture();

    static sf::Color decodeColor(int shade);
};

}
