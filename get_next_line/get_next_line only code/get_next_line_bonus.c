/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:38:10 by ercdeniz          #+#    #+#             */
/*   Updated: 2023/07/26 19:48:58 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*copy_to_cache(char *cache, char *buffer)
{
	char	*res;

	res = 0;
	if (!cache && buffer)
		return (ft_substr(buffer, 0, ft_strlen(buffer)));
	res = ft_strjoin(cache, buffer);
	if (!res)
		free_or_nl(&res, 0);
	return (free_or_nl(&cache, 0), res);
}

static int	exist_nl(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_line(char *cache)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!cache)
		return (free_or_nl(&cache, 0));
	while (cache[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (free_or_nl(&line, 0));
	j = -1;
	while (++j < i + 1)
		line[j] = cache[j];
	line[j] = '\0';
	return (line);
}

static char	*trimmed_cache(char *cache)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!cache)
		return (NULL);
	while (cache[i] != '\n')
		i++;
	res = ft_substr(cache, i + 1, ft_strlen(cache));
	if (!res)
		return (free_or_nl(&cache, 0), NULL);
	free_or_nl(&cache, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	long		rd_bytes;
	static char	*cache[CACHE_SIZE];
	char		*line;

	line = 0;
	rd_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (rd_bytes > 0)
	{
		rd_bytes = read(fd, buffer, BUFFER_SIZE);
		if ((rd_bytes <= 0 && !cache[fd]) || rd_bytes == -1)
			return (free_or_nl(&cache[fd], 0));
		buffer[rd_bytes] = '\0';
		cache[fd] = copy_to_cache(cache[fd], buffer);
		if (exist_nl(cache[fd]))
		{
			line = get_line(cache[fd]);
			if (!line)
				return (free_or_nl(&cache[fd], 0));
			return (cache[fd] = trimmed_cache(cache[fd]), line);
		}
	}
	return (free_or_nl(&cache[fd], 1));
}
