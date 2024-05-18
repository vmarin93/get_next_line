/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarin <vmarin@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:35:13 by vmarin            #+#    #+#             */
/*   Updated: 2024/05/15 19:59:02 by vmarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

void	resize_buffer(char **buffer, int new_size) 
{
	char	*new_buffer;
	int	i;

	new_buffer = malloc(sizeof(char) * (new_size + 1));
	if (new_buffer == NULL)
	{
		free(*buffer);
		return ;
	}
	i = 0;
	while ((*buffer)[i] != '\0')
	{
		new_buffer[i] = (*buffer)[i];
		i++;
	}
	free(*buffer);
	*buffer = new_buffer;
}

int	find_newline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	ssize_t	bytes_read;
	ssize_t	bytes_stored;
	int	i;
	int	newline_index;

	line = NULL;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	bytes_read = 1;
	bytes_stored = 0;
	while (bytes_read != 0)
	{
		if (buffer == NULL)
		{
			buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
			if (buffer == NULL)
				return (NULL);
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read == 0)
			{
				free(buffer);
				return (NULL);
			}
			buffer[bytes_read] = '\0';
		}
		else if (buffer != NULL)
		{
			resize_buffer(&buffer, bytes_stored + BUFFER_SIZE);
			bytes_read = read(fd, buffer + bytes_stored, BUFFER_SIZE);
			buffer[bytes_read + bytes_stored] = '\0';
		}
		newline_index = find_newline(buffer);
		if (newline_index != -1)
		{
			line = malloc(sizeof(char) * (newline_index + 2));
			if (line == NULL)
			{
				free(buffer);
				return (NULL);
			}
			i = 0;
			while (i <= newline_index)
			{
				line[i] = buffer[i];
				i++;
			}
			line[i] = '\0';
			return (line);
		}
		bytes_stored += bytes_read;
	}
	return (buffer);
}
