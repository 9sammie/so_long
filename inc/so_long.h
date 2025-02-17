/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:20:41 by maballet          #+#    #+#             */
/*   Updated: 2025/02/17 20:10:58 by maballet         ###   ########lyon.fr   */
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

typedef struct	s_map
{
	int		width;
	int		height;
	int		pos_count;
	int		pos;
	int		coll_count;
	int		exit_count;
	int		size;
}				t_map;

typedef struct	s_img
{
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*textures[5];
	t_map	map;
	t_img	img;
}				t_data;

char	*map_manage(char *file, t_data *data);
int		game_manage(t_data *data, char *map);
int		map_check(char *map, t_data *data);
char	*floodfill(char *map, int i, int width);

#endif
