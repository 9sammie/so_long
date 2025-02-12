/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:12:59 by maballet          #+#    #+#             */
/*   Updated: 2025/02/12 20:52:58 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_elements(char *map, t_data *data)
{
	int	i;

	i = 0;
	data->map.map_length = (data->map.hor_length + 1) * data->map.ver_length;
	while (i < data->map.map_length)
	{
		if (map[i] != '1' && map[i] != '0' && map[i] != 'C'
			&& map[i] != 'E' && map[i] != 'P' && map[i] != '\n' 
			&& map[i] != '\0')
		{
			ft_putendl_fd("Error\nUnknown element in the map", 2);
			return (1);
		}
		if (map[i] == 'C')
			data->map.coll_count++;
		if (map[i] == 'E')
			data->map.exit_count++;
		if (map[i] == 'P')
			data->map.pos_count++;
		i++;
	}
	return (0);
}

//static int	

static int	closed_check(char *map, t_data *data)
{
	int	i;
	int	whide_length;

	i = 0;
	whide_length = data->map.hor_length;
	while (i < data->map.map_length)
	{
		if (map[i] != 1)
		{
			ft_putendl_fd("Error\nUnknown element in the map", 2);
			return (1);
		}
		if (i + whide_length == whide_length
			|| i + whide_length == whide_length *4)
		{
			while (map[i] != '\n' && map[i] != '\0')
			{
				if (map[i] != 1)
				{
					ft_putendl_fd("Error\nUnknown element in the map", 2);
					return (1);
				}
				i++;
			}
		}
		else 
		{
			while (map[i] != '\n' && map[i] != '\0')
				i++;
		}
		if (map[i - 1] != 1)
		{
			ft_putendl_fd("Error\nUnknown element in the map", 2);
			return (1);
		}
		i++;
	}
	if (map[i - 1] != 1)
			return (1);
	return (0);
}

static int	rectangular_check(char *map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.map_length)
	{
		j = 0;
		while (map[i] != '\n' && map[i] != '\0')
		{
			j++;
			i++;
		}
		if (j != data->map.hor_length)
			return (1);
		i++;
	}
	return (0);
}

int	map_check(char *map, t_data *data)
{
	int	check;

	check = 0;
	check = count_elements(map, data);
	if (check == 1)
		return (1);
	check = rectangular_check(map, data);
	if (check == 1)
		return (1);
	check = closed_check(map, data);
	if (check == 1)
		return (1);
	if (data->map.pos_count != 1 || data->map.exit_count != 1
		|| data->map.coll_count < 1 || data->map.hor_length < 3
		|| data->map.ver_length < 3)
		return (1);
	return (0);
}
