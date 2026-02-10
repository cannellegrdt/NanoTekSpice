##
## EPITECH PROJECT, 2025
## G-OOP-400-LYN-4-1-tekspice-1
## File description:
## Makefile
##

NAME	=	nanotekspice
CC	=	g++
SRC	=	$(shell find src/ -name "*.cpp")
OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++20 -I./include

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f *.gcno *.gcda
	rm -f unit_tests

fclean:	clean
	rm -f $(NAME)

re:	fclean all

unit_tests:	fclean
	$(CC) -o unit_tests $(filter-out src/main.cpp, $(SRC)) tests/unit_tests.cpp $(CXXFLAGS) -lcriterion --coverage

functional_tests:	all
	./tests/functional_tests.sh

tests_run:	unit_tests
	./unit_tests
	$(MAKE) functional_tests

coverage:	tests_run
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

.PHONY: all clean fclean re unit_tests functional_tests tests_run coverage
