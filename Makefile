
#############################################################################################
#############################################################################################
#####                                     sources                                       #####
#############################################################################################
#############################################################################################

SRC_DIR = src
SRC_FILES = game_init.c \
			game_manage.c \
			map_manage.c \
			map_check.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

#############################################################################################
#############################################################################################
#####                                   variables                                       #####
#############################################################################################
#############################################################################################

NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra -I/usr/include -Imlx -O3 -g3
LFLAGS = -Lmlx -lmlx -lXext -lX11 -Imlx
HEADERS = inc/so_long.h
INCLUDES = -I inc -I $(LIBFT_DIR)/inc -I mlx
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

#############################################################################################
#############################################################################################
#####                                   commands                                        #####
#############################################################################################
#############################################################################################

all: $(NAME)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all


.PHONY: all clean fclean re