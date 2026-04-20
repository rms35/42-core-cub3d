# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/10 19:40:32 by almorene          #+#    #+#              #
#    Updated: 2026/04/10 19:40:34 by almorene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME        = build/cub3D
NAME_BONUS  = build/cub3D_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -flto -O3 #-MMD -fno-omit-frame-pointer
#-fsanitize=address,leak -O0 -g3
RM          = rm -rf

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	CFLAGS += -D LINUX -Wno-incompatible-pointer-types
	MLX_DIR   = minilibx-linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S),Darwin)
	CFLAGS += -D MACOS
	MLX_DIR   = minilibx_macos
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	MLX_MAKE_FLAGS = CFLAGS="-Wno-deprecated-declarations -Wno-deprecated-non-prototype -DGL_SILENCE_DEPRECATION"
else
	$(error Unsupported operating system: $(UNAME_S))
endif

SRC_DIR     = src
SRC_B_DIR   = bonus
INC_DIR     = includes
OBJ_DIR     = obj
BUILD_DIR   = build
LIBFT_DIR   = libft

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

SRCS_FILES  = main.c \
			  engine/hooks.c \
			  engine/init.c \
			  engine/input.c \
			  engine/move_player.c \
			  engine/player_dir.c \
			  engine/textures.c \
 			  engine/ray.c \
			  engine/render.c\
			  parsing/parsing.c \
			  parsing/parse_config.c \
			  parsing/parse_config1.c \
			  parsing/parse_config2.c \
			  parsing/parse_map.c \
			  parsing/error_messages.c \
			  parsing/validate_map.c \
			  parsing/map_cleanup.c

SRCS_B_FILES = main.c \
			   engine/hooks.c \
			   engine/input.c \
			   engine/input2.c \
			   engine/move_player.c \
			   engine/player_dir.c \
			   engine/ray.c \
			   engine/render.c \
			   engine/render_sprites.c \
			   engine/render_sprites2.c \
			   engine/render_door.c \
			   engine/render_door2.c \
			   engine/hud.c \
			   engine/sprites.c \
			   engine/textures.c \
			   engine/cleanup.c \
			   parsing/init.c \
			   parsing/init_player.c \
			   parsing/init_sprites.c \
			   parsing/parsing.c \
			   parsing/read_cub.c \
			   parsing/flood_fill.c \
			   parsing/parse_config.c \
			   parsing/parse_config2.c \
			   parsing/parse_config3.c \
			   parsing/parse_map.c \
			   parsing/error_messages.c \
			   parsing/validate_map.c

SRCS        = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/src/%.o)
DEPS        = $(OBJS:.o=.d)

SRCS_B      = $(addprefix $(SRC_B_DIR)/, $(SRCS_B_FILES))
OBJS_B      = $(SRCS_B:$(SRC_B_DIR)/%.c=$(OBJ_DIR)/bonus/%.o)
DEPS_B      = $(OBJS_B:.o=.d)

DEF_COLOR   = \033[0;39m
GREEN       = \033[0;92m
MAGENTA     = \033[0;95m
BLUE        = \033[0;94m
CYAN        = \033[0;96m
YELLOW      = \033[0;93m

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo -e "$(GREEN)cub3D compiled in $(BUILD_DIR)/!$(DEF_COLOR)"

$(NAME_BONUS): $(OBJS_B) $(LIBFT) $(MLX)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(OBJS_B) $(LIBFT) $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo -e "$(MAGENTA)cub3D_bonus compiled in $(BUILD_DIR)/!$(DEF_COLOR)"

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR) bonus

$(MLX):
	@$(MAKE) -s -C $(MLX_DIR) $(MLX_MAKE_FLAGS)

$(OBJ_DIR)/src/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/bonus/%.o: $(SRC_B_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@echo -e "$(BLUE)cub3D objects cleaned!$(DEF_COLOR)"

fclean: clean
	@$(RM) $(BUILD_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo -e "$(CYAN)cub3D build directory cleaned!$(DEF_COLOR)"

re: fclean all

debug: CFLAGS += -g3 -O0 -fsanitize=address
debug: re
	@echo -e "$(YELLOW)Debug build with AddressSanitizer enabled!$(DEF_COLOR)"

-include $(DEPS)
-include $(DEPS_B)

.PHONY: all bonus clean fclean re debug
