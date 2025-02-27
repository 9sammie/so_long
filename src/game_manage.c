/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:12:00 by maballet          #+#    #+#             */
/*   Updated: 2025/02/27 16:24:02 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	apply_texture(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.map[i])
	{
		if (data->map.map[i] == '\n')
		{
			data->img.y++;
			data->img.x = 0;
		}
		else
		{
			if (draw_tile(data, i) == 1)
				return (1);
			data->img.x++;
		}
		i++;
	}
	data->img.x = 0;
	data->img.y = 0;
	return (0);
}

static int	save_texture(t_data *data)
{
	int	width;
	int	height;

	width = 100;
	height = 100;
	data->texture.wall = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/ca_wall.xpm", &width, &height);
	data->texture.floor = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/ca_floor.xpm", &width, &height);
	data->texture.coll = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/ca_collectible.xpm", &width, &height);
	data->texture.exit = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/ca_exit.xpm", &width, &height);
	data->texture.player = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/ca_player.xpm", &width, &height);
	if (!data->texture.wall || !data->texture.floor || !data->texture.coll
		|| !data->texture.exit || !data->texture.player)
	{
		ft_putendl_fd("Error\nFailed to load texture", 2);
		return (1);
	}
	return (0);
}

int	close_game(t_data *data)
{
	if (data->mlx_ptr)
		mlx_loop_end(data->mlx_ptr);
	if (data->texture.wall)
		mlx_destroy_image(data->mlx_ptr, data->texture.wall);
	if (data->texture.floor)
		mlx_destroy_image(data->mlx_ptr, data->texture.floor);
	if (data->texture.player)
		mlx_destroy_image(data->mlx_ptr, data->texture.player);
	if (data->texture.exit)
		mlx_destroy_image(data->mlx_ptr, data->texture.exit);
	if (data->texture.coll)
		mlx_destroy_image(data->mlx_ptr, data->texture.coll);
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window (data->mlx_ptr, data->win_ptr);
	if (data->map.map)
		free(data->map.map);
	return (0);
}

static int	open_game(int width, int height, t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	if (save_texture(data) == 1)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height,
			"star night");
	if (data->win_ptr == NULL)
		return (1);
	if (apply_texture(data) == 1)
		return (1);
	mlx_hook(data->win_ptr, 17, 0, close_game, data);
	mlx_key_hook(data->win_ptr, handle_keypress, data);
	if (data->map.exit_count == 0)
		return (1);
	mlx_loop(data->mlx_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display (data->mlx_ptr);
		free (data->mlx_ptr);
	}
	return (0);
}

int	game_manage(t_data *data)
{
	if (open_game(data->map.width * 100, data->map.height * 100, data) == 1)
	{
		close_game(data);
		if (data->mlx_ptr)
		{
			mlx_destroy_display (data->mlx_ptr);
			free (data->mlx_ptr);
		}
		return (1);
	}
	return (0);
}
