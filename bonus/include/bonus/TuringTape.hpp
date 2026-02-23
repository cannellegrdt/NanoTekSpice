/*
** EPITECH PROJECT, 2025
** G-OOP-400-LYN-4-1-tekspice-1
** File description:
** TuringTape
*/

#ifndef BONUS_TURINGTAPE_HPP_
#define BONUS_TURINGTAPE_HPP_

#include <map>
#include <ostream>
#include <string>

namespace nts::bonus {

class TuringTape {
public:
    explicit TuringTape(char blank = '_');

    char read()  const;
    void write(char symbol);
    void moveLeft();
    void moveRight();
    int  headPosition() const;
    void reset();
    void loadInput(const std::string &input);
    void dump(std::ostream &os) const;

private:
    std::map<int, char> _tape;
    int                 _head;
    char                _blank;
};

} // namespace nts::bonus

#endif /* !BONUS_TURINGTAPE_HPP_ */
