/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:08:06 by maballet          #+#    #+#             */
/*   Updated: 2025/02/12 17:00:23 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_size (t_data *data, char *map)
{
	int	i;
	
	i = 0;
	while(map[i] != '\n' && map[i] != '\0')
		i++;
	data->map.hor_length = i;
	i = 0;
	while(map[i] != '\0')
	{
		if (map[i] == '\n')
			data->map.ver_length++;
		i++;
	}
	data->map.ver_length++;
}

static char	*get_all_lines(char *line, char *map, char *tmp, int fd)
{
	while(line != NULL)
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
			return (NULL);
		line = get_next_line(fd);
	}
	return(map);
}

static char	*map_cpy(char *file)
{
	int		fd;
	char	*line;
	char	*map;
	char	*tmp;
	
	fd = open (file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = NULL;
	tmp = NULL;
	line = get_next_line(fd);
	map = get_all_lines(line, map, tmp, fd);
	if (map == NULL)
	{
		close (fd);
		return (NULL);
	}
	//ft_printf("%s\n", map);
	close (fd);
	return (map);
}

char	*map_manage(char *file, t_data *data)
{
	char	*map;
	int	check;
	
	check = 0;
	map = map_cpy(file);
	if (map == NULL)
		return (NULL);
	map_size (data, map);
	check = map_check(map, data);
	if (check == 1)
		return (NULL);
	return (map);
}
