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

const int	BUFFER_SIZE;

BUFFER_SIZE = 1024;

char	*get_next_line(int fd)
{
	static int	bytes_read;
	char	*buffer[BUFFER_SIZE];
	char	*line;
	size_t	i;
	size_t	j;
	
	i = 0;
	j = 0;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, sizeof(char));
		while (buffer[i] != '\0')
		{
			if (buffer[i] == '\n')
			{
				bytes_read = i;

			}
		}
	}
	return (line);
}
