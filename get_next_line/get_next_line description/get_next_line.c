/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:15:23 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/26 19:46:56 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*copy_to_cache(char *cache, char *buffer)// cache ve buffer ı birleştirip cache e atıyoruz
{
	char	*res;

	res = 0;
	if (!cache && buffer)// cache boşsa ve buffer doluysa buffer a yer açıyoruz ve döndürüyoruz
		return (ft_substr(buffer, 0, ft_strlen(buffer)));
	res = ft_strjoin(cache, buffer);// cache ve buffer ı birleştiriyoruz
	if (!res)
		free_or_nl(&res, 0);
	return (free_or_nl(&cache, 0), res);// cache i free edip res i döndürüyoruz
}

static int	exist_nl(char *str)// str nin içinde \n varsa 1 yoksa 0 döndürüyoruz
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')// str nin sonuna kadar aruyoruz
	{
		if (str[i] == '\n')// \n varsa 1 döndürüyoruz
			return (1);
		i++;
	}
	return (0);
}

static char	*get_line(char *cache)// cache içindeki satırı alıyoruz
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!cache)
		return (free_or_nl(&cache, 0));
	while (cache[i] != '\n')// \n a kadar i yi arttırıyoruz ki satırın uzunluğunu bulalım
		i++;
	line = malloc(sizeof(char) * (i + 2));// \n ve \0 için +2 yapıyoruz
	if (!line)
		return (free_or_nl(&line, 0));
	j = -1;// -1 den başlama sebebim while içine girerken arttırıp ilk satırda 0 başlayıp alt satırda da 0 olması
	while (++j < i + 1)// \n dahil (+1 in olayı bu) satırı line a kopyalıyoruz
		line[j] = cache[j];
	line[j] = '\0';
	return (line);
}

static char	*trimmed_cache(char *cache)// cache de ki yazdırdığımız satırı çıkarıp kalanı yeni cache e atıyoruz
{
	size_t	i;
	char	*res;

	i = 0;
	if (!cache)
		return (NULL);
	while (cache[i] != '\n')// \n a kadar i yi arttırıyoruz ki satırın uzunluğunu bulalım
		i++;
	res = ft_substr(cache, i + 1, ft_strlen(cache));//i+1 den sonrasını yani null ı atlayıp kalanı alıyoruz
	if (!res)
		return (free_or_nl(&cache, 0), NULL);
	free_or_nl(&cache, 0);
	return (res);
}

char	*get_next_line(int fd) // fd kimlikli dosyanın içindeki satırları tek tek okuyoruz
{
	char buffer[BUFFER_SIZE + 1]; // buffer size ı 1 arttırıp sonuna null byte ekliyoruz
	long rd_bytes;// okunan bayt sayısı
	static char *cache; // okunan baytları tutmak için statik bir değişken oluşturuyoruz
	char *line; // okunan satırı tutmak için bir değişken oluşturuyoruz

	line = 0;
	rd_bytes = 1; // while döngüsüne ilk kez girmesi için 1 yapıyoruz
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (rd_bytes > 0)
	{
		rd_bytes = read(fd, buffer, BUFFER_SIZE);// dosyadan okuyoruz
		if ((rd_bytes <= 0 && !cache) || rd_bytes == -1)// (okuma başarısızsa ve cache boşsa) veya (okuma başarısızsa) null döndürüyoruz
			return (free_or_nl(&cache, 0));
		buffer[rd_bytes] = '\0';// okunan baytların sonuna null ekliyoruz
		cache = copy_to_cache(cache, buffer);
		if (exist_nl(cache))// cache içinde \n varsa satırı çıkarıyoruz
		{
			line =  get_line(cache);// cache içindeki satırı alıyoruz
			if (!line)
				return (free_or_nl(&cache, 0));
			return (cache = trimmed_cache(cache), line);// cache de ki yazdırdığımız satırı çıkarıp kalanı yeni cache e atıyoruz ve line ı döndürüyoruz
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
	int		i;
	char	*line;

	i = 1;
	fd = open("test.txt", O_RDONLY | O_CREAT, 0777);// dosyayı açıp izinlerini veriyoruz
	while ((line = get_next_line(fd)))// get next line fonksiyonundan bir şey döndüğü sürece döngü devam ediyor
	{
		printf("satır %d: %s", i++, line);// satır numarası ve satırı yazdırıyoruz
		free(line);// leak olmaması için line ı free ediyoruz
	}
		return (0);
}
 */
