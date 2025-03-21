/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:12:59 by maballet          #+#    #+#             */
/*   Updated: 2025/03/11 15:58:35 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_elements(char *map, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.size)
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
		{
			data->map.pos = i;
			data->map.pos_count++;
		}
		i++;
	}
	return (0);
}

static int	closed_side(t_data *data, int *i)
{
	while (data->map.map[*i] && *i < data->map.size - data->map.width)
	{
		if (data->map.map[*i] != '\n')
			(*i)++;
		else
		{
			if (data->map.map[*i + 1] != '1' || data->map.map[*i - 1] != '1')
			{
				ft_putendl_fd("Error\nMap not closed", 2);
				return (1);
			}
			(*i)++;
		}
	}
	return (0);
}

int	closed_check(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.map[i] != '\n' && data->map.map[i] != '\0')
	{
		if (data->map.map[i] != '1')
		{
			ft_putendl_fd("Error\nMap not closed", 2);
			return (1);
		}
		i++;
	}
	if ((closed_side(data, &i)) == 1)
		return (1);
	while (data->map.map[i] != '\0')
	{
		if (data->map.map[i] != '1')
		{
			ft_putendl_fd("Error\nMap not closed", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	rectangular_check(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.size)
	{
		j = 0;
		while (data->map.map[i] != '\n' && data->map.map[i] != '\0')
		{
			j++;
			i++;
		}
		if (j != data->map.width)
		{
			ft_putendl_fd("Error\nMap is not rectangular", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	map_check(t_data *data)
{
	int		check;
	char	*flofi;

	check = 0;
	check = check_inspect(data);
	if (check == 1)
		return (1);
	if (data->map.pos_count != 1 || data->map.exit_count != 1
		|| data->map.coll_count < 1 || data->map.width < 3
		|| data->map.height < 3)
	{
		ft_putendl_fd("Error\nMap too small or wrong element count", 2);
		return (1);
	}
	flofi = floodfill(ft_strdup(data->map.map), data->map.pos,
			(data->map.width + 1));
	if (ft_strchr(flofi, 'C') || ft_strchr(flofi, 'P') || ft_strchr(flofi, 'E'))
	{
		ft_putendl_fd("Error\nMap not solvable", 2);
		free(flofi);
		return (1);
	}
	free(flofi);
	return (0);
}
