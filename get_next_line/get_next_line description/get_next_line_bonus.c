/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:46:11 by ercdeniz          #+#    #+#             */
/*   Updated: 2023/07/26 19:47:06 by ercdeniz         ###   ########.fr       */
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
		return (free_or_nl(&cache, 0));
	free_or_nl(&cache, 0);
	return (res);
}

char	*get_next_line(int fd)// fd kimlikli birden dosyanın içindeki satırları tek tek okuyoruz
//normalden farklı olarak birden fazla dosya okuyabiliyoruz
{
	char		buffer[BUFFER_SIZE + 1];
	long		rd_bytes;
	char		*line;
	static char	*cache[CACHE_SIZE];/*buradaki CACHE_SIZE kaç adet dosya okuyabileceğimizi belirliyor
	sayının önemi yok büyük bir değer olması yeterli kaç adet dosyayla çalışacaksanız ona göre ayarlayabilirsiniz
	zaten makro olarak tanımlı derleme yaparken buffer size ı verdiğiniz gibi bunuda belirtebilirsiniz*/

	line = 0;
	rd_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	/*geriye kalan kod aynı tek fark cache static değişkenime verdiğim [fd] ye göre işlem yapıyoruz*/
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
/*
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd1;
	int fd2;
	int fd3;
	char *line;

	fd1 = open("test1.txt", O_RDONLY | O_CREAT , 0777);
	fd2 = open("test2.txt", O_RDONLY | O_CREAT , 0777);
	fd3 = open("test3.txt", O_RDONLY | O_CREAT , 0777);
	int i = 1;
	while (i <= 4)
	{
		line = get_next_line(fd1);
		printf("1. fd %d. satır: %s",i, line);
		free(line);
		line = get_next_line(fd2);
		printf("2. fd %d. satır: %s",i, line);
		free(line);
		line = get_next_line(fd3);
		printf("3. fd %d. satır: %s",i++, line);
		free(line);
		printf("\n");
	}
	free(line);
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
*/
