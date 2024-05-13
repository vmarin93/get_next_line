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

void	read_from_file(int fd, char *buffer)
{
	ssize_t	chars_read;
	char	*read_from_file;
	int	i;

	chars_read = 1;
	read_from_file = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_from_file == NULL)
		return ; 
	while (chars_read != 0)
	{
		chars_read = read(fd, read_from_file, BUFFER_SIZE);
		read_from_file[chars_read] = '\0';
		buffer = malloc(sizeof(char) * (chars_read + 1));
		if (buffer == NULL)
			return ;
		i = 0;
		while (read_from_file[i] != '\0')
		{
			buffer[i] = read_from_file[i];
			i++;
		}
	}
	free (read_from_file);
}

char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	read_from_file(fd, buffer);
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
