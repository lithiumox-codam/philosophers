NAME = philosophers
VEC_FILES = vec_apply vec_free vec_insert vec_remove vec_set vec_count vec_get vec_pop vec_replace vec_find vec_init vec_push vec_resize ft_mem ft_strcmp
FILES = main utils/init utils/vector utils/print utils/atost structs/philo utils/time debug/index utils/parse philos/index structs/mutex utils/cleanup $(VEC_FILES)
SRC_DIR = src
INCLUDES = -I includes
BUILD_DIR = build
vpath %.c $(SRC_DIR) $(SRC_DIR)/vector
SRCS = $(addsuffix .c, $(FILES))
OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
CC = gcc
DEBUG = 0
DEBUG_FLAGS = -g -fsanitize=thread
CFLAGS = -Wall -Wextra -Werror -pthread $(if DEBUG,$(DEBUG_FLAGS))


GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	@echo "\n$(GREEN)Compilation completed for $(NAME) 🎉 $(NC)\n"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW) ✅ Compiled $< $(NC)"

clean:
	@echo "$(YELLOW)⏳ Cleaning object files... $(NC)\n"
	@rm -rf $(BUILD_DIR)
	@echo "$(RED)🗑️	Removed $(BUILD_DIR) directory $(NC)\n"

fclean: clean
	@echo "$(YELLOW)⏳ Cleaning executable... $(NC)\n"
	@rm -f $(NAME)
	@echo "$(RED)🗑️	Removed $(NAME) executable $(NC)\n"

norm:
	@echo "$(YELLOW)⏳ Norminette... $(NC)\n"
	@norminette src includes

re: fclean all

.PHONY: all clean fclean re
