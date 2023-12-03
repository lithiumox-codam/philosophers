NAME = philo
FILES = main philo utils/init utils/forks utils/print utils/atost utils/time utils/parse utils/cleanup utils/sim_helpers
SRC_DIR = src
INCLUDES = -I includes
BUILD_DIR = build
vpath %.c $(SRC_DIR)
SRCS = $(addsuffix .c, $(FILES))
OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))
CC = gcc
DEBUG = 0
DEBUG_FLAGS = -g
CFLAGS = -Wall -Wextra -Werror $(if DEBUG,$(DEBUG_FLAGS))


GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	@echo "\n$(GREEN)Compilation completed for $(NAME) 🎉 $(NC)\n"

$(BUILD_DIR)/%.o: %.c includes/philos.h
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
