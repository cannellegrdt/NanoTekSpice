/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** GUIShell implementation
*/

#include "gui/GUIShell.hpp"

#include <iostream>
#include "nts/components/Input.hpp"
#include "nts/AComponent.hpp"

namespace gui {

static const char *FONT_PATH =
    "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";

GUIShell::GUIShell(nts::Circuit &circuit,
                   const std::map<std::string, sf::Vector2f> &positions,
                   const std::vector<LinkInfo> &links)
    : _circuit(circuit),
      _window(sf::VideoMode(WIN_W, WIN_H), "NanoTekSpice GUI",
              sf::Style::Titlebar | sf::Style::Close),
      _renderer(circuit, positions, links, _font)
{
    _window.setFramerateLimit(60);

    if (!_font.loadFromFile(FONT_PATH)) {
        std::cerr << "[GUIShell] Warning: could not load font at "
                  << FONT_PATH << "\n";
    }
}

void GUIShell::run()
{
    _loopClock.restart();

    while (_window.isOpen()) {
        handleEvents();
        update();

        _window.clear(sf::Color(25, 25, 35));
        drawToolbar();
        render();
        _window.display();
    }
}


void GUIShell::handleEvents()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    _window.close();
                    break;
                case sf::Keyboard::Space:
                    doSimulate();
                    break;
                case sf::Keyboard::L:
                    _loopMode = !_loopMode;
                    _loopClock.restart();
                    break;
                case sf::Keyboard::D:
                    _circuit.display();
                    break;
                default:
                    break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            handleClick(sf::Vector2f(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)));
        }
    }
}

void GUIShell::handleClick(sf::Vector2f mousePos)
{
    if (mousePos.y < 50.f) {
        if (mousePos.x >= 10.f && mousePos.x <= 160.f)
            doSimulate();
        else if (mousePos.x >= 170.f && mousePos.x <= 330.f) {
            _loopMode = !_loopMode;
            _loopClock.restart();
        }
        else if (mousePos.x >= 340.f && mousePos.x <= 500.f)
            _circuit.display();
        return;
    }

    const ComponentNode *node = _renderer.nodeAt(mousePos);
    if (!node)
        return;

    bool isInput = false;
    for (const auto &n : _circuit.inputNames())
        if (n == node->name) { isInput = true; break; }

    if (isInput)
        toggleInput(node->name);
}

void GUIShell::toggleInput(const std::string &name)
{
    nts::Tristate current = nts::Undefined;
    try {
        current = _circuit.getComponent(name).compute(1);
    } catch (...) {}

    std::string next;
    if (current == nts::Undefined) next = "0";
    else if (current == nts::False) next = "1";
    else next = "U";

    try {
        _circuit.setInputValue(name, next);
    } catch (...) {}
    doSimulate();
}


void GUIShell::doSimulate()
{
    _circuit.simulate();
    _circuit.computeAllOutputs();
    _needRedraw = true;
}

void GUIShell::update()
{
    if (_loopMode) {
        float elapsed = _loopClock.getElapsedTime().asSeconds();
        if (elapsed >= 1.f / LOOP_TPS) {
            doSimulate();
            _loopClock.restart();
        }
    }
}


void GUIShell::drawToolbar()
{
    sf::RectangleShape bar(sf::Vector2f(static_cast<float>(WIN_W), 55.f));
    bar.setFillColor(sf::Color(40, 40, 55));
    _window.draw(bar);

    sf::RectangleShape sep(sf::Vector2f(static_cast<float>(WIN_W), 1.f));
    sep.setPosition(0.f, 55.f);
    sep.setFillColor(sf::Color(80, 80, 100));
    _window.draw(sep);

    auto drawButton = [&](float x, const std::string &label,
                          sf::Color fillColor) {
        sf::RectangleShape btn(sf::Vector2f(150.f, 35.f));
        btn.setPosition(x, 10.f);
        btn.setFillColor(fillColor);
        btn.setOutlineColor(sf::Color(120, 120, 160));
        btn.setOutlineThickness(1.f);
        _window.draw(btn);

        sf::Text txt;
        txt.setFont(_font);
        txt.setCharacterSize(12);
        txt.setFillColor(sf::Color::White);
        txt.setString(label);
        sf::FloatRect tb = txt.getLocalBounds();
        txt.setPosition(x + 75.f - tb.width / 2.f, 20.f);
        _window.draw(txt);
    };

    drawButton(10.f,  "[Space] Simulate", sf::Color(50, 100, 180));
    drawButton(170.f, _loopMode ? "[L] Loop: ON " : "[L] Loop: OFF",
               _loopMode ? sf::Color(40, 140, 60) : sf::Color(80, 80, 80));
    drawButton(330.f, "[D] Display", sf::Color(100, 80, 40));

    sf::Text tickTxt;
    tickTxt.setFont(_font);
    tickTxt.setCharacterSize(13);
    tickTxt.setFillColor(sf::Color(200, 200, 120));
    tickTxt.setString("Tick: " + std::to_string(_circuit.tick()));
    tickTxt.setPosition(510.f, 18.f);
    _window.draw(tickTxt);

    sf::Text hint;
    hint.setFont(_font);
    hint.setCharacterSize(10);
    hint.setFillColor(sf::Color(120, 120, 120));
    hint.setString("Click an input to toggle  |  Esc: quit");
    hint.setPosition(700.f, 22.f);
    _window.draw(hint);
}

void GUIShell::render()
{
    _renderer.draw(_window);
    _needRedraw = false;
}

}
