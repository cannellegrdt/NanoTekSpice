/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** CircuitRenderer implementation
*/

#include "gui/CircuitRenderer.hpp"

#include <algorithm>
#include <cmath>

#include "nts/AComponent.hpp"
#include "gui/components/SevenSeg.hpp"
#include "gui/components/Matrix.hpp"

namespace gui {

CircuitRenderer::CircuitRenderer(nts::Circuit &circuit,
                                 const std::map<std::string, sf::Vector2f> &positions,
                                 const std::vector<LinkInfo> &links,
                                 sf::Font &font)
    : _circuit(circuit), _font(font), _links(links)
{
    buildNodes(positions);
}

void CircuitRenderer::buildNodes(const std::map<std::string, sf::Vector2f> &positions)
{
    std::vector<std::string> inputs, outputs, logic;
    for (const auto &[name, _] : _circuit.components()) {
        bool isInput  = false;
        bool isOutput = false;
        for (const auto &n : _circuit.inputNames())
            if (n == name) { isInput = true; break; }
        for (const auto &n : _circuit.outputNames())
            if (n == name) { isOutput = true; break; }

        if (isInput)       inputs.push_back(name);
        else if (isOutput) outputs.push_back(name);
        else               logic.push_back(name);
    }
    std::sort(inputs.begin(),  inputs.end());
    std::sort(outputs.begin(), outputs.end());
    std::sort(logic.begin(),   logic.end());

    auto makeNode = [&](const std::string &name,
                        const std::string &category,
                        std::size_t idx,
                        std::size_t total) {
        ComponentNode node;
        node.name = name;

        bool isInput  = (category == "input");
        bool isOutput = (category == "output");
        if (isInput)       node.type = "input";
        else if (isOutput) node.type = "output";
        else               node.type = "logic";

        auto &comp = _circuit.getComponent(name);
        if (dynamic_cast<SevenSeg *>(&comp)) {
            node.type = "7seg";
            node.size = sf::Vector2f(SevenSeg::WIDTH, SevenSeg::HEIGHT + 20.f);
        } else if (dynamic_cast<Matrix *>(&comp)) {
            node.type = "matrix";
            node.size = sf::Vector2f(Matrix::DISPLAY_SIZE, Matrix::DISPLAY_SIZE + 20.f);
        } else {
            node.size = sf::Vector2f(120.f, 40.f);
        }

        if (positions.count(name)) {
            node.position = positions.at(name);
        } else {
            node.position = GraphtcParser::autoPosition(
                category, idx, total, WIN_W, WIN_H);
        }

        _nodes.push_back(node);
    };

    for (std::size_t i = 0; i < inputs.size();  ++i)
        makeNode(inputs[i],  "input",  i, inputs.size());
    for (std::size_t i = 0; i < outputs.size(); ++i)
        makeNode(outputs[i], "output", i, outputs.size());
    for (std::size_t i = 0; i < logic.size();   ++i)
        makeNode(logic[i],   "logic",  i, logic.size());
}


void CircuitRenderer::draw(sf::RenderWindow &window)
{
    drawWires(window);
    for (auto &node : _nodes)
        drawNode(window, node);
}

void CircuitRenderer::drawWires(sf::RenderWindow &window)
{
    for (const auto &link : _links) {
        const ComponentNode *nodeA = nullptr;
        const ComponentNode *nodeB = nullptr;
        for (const auto &n : _nodes) {
            if (n.name == link.compA) nodeA = &n;
            if (n.name == link.compB) nodeB = &n;
        }
        if (!nodeA || !nodeB)
            continue;

        sf::Vector2f from = rightAnchor(*nodeA);
        sf::Vector2f to   = leftAnchor(*nodeB);

        nts::Tristate val = nts::Undefined;
        try {
            val = _circuit.getComponent(link.compA).compute(1);
        } catch (...) {}

        sf::Color lineColor;
        if (val == nts::True)       lineColor = sf::Color(50, 220, 50);
        else if (val == nts::False)  lineColor = sf::Color(220, 50, 50);
        else                         lineColor = sf::Color(120, 120, 120);

        sf::Vertex line[2] = {
            sf::Vertex(from, lineColor),
            sf::Vertex(to,   lineColor)
        };
        window.draw(line, 2, sf::Lines);
    }
}

void CircuitRenderer::drawNode(sf::RenderWindow &window,
                                const ComponentNode &node)
{
    auto &comp = _circuit.getComponent(node.name);

    if (node.type == "7seg") {
        if (auto *seg = dynamic_cast<SevenSeg *>(&comp))
            seg->draw(window, node.position, _font);
        return;
    }
    if (node.type == "matrix") {
        if (auto *mat = dynamic_cast<Matrix *>(&comp))
            mat->draw(window, node.position, _font);
        return;
    }

    sf::RectangleShape box(node.size);
    box.setPosition(node.position);
    box.setFillColor(typeColor(node.type));
    box.setOutlineColor(sf::Color(180, 180, 180));
    box.setOutlineThickness(1.f);
    window.draw(box);

    sf::Text nameText;
    nameText.setFont(_font);
    nameText.setCharacterSize(11);
    nameText.setFillColor(sf::Color::White);
    nameText.setString(node.name);
    sf::FloatRect tb = nameText.getLocalBounds();
    nameText.setPosition(
        node.position.x + node.size.x / 2.f - tb.width / 2.f,
        node.position.y + node.size.y / 2.f - tb.height);
    window.draw(nameText);

    if (node.type == "input" || node.type == "output") {
        nts::Tristate val = nts::Undefined;
        try { val = comp.compute(1); } catch (...) {}
        sf::Vector2f dotPos = (node.type == "input")
            ? rightAnchor(node)
            : leftAnchor(node);
        drawPinDot(window, dotPos, val);
    }
}

void CircuitRenderer::drawPinDot(sf::RenderWindow &window,
                                  sf::Vector2f pos,
                                  nts::Tristate value) const
{
    sf::CircleShape dot(5.f);
    dot.setOrigin(5.f, 5.f);
    dot.setPosition(pos);
    if (value == nts::True)         dot.setFillColor(sf::Color(50, 220, 50));
    else if (value == nts::False)   dot.setFillColor(sf::Color(220, 50, 50));
    else                            dot.setFillColor(sf::Color(150, 150, 150));
    window.draw(dot);
}


sf::Color CircuitRenderer::typeColor(const std::string &type) const
{
    if (type == "input")  return sf::Color(30, 80, 160);
    if (type == "output") return sf::Color(30, 130, 60);
    if (type == "clock")  return sf::Color(130, 60, 160);
    return sf::Color(60, 60, 80);
}

sf::Vector2f CircuitRenderer::rightAnchor(const ComponentNode &node) const
{
    return sf::Vector2f(node.position.x + node.size.x,
                        node.position.y + node.size.y / 2.f);
}

sf::Vector2f CircuitRenderer::leftAnchor(const ComponentNode &node) const
{
    return sf::Vector2f(node.position.x,
                        node.position.y + node.size.y / 2.f);
}

const ComponentNode *CircuitRenderer::nodeAt(sf::Vector2f point) const
{
    for (const auto &node : _nodes) {
        sf::FloatRect rect(node.position.x, node.position.y,
                           node.size.x, node.size.y);
        if (rect.contains(point))
            return &node;
    }
    return nullptr;
}

}
