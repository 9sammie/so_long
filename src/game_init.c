/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:33:58 by maballet          #+#    #+#             */
/*   Updated: 2025/02/24 15:19:21 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	data_init(t_data *data)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img_ptr = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->map.pos_count = 0;
	data->map.pos = 0;
	data->map.coll_count = 0;
	data->map.exit_count = 0;
	data->map.size = 0;
	data->map.map = NULL;
	data->img.addr = NULL;
	data->img.bpp = 0;
	data->img.line_length = 0;
	data->img.endian = 0;
	data->img.x = 0;
	data->img.y = 0;
	data->texture.wall = 0;
	data->texture.floor = 0;
	data->texture.coll = 0;
	data->texture.exit = 0;
	data->texture.player = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (1);
	data_init (&data);
	data.map.map = map_manage(argv[1], &data);
	if (data.map.map == NULL)
		return (3);
	if (game_manage(&data) == 1)
		return (4);
	return (0);
}
