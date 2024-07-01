/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarin <vmarin@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:35:13 by vmarin            #+#    #+#             */
/*   Updated: 2024/07/01 17:39:35 by vmarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_newline(char *buffer)
{
	int	i;

	i = 0;
	while (buffer != NULL && buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*append_to_buffer(char *buffer, char *temp, ssize_t bytes_read)
{
	char	*new_buffer;
	size_t	buffer_len;

	buffer_len = 0;
	if (buffer != NULL)
		buffer_len = ft_strlen(buffer);
	new_buffer = malloc(sizeof(char) * buffer_len + bytes_read + 1);
	if (new_buffer == NULL)
		return (NULL);
	if (buffer != NULL)
	{
		ft_strcpy(new_buffer, buffer);
		free(buffer);
	}
	ft_strcpy(new_buffer + buffer_len, temp);
	return (new_buffer);
}

char	*get_line(char **buffer, int newline_index)
{
	char	*line;
	char	*new_buffer;
	int		i;

	line = malloc(newline_index + 2);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i <= newline_index)
	{
		line[i] = (*buffer)[i];
		i++;
	}
	line[i] = '\0';
	new_buffer = ft_strdup(*buffer + newline_index + 1);
	free(*buffer);
	*buffer = new_buffer;
	if ((*buffer) != NULL && (*buffer)[0] == '\0')
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*handle_eof(char **buffer, char *temp)
{
	char	*line;

	line = *buffer;
	*buffer = NULL;
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*temp;
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (temp == NULL)
		return (NULL);
	while (find_newline(buffer[fd]) == -1)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1 && buffer[fd] == NULL)
			return (NULL);
		else if (bytes_read == 0)
			return (handle_eof(&buffer[fd], temp));
		temp[bytes_read] = '\0';
		buffer[fd] = append_to_buffer(buffer[fd], temp, bytes_read);
		if (buffer[fd] == NULL)
			return (NULL);
	}
	line = get_line(&buffer[fd], find_newline(buffer[fd]));
	free(temp);
	return (line);
}
