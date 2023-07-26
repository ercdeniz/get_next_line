/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:36:53 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/26 17:09:11 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str)// str nin uzunluğunu buluyoruz
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char const *str1, char const *str2)// str1 ve str2 yi birleştirip return ediyoruz
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!str1 || !str2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (str1[++i] != '\0')
		res[i] = str1[i];
	j = 0;
	while (str2[j] != '\0')
		res[i++] = str2[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)// str nin start dan başlayıp len kadarını malloc ile yer açıp kopyalıyoruz
{
	char	*concat;
	size_t	concat_len;
	size_t	i;
	size_t	j;

	concat_len = ft_strlen(str);
	if (!str || len <= 0)
		return (NULL);
	if (len > concat_len)
		len = concat_len;
	concat = malloc(sizeof(char) * (len + 1));
	if (!concat)
		return (NULL);
	i = start;
	j = 0;
	while (i < concat_len && j < len)
		concat[j++] = str[i++];
	concat[j] = '\0';
	return (concat);

}
//parametreden (creat_line) 0 yollarsak sadece free işlemi yapar, 1 yollarsak line a cache i atıp cache i free ler ve line ı return eder
void	*free_or_nl(char **cache, int create_line)
{
	char	*line;

	if (!*cache)//cache boşsa işlem yapmadan null döndürür
		return (NULL);
	if (create_line == 0)
		return (free(*cache), *cache = NULL, NULL);//cache i free ler ve null döndürür
	else if (create_line == 1)
		return (line = ft_substr(*cache, 0, ft_strlen(*cache)), free(*cache),//cache i line a atar ve cache i free ler
			*cache = NULL, line);
	return (NULL);
}
