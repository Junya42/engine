NAME = sfml-app

OBJ_DIR = objs

SRCS = window.cpp \
		player.cpp \
		event.cpp \
		engine.cpp

SRCS_DIR = $(shell find srcs -type d)
SRC = $(SRCS)
vpath %.cpp $(foreach dir, $(SRCS_DIR), $(dir))
SRCS_PATH = $(addprefix srcs/, $(SRCS))

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))
OBJ_LIST = $(wildcard objs/*.o)
DEPS = $(OBJS:%.o=%.d)

CC = c++
#FLAGS = -Wall -Wextra -Werror -std=c++98
FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) ${FLAGS}
	@echo "Successfully built $(NAME)"

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@echo "Compiling $@"
	@$(CC) $(FLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@echo "Removing objects and dependencies"
	@rm -rf $(OBJS) $(DEPS) $(OBJ_DIR)

fclean: clean
	@echo "Removing executable '$(NAME)'"
	@rm -rf $(NAME)
	@rm -rf $(DNAME)

re: fclean
	$(MAKE) -C .

.PHONY: all, clean, fclean, re, $(OBJ_DIR)

-include $(DEPS)
