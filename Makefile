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
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR)
LDFLAGS		= -L$(LIBFT_DIR) -lft -lreadline -L$(MLX_DIR) -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm

# Sources
SRCS		= $(SRC_DIR)/main.c \
              $(SRC_UTILS_DIR)/gc.c \
              $(SRC_PARSING_DIR)/map_file.c \
              $(SRC_PARSING_DIR)/textures.c \
              $(SRC_PARSING_DIR)/colors.c \
              $(SRC_PARSING_DIR)/error.c \
              $(SRC_PARSING_DIR)/map_parser.c \
              $(SRC_PARSING_DIR)/raycasting.c \
              $(SRC_PARSING_DIR)/events.c \
              $(SRC_PARSING_DIR)/map_validation.c \
              $(SRC_PARSING_DIR)/utils.c

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
	@rm -rf $(OBJ_DIR)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		echo "Cleaning Libft library..."; \
		$(MAKE) -C $(LIBFT_DIR) clean; \
	else \
		echo "Libft directory not found, skipping..."; \
	fi
	@if [ -d "$(MLX_DIR)" ]; then \
		if [ -f "$(MLX_DIR)/Makefile" ]; then \
			echo "Cleaning MinilibX library..."; \
			$(MAKE) -C $(MLX_DIR) clean || echo "MinilibX clean failed, continuing..."; \
		else \
			echo "MinilibX Makefile not found, skipping clean..."; \
		fi; \
	else \
		echo "MinilibX directory not found, skipping..."; \
	fi
	@echo "Clean completed!"

fclean: clean
	@echo "Removing $(NAME) binary..."
	@rm -f $(NAME)
	@if [ -d "test_files" ]; then \
		echo "Removing test_files/ directory..."; \
		rm -rf test_files; \
	fi
	@if [ -d "$(LIBFT_DIR)" ]; then \
		echo "Removing Libft directory..."; \
		rm -rf $(LIBFT_DIR); \
	fi
	@if [ -d "$(MLX_DIR)" ]; then \
		echo "Removing MinilibX directory..."; \
		rm -rf $(MLX_DIR); \
	fi
	@echo "Full clean completed!"

re: fclean all

# **************************************************************************** #
#                                   PHONY                                      #
# **************************************************************************** #
.PHONY: all clean fclean re valgrind debug