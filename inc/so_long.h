/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:20:41 by maballet          #+#    #+#             */
/*   Updated: 2025/02/11 14:47:21 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/inc/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct	s_map
{
	int		hor_length;
	int		ver_length;
	int		pos_count;
	int		coll_count;
	int		exit_count;
}				t_map;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*wind_ptr;
	void	*textures[5];
	t_map	map;
}				t_data;

#endif
