/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** SevenSeg component implementation
*/

#include "gui/components/SevenSeg.hpp"
#include "nts/Errors.hpp"

namespace gui {

//  Segment layout:
//    aaa
//   f   b
//   f   b
//    ggg
//   e   c
//   e   c
//    ddd
//
// Array index: [digit][segment] with segments a=0,b=1,c=2,d=3,e=4,f=5,g=6
const bool SevenSeg::SEGMENTS[16][7] = {
//   a      b      c      d      e      f      g
    {true,  true,  true,  true,  true,  true,  false}, // 0
    {false, true,  true,  false, false, false, false}, // 1
    {true,  true,  false, true,  true,  false, true }, // 2
    {true,  true,  true,  true,  false, false, true }, // 3
    {false, true,  true,  false, false, true,  true }, // 4
    {true,  false, true,  true,  false, true,  true }, // 5
    {true,  false, true,  true,  true,  true,  true }, // 6
    {true,  true,  true,  false, false, false, false}, // 7
    {true,  true,  true,  true,  true,  true,  true }, // 8
    {true,  true,  true,  true,  false, true,  true }, // 9
    {true,  true,  true,  false, true,  true,  true }, // A
    {false, false, true,  true,  true,  true,  true }, // b
    {true,  false, false, true,  true,  true,  false}, // C
    {false, true,  true,  true,  true,  false, true }, // d
    {true,  false, false, true,  true,  true,  true }, // E
    {true,  false, false, false, true,  true,  true }, // F
};

SevenSeg::SevenSeg(const std::string &name)
{
    _name = name;
    for (std::size_t pin = 1; pin <= 4; ++pin)
        setPin(pin, nts::Undefined);
}

void SevenSeg::simulate(std::size_t tick)
{
    _tick = tick;
}

nts::Tristate SevenSeg::compute(std::size_t pin)
{
    if (pin < 1 || pin > 4)
        throw nts::NtsException("SevenSeg: invalid pin " + std::to_string(pin));
    return getLinkValue(pin);
}

int SevenSeg::getCurrentValue() const
{
    int value = 0;
    for (int bit = 0; bit < 4; ++bit) {
        nts::Tristate t = const_cast<SevenSeg *>(this)->getLinkValue(
            static_cast<std::size_t>(bit + 1));
        if (t == nts::True)
            value |= (1 << bit);
    }
    return value;
}

// Draw one segment bar.
// horizontal == true  → horizontal bar (a, d, g)
// horizontal == false → vertical bar   (b, c, e, f)
// offset: position along the component box
void SevenSeg::drawSegment(sf::RenderWindow &window,
                            sf::Vector2f origin,
                            bool horizontal,
                            float offset,
                            bool active) const
{
    const float thick  = 6.f;
    const float segLen = WIDTH - 2.f * thick;
    sf::Color on(220, 50, 50);
    sf::Color off(40, 10, 10);

    sf::RectangleShape seg;
    if (horizontal) {
        seg.setSize(sf::Vector2f(segLen, thick));
        seg.setPosition(origin.x + thick, origin.y + offset);
    } else {
        seg.setSize(sf::Vector2f(thick, segLen / 2.f - thick / 2.f));
        seg.setPosition(origin.x + offset, origin.y + thick + (offset > WIDTH / 2.f ? HEIGHT / 2.f : 0.f));
    }
    seg.setFillColor(active ? on : off);
    window.draw(seg);
}

void SevenSeg::draw(sf::RenderWindow &window,
                    sf::Vector2f position,
                    sf::Font &font) const
{
    const float thick  = 6.f;
    const float segW   = WIDTH  - 2.f * thick;
    const float halfH  = HEIGHT / 2.f;

    sf::Color on(220, 50, 50);
    sf::Color off(40, 10, 10);

    int value = getCurrentValue();
    const bool *segs = (value >= 0) ? SEGMENTS[value] : nullptr;

    auto segColor = [&](int idx) -> sf::Color {
        if (!segs) return off;
        return segs[idx] ? on : off;
    };

    sf::RectangleShape bg(sf::Vector2f(WIDTH, HEIGHT));
    bg.setPosition(position);
    bg.setFillColor(sf::Color(10, 10, 10));
    bg.setOutlineColor(sf::Color(80, 80, 80));
    bg.setOutlineThickness(1.f);
    window.draw(bg);

    // --- Horizontal segments ---
    // a: top
    sf::RectangleShape ha(sf::Vector2f(segW, thick));
    ha.setPosition(position.x + thick, position.y);
    ha.setFillColor(segColor(0));
    window.draw(ha);

    // g: middle
    sf::RectangleShape hg(sf::Vector2f(segW, thick));
    hg.setPosition(position.x + thick, position.y + halfH - thick / 2.f);
    hg.setFillColor(segColor(6));
    window.draw(hg);

    // d: bottom
    sf::RectangleShape hd(sf::Vector2f(segW, thick));
    hd.setPosition(position.x + thick, position.y + HEIGHT - thick);
    hd.setFillColor(segColor(3));
    window.draw(hd);

    // --- Vertical segments ---
    float vLen = halfH - thick * 1.5f;

    // f: top-left
    sf::RectangleShape vf(sf::Vector2f(thick, vLen));
    vf.setPosition(position.x, position.y + thick);
    vf.setFillColor(segColor(5));
    window.draw(vf);

    // b: top-right
    sf::RectangleShape vb(sf::Vector2f(thick, vLen));
    vb.setPosition(position.x + WIDTH - thick, position.y + thick);
    vb.setFillColor(segColor(1));
    window.draw(vb);

    // e: bottom-left
    sf::RectangleShape ve(sf::Vector2f(thick, vLen));
    ve.setPosition(position.x, position.y + halfH + thick / 2.f);
    ve.setFillColor(segColor(4));
    window.draw(ve);

    // c: bottom-right
    sf::RectangleShape vc(sf::Vector2f(thick, vLen));
    vc.setPosition(position.x + WIDTH - thick, position.y + halfH + thick / 2.f);
    vc.setFillColor(segColor(2));
    window.draw(vc);

    sf::Text label;
    label.setFont(font);
    label.setCharacterSize(11);
    label.setFillColor(sf::Color(180, 180, 180));
    if (value >= 0) {
        const char hex[] = "0123456789ABCDEF";
        label.setString(std::string(1, hex[value]));
    } else {
        label.setString("U");
    }
    label.setPosition(position.x + WIDTH / 2.f - 4.f,
                      position.y + HEIGHT + 2.f);
    window.draw(label);

    sf::Text nameLabel;
    nameLabel.setFont(font);
    nameLabel.setCharacterSize(10);
    nameLabel.setFillColor(sf::Color(200, 200, 100));
    nameLabel.setString(_name);
    nameLabel.setPosition(position.x, position.y - 14.f);
    window.draw(nameLabel);
}

}
