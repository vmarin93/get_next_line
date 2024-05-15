/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarin <vmarin@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:35:13 by vmarin            #+#    #+#             */
/*   Updated: 2024/05/13 18:01:37 by vmarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char	*save_from_buffer(char *buffer, ssize_t chars_read)
{
	static char	*saved_from_buffer = NULL;
	char	*temp;
	char	*line;
	int	i;
	int	j;

	if (saved_from_buffer == NULL)
	{
		saved_from_buffer = malloc(sizeof(char) * (chars_read + 1));
		if (saved_from_buffer == NULL)
			return (NULL);
		i = 0;
		while (buffer[i] != '\0')
		{
			saved_from_buffer[i] = buffer[i];
			i++;
		}
		saved_from_buffer[i] = '\0';
	}
	else
	{
		i = 0;
		while (saved_from_buffer[i] != '\0')
			i++;
		temp = malloc(sizeof(char) * (i + chars_read + 1));
		if (temp == NULL)
			return (NULL);
		i = 0;
		while (saved_from_buffer[i] != '\0')
		{
			temp[i] = saved_from_buffer[i];
			i++;
		}
		j = 0;
		while (buffer[j] != '\0')
		{
			temp[i + j] = buffer[j];
			j++;
		}
		temp[i + j] = '\0';
		free(saved_from_buffer);
		saved_from_buffer = temp;
	}
	i = 0;
	while (saved_from_buffer[i] != '\0')
	{
		if (saved_from_buffer[i] == '\n')
		{
			line = malloc(sizeof(char) * (i + 1));
			if (line == NULL)
				return (NULL);
			j = 0;
			while(j <= i)
			{
				line[j] = saved_from_buffer[j];
				j++;
			}
			line[j] = '\0';
			j = 0;
			while (saved_from_buffer[i + j] != '\0')
				j++;
			temp = malloc(sizeof(char) * (j + 1));
			if (temp == NULL)
				return (NULL);
			j = 0;
			while (saved_from_buffer[i + j] != '\0')
			{
				temp[j] = saved_from_buffer[i + j]; 
				j++;
			}
			temp[j] = '\0';
			free (saved_from_buffer);
			saved_from_buffer = temp;
			break ;
		}
		i++;
	}
	return (line);
}

char	*read_from_file(int fd, char *buffer)
{
	ssize_t	chars_read;
	char	*line;

	chars_read = 1;
	while (chars_read > 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		line = save_from_buffer(buffer, chars_read);
	}
	buffer[chars_read] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	line = read_from_file(fd, buffer);
	free(buffer);
	return (line);
}

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);

	printf("first call ->\n");
	line = get_next_line(fd);
	printf("%s\n", line);
	printf("second call ->\n");
	line = get_next_line(fd);
	printf("%s\n", line);
	printf("third call ->\n");
	line = get_next_line(fd);
	printf("%s\n", line);
	free (line);
	close (fd);
}
