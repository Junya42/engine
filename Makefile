NAME = sfml-app

OBJ_DIR = objs

SRCS = main.cpp \
		player.cpp \
		event.cpp \
		engine.cpp \
		imgui.cpp \
		imgui_widgets.cpp \
		imgui_tables.cpp \
		imgui_draw.cpp \
		imgui-SFML.cpp \
		gui_objects.cpp \
		gui_settings.cpp \
		gui_save.cpp \
		gui_load.cpp

SRCS_DIR = $(shell find srcs -type d)
SRC = $(SRCS)
vpath %.cpp $(foreach dir, $(SRCS_DIR), $(dir))
SRCS_PATH = $(addprefix srcs/, $(SRCS))

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))
OBJ_LIST = $(wildcard objs/*.o)
DEPS = $(OBJS:%.o=%.d)

CC = c++
#FLAGS = -Wall -Wextra -Werror -std=c++98
FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lglut -lGLU -lGL -Iincludes/imgui

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) ${FLAGS}
	@echo "Successfully built $(NAME)"

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@echo "Compiling $@"
	@$(CC) $(FLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $@

depend:
	apt-get update -y
	apt-get upgrade -y
	apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev libsfml-dev -y

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
