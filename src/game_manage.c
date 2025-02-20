/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:12:00 by maballet          #+#    #+#             */
/*   Updated: 2025/02/20 14:07:24 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	apply_texture(t_data *data, char *map)
{
	int	x;
	int	y;
	int	i;
	void	*img;
	
	y = 0;
	i = 0;
	while(map[i])
	{
		if (map[i] == '\n')
		{
			y++;
			x = 0;
		}
		else
		{
			if (map[i] == '1')
				img = data->texture.wall;
			else if (map[i] == '0')
				img = data->texture.floor;
			else if (map[i] == 'C')
				img = data->texture.coll;
			else if (map[i] == 'P')
				img = data->texture.player;
			else if (map[i] == 'E')
				img = data->texture.exit;
			if (img)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
										img, x * 46, y * 46);
			else
			{
				ft_putendl_fd ("Error\nTexture missing", 2);
				return (1);
			}
			x++;
		}
		i++;
	}
	return (0);
}

static int	save_texture(t_data *data)
{
	int	width;
	int	height;

	width = 46;
	height = 46;

	data->texture.wall = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/wall.xpm", &width, &height);
	data->texture.floor = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/floor.xpm", &width, &height);
	data->texture.coll = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/collectible.xpm", &width, &height);
	data->texture.exit = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/exit.xpm", &width, &height);
	data->texture.player = mlx_xpm_file_to_image(data->mlx_ptr,
				"textures/player.xpm", &width, &height);
	if (!data->texture.wall || !data->texture.floor || !data->texture.coll ||
		!data->texture.exit || !data->texture.player)
	{
		ft_putendl_fd("Error\nFailed to load texture", 2);
		return(1);
	}
	return(0);
}

static void	close_game(t_data *data)
{
	if (data == NULL)
		return ;
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window (data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display (data->mlx_ptr);
		free (data->mlx_ptr);
	}
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
}

static int	open_game(int width, int height, t_data *data, char *map)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	if (save_texture(data) == 1)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "hi :)");
	if (data->win_ptr == NULL)
		return (1);
	if (apply_texture(data, map) == 1)
		return (1);
	mlx_loop(data->mlx_ptr);
	return (0);
}

int	game_manage(t_data *data, char *map)
{
	// free(map);
	if (open_game(data->map.width *46, data->map.height *46, data, map) == 1)
	{
		close_game(data);
		return (1);
	}
	close_game(data);
	return (0);
}
