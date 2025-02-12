/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:33:58 by maballet          #+#    #+#             */
/*   Updated: 2025/02/12 14:12:13 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	data_init(t_data *data)
{
	data->mlx_ptr = NULL;
	data->wind_ptr = NULL;
	data->map.hor_length = 0;
	data->map.ver_length = 0;
	data->map.coll_count = 0;
	data->map.exit_count = 0;
}

int	main(int argc, char **argv)
{
	t_data	*data;
	char	*map;

	map = NULL;
	if (argc != 2)
		return (1);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (2);
	data_init (data);
	map = map_manage(argv[1], data);
	if (map == NULL)
	{
		free(data);
		return (3);
	}
	if (game_manage(data, map) == 1)
	{
		free(data);
		return (4);
	}
	return (0);
}
