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

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 14
#endif

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

void	shift_buffer(char *buffer, int i)
{
	int	j;
	int	k;
	int	buffer_len;
	char	*temp;

	buffer_len = ft_strlen(buffer);
	temp = malloc(sizeof(char) * (buffer_len - i + 1));
	if (temp == NULL)
		return ;
	j = i + 1;
	k = 0;
	while (buffer[j] != '\0')
	{
		temp[k] = buffer[j + k];
	}
	temp[k] = '\0';
	free (buffer);
	buffer = temp;
}

char	*get_line(char *buffer, int i)
{
	char	*line;
	int	j;

	line = malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';
	shift_buffer(buffer, i);
	return (line);
}

char	*read_from_file(int fd)
{
	static char	*buffer = NULL;
	char	*temp;
	ssize_t	bytes_read;
	int	i;
	
	bytes_read = 1;
	while (bytes_read > 0)
	{
		if (buffer == NULL)
		{
			buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
			if (buffer == NULL)
				return (NULL);
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			buffer[bytes_read] = '\0';
			i = 0;
			while (buffer[i] != '\0')
			{
				if (buffer[i] == '\n')
					return (get_line(buffer, i));
				i++;
			}
		}
		else
		{
			i = 0;
			while (buffer[i] != '\0')
				i++;
			temp = malloc(sizeof(char) * (i + BUFFER_SIZE + 1));
			if (temp == NULL)
				return (NULL);
			i = 0;
			while (buffer[i] != '\0')
			{
				temp[i] = buffer[i];
				i++;
			}
			bytes_read = read(fd, temp + i, BUFFER_SIZE);
			temp[bytes_read + i] = '\0';
			free (buffer);
			buffer = temp;
			i = 0;
			while (buffer[i] != '\0')
			{
				if (buffer[i] == '\n')
					return (get_line(buffer, i));
				i++;
			}
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)
		return (NULL);
	line = read_from_file(fd);
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
