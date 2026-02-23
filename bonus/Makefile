##
## EPITECH PROJECT, 2025
## G-OOP-400-LYN-4-1-tekspice-1
## File description:
## Makefile for the Turing machine bonus
##

NAME    = turing_simulator

CC      = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20 \
           -I../include \
           -I./include

BONUS_SRC = $(shell find src/ -name "*.cpp")
BONUS_OBJ = $(BONUS_SRC:.cpp=.o)

CORE_SRC  = $(shell find ../src/ -name "*.cpp" ! -name "main.cpp")
CORE_OBJ  = $(CORE_SRC:../src/%.cpp=build/%.o)

all: $(NAME)

$(NAME): $(BONUS_OBJ) $(CORE_OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

build/%.o: ../src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BONUS_OBJ)
	rm -rf build/

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
