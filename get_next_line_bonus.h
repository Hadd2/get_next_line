/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:31:07 by habernar          #+#    #+#             */
/*   Updated: 2024/06/14 16:56:52 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

typedef struct s_array
{
	uint64_t	count;
	uint64_t	capacity;
	char		*buffer;
}	t_array;

char		*get_next_line(int fd);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		array_init(t_array *array);
void		array_append(t_array *array, char *line);
void		*array_delete(t_array *array);
uint64_t	ft_strlen(char *str);

#endif
