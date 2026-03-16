# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafael <rafael@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/13 12:00:00 by rafael            #+#    #+#              #
#    Updated: 2026/03/06 18:30:00 by rafael           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = build/cub3D
NAME_BONUS  = build/cub3D_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Wno-incompatible-pointer-types -g3 \
-fsanitize=address,leak -O0
RM          = rm -rf

# Directories
SRC_DIR     = src
SRC_B_DIR   = bonus
INC_DIR     = includes
OBJ_DIR     = obj
BUILD_DIR   = build
LIBFT_DIR   = libft
MLX_DIR     = minilibx-linux

# Libraries
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

# Includes
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Sources
SRCS_FILES  = main.c map_mock.c init.c hooks.c  input.c \
render.c move_player.c player_dir.c ray.c

SRCS_B_FILES = main.c map_mock.c render.c move_player.c player_dir.c \
               init.c input.c hooks.c ray.c

SRCS        = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/mandatory/%.o)

SRCS_B      = $(addprefix $(SRC_B_DIR)/, $(SRCS_B_FILES))
OBJS_B      = $(SRCS_B:$(SRC_B_DIR)/%.c=$(OBJ_DIR)/bonus/%.o)

# Colors
DEF_COLOR   = \033[0;39m
GRAY        = \033[0;90m
RED         = \033[0;91m
GREEN       = \033[0;92m
YELLOW      = \033[0;93m
BLUE        = \033[0;94m
MAGENTA     = \033[0;95m
CYAN        = \033[0;96m
WHITE       = \033[0;97m

# Rules
all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo -e "$(GREEN)cub3D compiled in $(BUILD_DIR)/!$(DEF_COLOR)"

$(NAME_BONUS): $(OBJS_B)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(OBJS_B) $(LIBFT) $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo -e "$(MAGENTA)cub3D_bonus compiled in $(BUILD_DIR)/!$(DEF_COLOR)"

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(MLX):
	@make -s -C $(MLX_DIR)

$(OBJ_DIR)/mandatory/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/mandatory
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/bonus/%.o: $(SRC_B_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/bonus
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@make -s -C $(LIBFT_DIR) clean
	@make -s -C $(MLX_DIR) clean
	@echo -e "$(BLUE)cub3D objects cleaned!$(DEF_COLOR)"

fclean: clean
	@$(RM) $(BUILD_DIR)
	@make -s -C $(LIBFT_DIR) fclean
	@echo -e "$(CYAN)cub3D build directory cleaned!$(DEF_COLOR)"

re: fclean all

# Debugging builds
debug: CFLAGS += -fsanitize=address,leak -O0
debug: re
	@echo -e "$(YELLOW)Address Sanitizer enabled!$(DEF_COLOR)"

thread: CFLAGS += -fsanitize=thread -O0
thread: re
	@echo -e "$(YELLOW)Thread Sanitizer enabled!$(DEF_COLOR)"

bonus: $(LIBFT) $(MLX) $(NAME_BONUS)

.PHONY: all clean fclean re bonus debug thread
