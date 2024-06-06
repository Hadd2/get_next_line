/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habernar <habernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:31:18 by habernar          #+#    #+#             */
/*   Updated: 2024/06/06 22:41:49 by habernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

long	carriage_index(t_array *array)
{
	long			idx;
	uint64_t		counter;

	if (!array || !array->buffer)
		return (-1);
	idx = 0;
	counter = array->count;
	while (counter-- && *(array->buffer + idx))
	{
		if (*(array->buffer + idx) == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

static char	*array_truncate(t_array *array)
{
	unsigned int	len;
	char			*line;
	char			*tmp;

	len = carriage_index(array) + 1;
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (0);
	ft_memcpy(line, array->buffer, len);
	*(line + len) = 0;
	array->count -= len;
	tmp = (char *)malloc(sizeof(char) * (array->capacity));
	if (!tmp)
		return (0);
	ft_memcpy(tmp, array->buffer + len, array->count);
	*(tmp + array->count) = 0;
	free(array->buffer);
	array->buffer = tmp;
	return (line);
}

static char	*handle_end_of_file(t_array *array, long bytes_read)
{
	unsigned int	len;
	char			*line;

	if (bytes_read < 0 || array->count == 0)
		return (array_delete(array));
	len = ft_strlen(array->buffer);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (array_delete(array));
	ft_memcpy(line, array->buffer, len);
	*(line + len) = 0;
	array_delete(array);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_array	array[FD_MAX];	
	long			bytes_read;
	char			*line;

	if (!array[fd].buffer)
		array_init(&array[fd]);
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (0);
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (free(line), array_delete(&array[fd]));
	while (carriage_index(&array[fd]) == -1)
	{
		bytes_read = read(fd, line, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (free(line), handle_end_of_file(&array[fd], bytes_read));
		line[bytes_read] = 0;
		array_append(&array[fd], line);
	}
	return (free(line), array_truncate(&array[fd]));
}

/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		int fd = open(argv[1], O_RDONLY);
		if (fd <= 0)
			return (-1);
		char *buffer = get_next_line(fd);
		while (buffer)
		{
			printf("%s", buffer);
			free(buffer);
			buffer = get_next_line(fd);
		}
		close(fd);
	}
	return (0);
}
*/
