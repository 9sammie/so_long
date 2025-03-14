/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maballet <maballet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:31:23 by maballet          #+#    #+#             */
/*   Updated: 2025/01/13 16:31:57 by maballet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_mark(const char *s, char c, size_t *start, size_t *end);
static size_t	ft_countword(char const *s, char c);
static int		ft_free(char **array, size_t limit);

char	**ft_split(char const *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	limit;
	size_t	word;
	char	**array;

	limit = 0;
	end = 0;
	word = ft_countword(s, c);
	array = malloc(sizeof(char *) * (word + 1));
	if (!array)
		return (NULL);
	while (limit < word)
	{
		if (ft_mark(s, c, &start, &end))
			return (array);
		array[limit] = ft_substr(s, start, (end - start));
		if (ft_free(array, limit))
			return (NULL);
		limit++;
	}
	array[limit] = NULL;
	return (array);
}

static int	ft_free(char **array, size_t limit)
{
	if (!array[limit])
	{
		while (limit + 1 > 0)
		{
			free(array[limit]);
			limit--;
		}
		free(array);
		return (1);
	}
	return (0);
}

static int	ft_mark(const char *s, char c, size_t *start, size_t *end)
{
	*start = *end;
	while (s[*start] == c)
	{
		*start = *start + 1;
	}
	if (s[*start] == '\0' )
		return (1);
	*end = *start;
	while (s[*end] != c && s[*end] != '\0')
		*end = *end + 1;
	return (0);
}

static size_t	ft_countword(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (count);
		while (s[i] != c && s[i] != '\0')
			i++;
		count++;
	}
	return (count);
}
