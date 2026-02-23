/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** CircuitRenderer — draws the circuit graph in the SFML window
*/

#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "nts/Circuit.hpp"
#include "nts/Tristate.hpp"
#include "gui/GraphtcParser.hpp"

namespace gui {

struct ComponentNode {
    std::string      name;
    std::string      type;
    sf::Vector2f     position;
    sf::Vector2f     size;
};

class CircuitRenderer {
public:
    static constexpr float WIN_W = 1200.f;
    static constexpr float WIN_H =  800.f;

    CircuitRenderer(nts::Circuit &circuit,
                    const std::map<std::string, sf::Vector2f> &positions,
                    const std::vector<LinkInfo> &links,
                    sf::Font &font);

    void draw(sf::RenderWindow &window);

    const ComponentNode *nodeAt(sf::Vector2f point) const;

    const std::vector<ComponentNode> &nodes() const { return _nodes; }

private:
    nts::Circuit              &_circuit;
    sf::Font                  &_font;
    std::vector<ComponentNode>  _nodes;
    std::vector<LinkInfo>       _links;

    void buildNodes(const std::map<std::string, sf::Vector2f> &positions);

    void drawNode(sf::RenderWindow &window, const ComponentNode &node);
    void drawWires(sf::RenderWindow &window);
    void drawPinDot(sf::RenderWindow &window, sf::Vector2f pos,
                    nts::Tristate value) const;

    sf::Color typeColor(const std::string &type) const;
    static nts::Tristate getOutputValue(nts::IComponent &comp);

    sf::Vector2f rightAnchor(const ComponentNode &node) const;
    sf::Vector2f leftAnchor(const ComponentNode &node) const;
};

}
