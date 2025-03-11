/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:20:41 by maballet          #+#    #+#             */
/*   Updated: 2025/03/11 16:12:47 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/inc/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_texture
{
	void	*wall;
	void	*floor;
	void	*coll;
	void	*exit;
	void	*player;
}				t_texture;

typedef struct s_map
{
	int		width;
	int		height;
	int		pos_count;
	int		pos;
	int		coll_count;
	int		exit_count;
	int		size;
	char	*map;
}				t_map;

typedef struct s_img
{
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}				t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			move_count;
	void		*textures[5];
	t_map		map;
	t_img		img;
	t_texture	texture;
}				t_data;

char	*map_manage(char *file, t_data *data);
int		game_manage(t_data *data);
int		map_check(t_data *data);
char	*floodfill(char *map, int i, int width);
int		draw_tile(t_data *data, int i);
int		handle_keypress(int keycode, t_data *data);
int		close_game(t_data *data);
int		rectangular_check(t_data *data);
int		closed_check(t_data *data);
int		count_elements(char *map, t_data *data);
int		check_inspect(t_data *data);

#endif
