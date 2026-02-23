/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** Matrix component implementation
*/

#include "gui/components/Matrix.hpp"
#include "nts/Errors.hpp"

namespace gui {

Matrix::Matrix(const std::string &name)
{
    _name = name;

    _pixels.fill(sf::Color::Black);

    _image.create(static_cast<unsigned>(PIXEL_SIZE),
                  static_cast<unsigned>(PIXEL_SIZE),
                  sf::Color::Black);
    _texture.loadFromImage(_image);
    _sprite.setTexture(_texture);
    _sprite.setScale(DISPLAY_SCALE, DISPLAY_SCALE);

    for (std::size_t pin = 1; pin <= 20; ++pin)
        setPin(pin, nts::Undefined);
}

void Matrix::simulate(std::size_t tick)
{
    _tick = tick;

    int shade = readBits(1, 8);
    int x     = readBits(9, 6);
    int y     = readBits(15, 6);

    if (shade < 0 || x < 0 || y < 0)
        return;

    sf::Color color = decodeColor(shade);
    _pixels[static_cast<std::size_t>(y) * PIXEL_SIZE +
            static_cast<std::size_t>(x)] = color;
    _dirty = true;
}

nts::Tristate Matrix::compute(std::size_t pin)
{
    if (pin < 1 || pin > 20)
        throw nts::NtsException("Matrix: invalid pin " + std::to_string(pin));
    return getLinkValue(pin);
}

int Matrix::readBits(std::size_t startPin, std::size_t count)
{
    int value = 0;
    for (std::size_t i = 0; i < count; ++i) {
        nts::Tristate t = getLinkValue(startPin + i);
        if (t == nts::Undefined)
            return -1;
        if (t == nts::True)
            value |= (1 << static_cast<int>(i));
    }
    return value;
}

void Matrix::updateTexture()
{
    for (int py = 0; py < PIXEL_SIZE; ++py) {
        for (int px = 0; px < PIXEL_SIZE; ++px) {
            sf::Color c = _pixels[static_cast<std::size_t>(py) * PIXEL_SIZE +
                                   static_cast<std::size_t>(px)];
            _image.setPixel(static_cast<unsigned>(px),
                            static_cast<unsigned>(py), c);
        }
    }
    _texture.loadFromImage(_image);
    _sprite.setTexture(_texture, true);
    _dirty = false;
}

sf::Color Matrix::decodeColor(int shade)
{
    int r = (shade >> 5) & 0x7;
    int g = (shade >> 2) & 0x7;
    int b =  shade       & 0x3;
    return sf::Color(
        static_cast<sf::Uint8>(r * 255 / 7),
        static_cast<sf::Uint8>(g * 255 / 7),
        static_cast<sf::Uint8>(b * 255 / 3)
    );
}

void Matrix::draw(sf::RenderWindow &window, sf::Vector2f position,
                  sf::Font &font)
{
    if (_dirty)
        updateTexture();

    sf::RectangleShape border(sf::Vector2f(DISPLAY_SIZE + 4.f, DISPLAY_SIZE + 4.f));
    border.setPosition(position.x - 2.f, position.y - 2.f);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color(100, 100, 200));
    border.setOutlineThickness(2.f);
    window.draw(border);

    _sprite.setPosition(position);
    window.draw(_sprite);

    sf::Text nameLabel;
    nameLabel.setFont(font);
    nameLabel.setCharacterSize(10);
    nameLabel.setFillColor(sf::Color(200, 200, 100));
    nameLabel.setString(_name);
    nameLabel.setPosition(position.x, position.y - 14.f);
    window.draw(nameLabel);
}

}
