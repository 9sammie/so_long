/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:45:51 by maballet          #+#    #+#             */
/*   Updated: 2025/02/26 16:23:34 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	draw_tile(t_data *data, int i)
{
	void	*img;

	img = NULL;
	if (data->map.map[i] == '1')
		img = data->texture.wall;
	else if (data->map.map[i] == '0')
		img = data->texture.floor;
	else if (data->map.map[i] == 'C')
		img = data->texture.coll;
	else if (data->map.map[i] == 'P')
		img = data->texture.player;
	else if (data->map.map[i] == 'E')
		img = data->texture.exit;
	if (img != NULL)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			img, data->img.x * 100, data->img.y * 100);
	else
	{
		ft_putendl_fd ("Error\nTexture missing", 2);
		return (1);
	}
	return (0);
}

static int	update_tiles_utils(t_data *data, int dir, int *i)
{
	if (data->map.map[*i + dir] == 'C')
		data->map.coll_count--;
	if (data->map.map[*i + dir] == 'E' && data->map.coll_count != 0)
		return (0);
	if (data->map.map[*i + dir] == 'E' && data->map.coll_count == 0)
		data->map.exit_count = 0;
	data->map.map[*i] = '0';
	data->map.map[*i + dir] = 'P';
	draw_tile(data, *i);
	if (dir == -1 || dir == 1)
		data->img.x += dir;
	if (dir == -(data->map.width + 1))
		data->img.y -= 1;
	if (dir == (data->map.width + 1))
		data->img.y += 1;
	draw_tile(data, (*i + dir));
	if (data->map.exit_count == 0)
	{
		close_game(data);
		ft_putendl_fd("\n\n\n✧WOW✧⋋| ◉ ͟ʖ ◉ |⋌✧OMG✧\n\n(⚆ᗝ⚆)SUCCESS(⊙︿⊙)", 0);
		return (0);
	}
	if (data->map.exit_count != 0)
		ft_printf("move count = %d\n", data->move_count++);
	return (0);
}

static int	update_tiles(t_data *data, int dir)
{
	int	i;

	i = 0;
	data->img.x = 0;
	data->img.y = 0;
	while(data->map.map[i++])
	{
		if (data->map.map[i] == '\n')
		{
			data->img.y++;
			data->img.x = 0;
		}
		else
		{
			if (data->map.map[i] == 'P' && data->map.map[i + dir] != '1')
			{
				update_tiles_utils(data, dir, &i);
				return (0);
			}
			data->img.x++;
		}
	}
	return (0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_game(data);
	data->img.x = 0;
	data->img.y = 0;
	if (keycode == XK_Left)
		update_tiles(data, (-1));
	if (keycode == XK_Right)
		update_tiles(data, (1));
	if (keycode == XK_Up)
		update_tiles(data, -(data->map.width + 1));
	if (keycode == XK_Down)
		update_tiles(data, (data->map.width + 1));
	return (0);
}
