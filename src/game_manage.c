/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:12:00 by maballet          #+#    #+#             */
/*   Updated: 2025/02/17 20:13:55 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	free (data);
}

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bpp / 8));
	*(unsigned int*)dst = color;
}

static int	open_game(int width, int height, t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	data->img_ptr = mlx_new_image(data->mlx_ptr, width, height);
	data->img.addr = mlx_get_data_addr(data->img_ptr, &data->img.bpp, &data->img.line_length, &data->img.endian);
	ft_printf("ok\n");
	my_mlx_pixel_put(data, 5, 5, 0x00FF0000);
	ft_printf("ok\n");
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	ft_printf("ok\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "hi :)");
	if (data->win_ptr == NULL)
	{
		close_game(data);
		return (1);
	}
	mlx_loop(data->mlx_ptr);
	return (0);
}

int	game_manage(t_data *data, char *map)
{
	free(map);
	if (open_game(data->map.width *200, data->map.height *200, data) == 1)
		return (1);
	close_game(data);
	return (0);
}
