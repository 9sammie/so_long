/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:33:58 by maballet          #+#    #+#             */
/*   Updated: 2025/02/11 17:49:44 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	map_size (t_data *data, char *map)
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

char	*map_cpy(char *file)
{
	int		fd;
	char	*line;
	char	*map;
	char	*tmp;
	
	fd = open (file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = NULL;
	line = get_next_line(fd);
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
		{
			close (fd);
			return (NULL);
		}
		line = get_next_line(fd);
	}
	//ft_printf("%s\n", map);
	close (fd);
	return (map);
}

char	*map_manage(char *file, t_data *data)
{
	char	*map;
	
	map = map_cpy(file);
	if (map == NULL)
		return (NULL);
	map_size (data, map);
	//ft_printf("largeur : %d, hauteur : %d\n", data->map.hor_length, data->map.ver_length);
	return (map);
}

void	close_game(t_data *data)
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

int	open_game(int height, int whide, t_data *data)
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
