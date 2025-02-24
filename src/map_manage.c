/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:08:06 by maballet          #+#    #+#             */
/*   Updated: 2025/02/24 17:54:28 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//#include <x11/keysymdef.h>

char	*floodfill(char *map, int i, int width)
{
	if (map[i] == 'V' || map[i] == '1')
		return (NULL);
	if (map[i] == 'C')
		map[i] = 'V';
	if (map[i] == 'E')
		map[i] = 'V';
	if (map[i] == '0' || map[i] == 'P')
		map[i] = 'V';
	floodfill(map, i - 1, width);
	floodfill(map, i + 1, width);
	floodfill(map, i - width, width);
	floodfill(map, i + width, width);
	return (map);
}

static char	*get_all_lines(char *map, char *line, char *tmp, int fd)
{
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
	char	*tmp;
	int		i;

	i = 0;
	fd = open (file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = NULL;
	tmp = NULL;
	line = get_next_line(fd);
	data->map.width = ft_strlen(line) - 1;
	map = get_all_lines(map, line, tmp, fd);
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
		return (NULL);
	data->map.size = ft_strlen(data->map.map) + 1;
	check = map_check(data);
	if (check == 1)
		return (NULL);
	return (data->map.map);
}
