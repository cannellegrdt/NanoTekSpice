/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** GraphtcParser implementation
*/

#include "gui/GraphtcParser.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>

namespace gui {

static bool isSectionLine(const std::string &line)
{
    auto trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    return trimmed.rfind(".chipsets", 0) == 0 ||
           trimmed.rfind(".links", 0) == 0 ||
           trimmed.rfind(".graphtc", 0) == 0;
}

static std::string trimLine(const std::string &line)
{
    auto pos = line.find('#');
    std::string s = (pos != std::string::npos) ? line.substr(0, pos) : line;
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r'))
        s.pop_back();
    return s;
}

std::map<std::string, sf::Vector2f>
GraphtcParser::parsePositions(const std::string &filepath)
{
    std::map<std::string, sf::Vector2f> positions;
    std::ifstream file(filepath);
    if (!file.is_open())
        return positions;

    bool inGraphtc = false;
    std::string line;
    while (std::getline(file, line)) {
        std::string clean = trimLine(line);
        if (clean.empty())
            continue;

        if (clean.rfind(".graphtc", 0) == 0) {
            inGraphtc = true;
            continue;
        }
        if (isSectionLine(clean) && clean.rfind(".graphtc", 0) != 0) {
            inGraphtc = false;
            continue;
        }

        if (!inGraphtc)
            continue;

        std::istringstream ss(clean);
        std::string name;
        float x, y;
        if (ss >> name >> x >> y)
            positions[name] = sf::Vector2f(x, y);
    }
    return positions;
}

std::vector<LinkInfo>
GraphtcParser::parseLinks(const std::string &filepath)
{
    std::vector<LinkInfo> links;
    std::ifstream file(filepath);
    if (!file.is_open())
        return links;

    bool inLinks = false;
    std::string line;
    while (std::getline(file, line)) {
        std::string clean = trimLine(line);
        if (clean.empty())
            continue;

        if (clean.rfind(".links", 0) == 0) {
            inLinks = true;
            continue;
        }
        if (isSectionLine(clean) && clean.rfind(".links", 0) != 0) {
            inLinks = false;
            continue;
        }

        if (!inLinks)
            continue;

        std::istringstream ss(clean);
        std::string tokenA, tokenB;
        if (!(ss >> tokenA >> tokenB))
            continue;

        auto extractName = [](const std::string &token) {
            auto colon = token.find(':');
            return (colon != std::string::npos) ? token.substr(0, colon) : token;
        };

        LinkInfo info;
        info.compA = extractName(tokenA);
        info.compB = extractName(tokenB);

        bool found = false;
        for (const auto &existing : links) {
            if ((existing.compA == info.compA && existing.compB == info.compB) ||
                (existing.compA == info.compB && existing.compB == info.compA)) {
                found = true;
                break;
            }
        }
        if (!found)
            links.push_back(info);
    }
    return links;
}

std::string GraphtcParser::stripGraphtc(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
        return "";

    std::ostringstream result;
    bool inGraphtc = false;
    std::string line;
    while (std::getline(file, line)) {
        std::string clean = trimLine(line);

        if (clean.rfind(".graphtc", 0) == 0) {
            inGraphtc = true;
            continue;
        }
        if (inGraphtc && isSectionLine(clean) && clean.rfind(".graphtc", 0) != 0) {
            inGraphtc = false;
        }
        if (!inGraphtc)
            result << line << '\n';
    }
    return result.str();
}

sf::Vector2f GraphtcParser::autoPosition(const std::string &category,
                                         std::size_t indexInCategory,
                                         std::size_t totalInCategory,
                                         float windowWidth,
                                         float windowHeight)
{
    const float margin = 80.f;
    const float topOffset = 80.f;
    float x = 0.f;
    float y = 0.f;

    float usableHeight = windowHeight - topOffset - margin;
    float step = (totalInCategory > 1)
        ? usableHeight / static_cast<float>(totalInCategory - 1)
        : usableHeight / 2.f;
    float posY = topOffset + margin / 2.f +
                 static_cast<float>(indexInCategory) * step;

    if (category == "input" || category == "clock") {
        x = margin;
        y = posY;
    } else if (category == "output") {
        x = windowWidth - margin - 120.f;
        y = posY;
    } else {
        x = windowWidth / 2.f - 60.f +
            static_cast<float>(indexInCategory % 3) * 200.f -
            static_cast<float>((totalInCategory < 3 ? totalInCategory : 3) / 2) * 200.f;
        y = topOffset + margin / 2.f +
            static_cast<float>(indexInCategory / 3) * 180.f;
    }

    return sf::Vector2f(x, y);
}

}
