CXX := c++

CXXFLAGS := -Wall -Wextra -Werror -std=c++98

CPPFLAGS := -Iinc
NAME := ft_containers
SRCS := 
VPATH = src/
OBJ_DIR := obj/
DEP_DIR := dep/
OBJS := $(SRCS:%.cpp=$(OBJ_DIR)%.o)
DEPS := $(SRCS:%.cpp=$(DEP_DIR)%.d)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d

all: $(NAME)

$(DEP_DIR): ; mkdir -p $@
$(OBJ_DIR): ; mkdir -p $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJS) -o $@

$(OBJ_DIR)%.o : %.cpp $(DEP_DIR)%.d Makefile | $(OBJ_DIR) $(DEP_DIR)
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

$(DEPS): Makefile
-include $(DEPS)

clean:
	$(RM) $(OBJS)
	$(RM) $(DEPS)

fclean: clean
	$(RM) $(NAME)

resetclean: fclean clean
	$(RM) -r $(OBJ_DIR) $(DEP_DIR)

re: fclean all

.PHONY: all clean fclean resetclean re