# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafael <rafael@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/13 12:00:00 by rafael            #+#    #+#              #
#    Updated: 2026/02/13 12:00:00 by rafael           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = build/cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
RM          = rm -rf

# Directories
SRC_DIR     = src
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
SRCS_FILES  = main.c

SRCS        = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)cub3D compiled in $(BUILD_DIR)/!$(DEF_COLOR)"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "$(BLUE)cub3D objects cleaned!$(DEF_COLOR)"

fclean: clean
	@$(RM) $(BUILD_DIR)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(CYAN)cub3D build directory cleaned!$(DEF_COLOR)"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
