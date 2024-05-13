/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarin <vmarin@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:35:13 by vmarin            #+#    #+#             */
/*   Updated: 2024/05/09 22:00:10 by vmarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char	*get_next_line(int fd)
{
	int	i;
	int	j;
	int	x;
	int	line_len;
	ssize_t	bytes_read;
	char	*buffer;
	char	*lines;
	char	*line;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	lines = NULL;
	bytes_read = -1;
	x = 0;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (lines == NULL)
		{
			lines = malloc(bytes_read + 1);
			if (lines == NULL)
				return (NULL);
			lines[bytes_read] = '\0';
		}
		else if(lines != NULL)
		{
			char	*temp;
			int	len;

			len = 0;
			while (lines[len] != '\0')
				len++;
			temp = malloc(len + bytes_read + 1);
			if (temp == NULL)
				return (NULL);
			temp[len + bytes_read] = '\0';
			i = 0;
			while (lines[i] != '\0')
			{
				temp[i] = lines[i];
				i++;
			}
			lines = temp;
		}
		i = 0;
		while (i < bytes_read)
		{
			lines[x] = buffer[i];
			i++;
			x++;
		}
		i = 0;
		j = 0;
		while (lines[i] != '\0')
		{
			if (lines[i] == '\n')
			{
				line_len = i - j;
				line = malloc(line_len + 1);
				if (line == NULL)
					return (NULL);
				line[line_len] = '\0';
				while (j < line_len) 
				{
					line[j] = lines[j];
					j++;
				}
				return (line);
			}
			i++;
		}
		free (buffer);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return ("bazinga");
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
}
