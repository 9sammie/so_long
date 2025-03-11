
#############################################################################################
#############################################################################################
#####                                     sources                                       #####
#############################################################################################
#############################################################################################

SRC_DIR = src
SRC_FILES = game_init.c \
			game_manage.c \
			map_manage.c \
			map_check.c \
			game_utils.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

#############################################################################################
#############################################################################################
#####                                   variables                                       #####
#############################################################################################
#############################################################################################

NAME			=		so_long
CC				=		cc
CFLAGS			=		-Wall -Werror -Wextra -I/usr/include -Imlx -g3
LFLAGS			=		-Lmlx -lmlx -lXext -lX11 -Imlx
HEADERS			=		inc/so_long.h
INCLUDES		=		-I inc -I $(LIBFT_DIR)/inc -I mlx

LIBFT_DIR		=		libft
LIBFT			=		$(LIBFT_DIR)/libft.a

MLX_DIR			=		mlx
MLX_LIB			=		$(MLX_DIR)/libmlx_Linux.a

OBJ_DIR			=		obj
OBJ				=		$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

#############################################################################################
#############################################################################################
#####                                   commands                                        #####
#############################################################################################
#############################################################################################

all: $(NAME)

$(NAME): lib
		$(MAKE) .compile

$(MLX_LIB):
		$(MAKE) -C $(MLX_DIR)

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) libft/inc/libft.h | $(OBJ_DIR)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.compile: $(OBJ) $(LIBFT) $(MLX_LIB)
		$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -L $(LIBFT_DIR) -lft -L $(MLX_DIR) -lmlx -o $(NAME)
		@touch .compile

lib:
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

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
