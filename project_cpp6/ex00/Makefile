NAME = convert
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp ScalarConverter.cpp
OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

test: $(NAME)
	@echo "=== Testing char ==="
	./$(NAME) 'a'
	@echo ""
	./$(NAME) c
	@echo ""
	@echo "=== Testing int ==="
	./$(NAME) 0
	@echo ""
	./$(NAME) -42
	@echo ""
	./$(NAME) 42
	@echo ""
	@echo "=== Testing float ==="
	./$(NAME) 0.0f
	@echo ""
	./$(NAME) -4.2f
	@echo ""
	./$(NAME) 42.0f
	@echo ""
	@echo "=== Testing double ==="
	./$(NAME) 0.0
	@echo ""
	./$(NAME) -4.2
	@echo ""
	./$(NAME) 42.0
	@echo ""
	@echo "=== Testing pseudo-literals ==="
	./$(NAME) nan
	@echo ""
	./$(NAME) nanf
	@echo ""
	./$(NAME) +inf
	@echo ""
	./$(NAME) -inf
	@echo ""
	./$(NAME) +inff
	@echo ""
	./$(NAME) -inff
	@echo ""
	@echo "=== Testing special cases ==="
	./$(NAME) '*'
	@echo ""
	./$(NAME) 2147483647
	@echo ""
	./$(NAME) -2147483648
	@echo ""
	@echo "=== Testing invalid ==="
	./$(NAME) invalid
	@echo ""
	./$(NAME) ""

.PHONY: all clean fclean re test
