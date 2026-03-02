##
## EPITECH PROJECT, 2025
## G-OOP-400-LYN-4-1-tekspice-1
## File description:
## Makefile
##

CC          =   clang++
CXXFLAGS    =   -Wall -Wextra -Werror -Wunused-private-field -std=c++20
COMMON_INC  =   -I./include

NAME        =   nanotekspice
TURING_NAME =   turing_machine
GUI_NAME    =   gui_nts

SRC         =   $(shell find src/ -name "*.cpp")
OBJ         =   $(SRC:.cpp=.o)

CORE_SRC    =   $(filter-out src/main.cpp, $(SRC))
CORE_OBJ    =   $(CORE_SRC:src/%.cpp=build/core/%.o)

TURING_SRC  =   $(shell find bonus/src/ -name "*.cpp")
TURING_OBJ  =   $(TURING_SRC:bonus/src/%.cpp=build/turing/%.o)
TURING_INC  =   -I./bonus/include

GUI_SRC     =   $(shell find bonus/gui/src/ -name "*.cpp")
GUI_OBJ     =   $(GUI_SRC:bonus/gui/src/%.cpp=build/gui/%.o)
GUI_INC     =   -I./bonus/gui/include
GUI_LIBS    =   -lsfml-graphics -lsfml-window -lsfml-system


all:	$(NAME)
$(NAME):	$(OBJ)
	$(CC) $(CXXFLAGS) -o $(NAME) $(OBJ) $(COMMON_INC)


turing:	$(TURING_NAME)
$(TURING_NAME):	$(CORE_OBJ) $(TURING_OBJ)
	$(CC) $(CXXFLAGS) -o $(TURING_NAME) $^ $(COMMON_INC) $(TURING_INC)


gui:	$(GUI_NAME)
$(GUI_NAME):	$(CORE_OBJ) $(GUI_OBJ)
	$(CC) $(CXXFLAGS) -o $(GUI_NAME) $^ $(GUI_LIBS) $(COMMON_INC) $(GUI_INC)


src/%.o:	src/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ $(COMMON_INC)

build/core/%.o:	src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@ $(COMMON_INC)

build/turing/%.o:	bonus/src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@ $(COMMON_INC) $(TURING_INC)

build/gui/%.o:	bonus/gui/src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@ $(COMMON_INC) $(GUI_INC)

bonus:	turing gui

unit_tests:	fclean
	$(CC) -o unit_tests $(CORE_SRC) tests/unit_tests.cpp $(CXXFLAGS) $(COMMON_INC) -lcriterion --coverage
	./unit_tests

functional_tests:	all
	./tests/functional_tests.sh

tests_run:	unit_tests
	$(MAKE) functional_tests

coverage:	unit_tests
	gcovr --gcov-executable "llvm-cov gcov" --exclude tests/

lint:
	cppcheck --enable=warning,performance,portability --error-exitcode=1 -I include/ src/

memcheck:	unit_tests
	valgrind --leak-check=full --soname-synonyms=somalloc=none ./unit_tests

clean:
	rm -f $(OBJ)
	rm -rf build/
	rm -f *.gcno *.gcda unit_tests

fclean: clean
	rm -f $(NAME)
	rm -f $(TURING_NAME)
	rm -f $(GUI_NAME)

re: fclean all

.PHONY: all clean fclean re bonus turing gui unit_tests tests_run coverage lint memcheck functional_tests
