/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:15:23 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/26 19:48:03 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*cache;
	char		*line;

	line = 0;
	rd_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (rd_bytes > 0)
	{
		rd_bytes = read(fd, buffer, BUFFER_SIZE);
		if ((rd_bytes <= 0 && !cache) || rd_bytes == -1)
			return (free_or_nl(&cache, 0));
		buffer[rd_bytes] = '\0';
		cache = copy_to_cache(cache, buffer);
		if (exist_nl(cache))
		{
			line = get_line(cache);
			if (!line)
				return (free_or_nl(&cache, 0));
			return (cache = trimmed_cache(cache), line);
		}
	}
	return (free_or_nl(&cache, 1));
}

/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		i;

	i = 1;
	fd = open("test.txt", O_RDONLY | O_CREAT , 0777);
	while ((line = get_next_line(fd)))
	{
		printf("satır %d: %s",i++, line);
		free(line);
	}
	return (0);
}
 */
