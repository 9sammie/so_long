/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:08:06 by maballet          #+#    #+#             */
/*   Updated: 2025/03/03 16:38:54 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_inspect(t_data *data)
{
	int		check[3];

	if (data->map.map[0] == '\n')
	{
		ft_putendl_fd("Error\nMap doesn't begin at first line", 2);
		return (1);
	}
	check[0] = count_elements(data->map.map, data);
	if (check[0] == 1)
		return (1);
	check[1] = rectangular_check(data);
	if (check[1] == 1)
		return (1);
	check[2] = closed_check(data);
	if (check[2] == 1)
		return (1);
	return (0);
}

char	*floodfill(char *map, int i, int width)
{
	if (map[i] == 'V' || map[i] == '1' || map[i] == 'E')
		return (NULL);
	if (map[i] == 'C')
		map[i] = 'V';
	if (map[i] == '0' || map[i] == 'P')
		map[i] = 'V';
	floodfill(map, i - 1, width);
	floodfill(map, i + 1, width);
	floodfill(map, i - width, width);
	floodfill(map, i + width, width);
	return (map);
}

static char	*get_all_lines(char *map, char *line, int fd)
{
	char	*tmp;

	tmp = NULL;
	while (line != NULL)
	{
		tmp = map;
		if (tmp == NULL)
			map = strdup(line);
		else
			map = ft_strjoin(tmp, line);
		free (line);
		if (tmp != NULL)
			free (tmp);
		if (map == NULL)
		{
			close (fd);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	return (map);
}

static char	*map_cpy(char *file, t_data *data)
{
	int		fd;
	char	*line;
	char	*map;
	int		i;

	i = 0;
	fd = open (file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = NULL;
	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	data->map.width = ft_strlen(line) - 1;
	map = get_all_lines(map, line, fd);
	if (map == NULL)
		return (NULL);
	while (map[i++])
	{
		if (map[i] == '\n')
			data->map.height++;
	}
	data->map.height++;
	close (fd);
	return (map);
}

char	*map_manage(char *file, t_data *data)
{
	int		check;

	check = 0;
	data->map.map = map_cpy(file, data);
	if (data->map.map == NULL)
	{
		ft_putendl_fd("Error\nmissing map", 2);
		return (NULL);
	}
	data->map.size = ft_strlen(data->map.map) + 1;
	check = map_check(data);
	if (check == 1)
	{
		free(data->map.map);
		return (NULL);
	}
	return (data->map.map);
}
