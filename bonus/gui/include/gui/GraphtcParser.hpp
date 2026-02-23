/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** GraphtcParser — reads .graphtc section from a .nts file
*/

#pragma once

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <SFML/System/Vector2.hpp>

namespace gui {

struct LinkInfo {
    std::string compA;
    std::string compB;
};

class GraphtcParser {
public:
    static std::map<std::string, sf::Vector2f>
    parsePositions(const std::string &filepath);

    static std::vector<LinkInfo>
    parseLinks(const std::string &filepath);

    static std::string stripGraphtc(const std::string &filepath);

    static sf::Vector2f autoPosition(const std::string &category,
                                     std::size_t indexInCategory,
                                     std::size_t totalInCategory,
                                     float windowWidth,
                                     float windowHeight);
};

}
