/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:18:54 by ercdeniz          #+#    #+#             */
/*   Updated: 2023/07/26 17:09:52 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 
# endif

char	*get_next_line(int fd);
char	*ft_strjoin(char const *str1, char const *str2);
char	*ft_substr(char const *str, unsigned int start, size_t len);
void	*free_or_nl(char **cache, int create_line);
size_t	ft_strlen(const char *str);

#endif
