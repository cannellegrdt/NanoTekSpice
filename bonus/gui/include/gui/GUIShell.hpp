/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** GUIShell — SFML window manager and simulation loop
*/

#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "nts/Circuit.hpp"
#include "gui/CircuitRenderer.hpp"
#include "gui/GraphtcParser.hpp"

namespace gui {

class GUIShell {
public:
    static constexpr unsigned WIN_W = 1920;
    static constexpr unsigned WIN_H = 1080;

    GUIShell(nts::Circuit &circuit,
             const std::map<std::string, sf::Vector2f> &positions,
             const std::vector<LinkInfo> &links);

    void run();

private:
    nts::Circuit      &_circuit;
    sf::RenderWindow   _window;
    sf::Font           _font;
    CircuitRenderer    _renderer;

    bool _loopMode  = false;
    bool _needRedraw = true;

    static constexpr float LOOP_TPS = 5.f;
    sf::Clock _loopClock;

    void handleEvents();
    void handleClick(sf::Vector2f mousePos);
    void update();
    void render();

    void drawToolbar();
    void doSimulate();

    void toggleInput(const std::string &name);
};

}
