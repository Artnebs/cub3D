# **************************************************************************** #
#                                   VARIABLES                                  #
# **************************************************************************** #

# Program Name
NAME		= cub3D

# Directories
SRC_DIR		= srcs
SRC_UTILS_DIR	= $(SRC_DIR)/utils
SRC_PARSING_DIR = $(SRC_DIR)/parsing
INC_DIR		= includes
LIBFT_DIR	= Libft_GNL_Printf
MLX_DIR		= minilibx-linux
OBJ_DIR		= obj

# Libraries Setup
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_REPO	= https://github.com/Artnebs/Libft_GNL_Printf.git
MLX			= $(MLX_DIR)/libmlx.a
MLX_REPO	= https://github.com/42Paris/minilibx-linux.git

# Compiler and Flags
CC		= gcc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)
LDFLAGS		= -L$(LIBFT_DIR) -lft -lreadline -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Sources
SRCS		= $(SRC_DIR)/main.c \
              $(SRC_UTILS_DIR)/gc.c \
              $(SRC_PARSING_DIR)/map_file.c \
              $(SRC_PARSING_DIR)/textures.c \
              $(SRC_PARSING_DIR)/colors.c


OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

# Default Rule: build the program (release mode)
all: $(LIBFT) $(MLX) $(NAME)

# Main linking: link the objects with your Libft library
$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "Build complete!"

# Compile .c into .o in obj/ preserving subdirectory structure
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build Libft if not present
$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning Libft repository..."; \
		git clone $(LIBFT_REPO) $(LIBFT_DIR); \
	fi; \
	if [ -d "$(LIBFT_DIR)" ]; then \
		echo "Building Libft library..."; \
		$(MAKE) -C $(LIBFT_DIR); \
	else \
		echo "Error: Failed to clone Libft repository"; \
		exit 1; \
	fi

# Build MinilibX if not present
$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MinilibX repository..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi; \
	if [ -d "$(MLX_DIR)" ]; then \
		echo "Building MinilibX library..."; \
		$(MAKE) -C $(MLX_DIR); \
	else \
		echo "Error: Failed to clone MinilibX repository"; \
		exit 1; \
	fi

# ----------------------------------------------------------------------------- #
# Debug and Valgrind Targets
# ----------------------------------------------------------------------------- #

# Valgrind: build the program then run it with full leak checking
valgrind: all
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

# Debug: add debugging flags (-g -DDEBUG) and rebuild everything.
# In your C code, wrap any extra debug prints with:
#    #ifdef DEBUG
#       printf("Debug: variable x = %d\n", x);
#    #endif
# To use debug mode, run: make debug
debug: CFLAGS += -g -DDEBUG
debug: re

# ---------------------------------------------------------------------------- #
# Cleaning Rules
# ---------------------------------------------------------------------------- #

clean:
	@echo "Cleaning object files in $(OBJ_DIR)/..."
	rm -rf $(OBJ_DIR)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		$(MAKE) -C $(LIBFT_DIR) clean; \
	fi
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean: clean
	@echo "Removing $(NAME) binary..."
	rm -f $(NAME)
	@if [ -d "test_files" ]; then \
		echo "Removing test_files/ directory..."; \
		rm -rf test_files; \
	fi
	@echo "Removing Libft directory (optional)..."
	rm -rf $(LIBFT_DIR)
	@echo "Removing MinilibX directory (optional)..."
	rm -rf $(MLX_DIR)

re: fclean all

# **************************************************************************** #
#                                   PHONY                                      #
# **************************************************************************** #
.PHONY: all clean fclean re valgrind debug