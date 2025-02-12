/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:12:00 by maballet          #+#    #+#             */
/*   Updated: 2025/02/12 14:15:44 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	close_game(t_data *data)
{
	if (data == NULL)
		return;
	if (data->mlx_ptr && data->wind_ptr)
		mlx_destroy_window (data->mlx_ptr, data->wind_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display (data->mlx_ptr);
		free (data->mlx_ptr);
	}
	free (data);
}

static int	open_game(int height, int whide, t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	data->wind_ptr = mlx_new_window(data->mlx_ptr, height, whide, "hi :)");
	if (data->wind_ptr == NULL)
	{
		close_game(data);
		return (1);
	}
	return (0);
}

int	game_manage(t_data *data, char *map)
{
	free(map);
	if (open_game(600, 400, data) == 1)
		return (1);
	close_game(data);
	return (0);
}
