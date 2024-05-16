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
# define BUFFER_SIZE 1 
#endif

void	shift_buffer(char **buffer, int i)
{
	char	*temp;
	int	j;

	j = i;
	while((*buffer)[j] != '\0')
	{
		j++;
	}
	j = j - i;
	temp = malloc(sizeof(char) * (j + 1));
	if (temp == NULL)
		return ;
	j = 0;
	while ((*buffer)[i + j] != '\0')
	{
		temp[j] = (*buffer)[i + j];
		j++;
	}
	temp[j] = '\0';
	free(*buffer);
	*buffer = temp;
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		len;
	char	to_find;

	to_find = (char)c;
	len = ft_strlen(s);
	i = 0;
	while (i < len + 1)
	{
		if (s[i] == to_find)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
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
	return (line);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len + 1 < size)
	{
		i = 0;
		while (i < src_len + 1)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else if (size != 0)
	{
		i = 0;
		while (i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	size_t	i;

	duplicate = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (duplicate == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s) + 1)
	{
		duplicate[i] = s[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*read_from_file(int fd)
{
	static char	*buffer = NULL;
	char	*temp;
	char	*line;
	char	*newline_address;
	ssize_t	bytes_read;
	int	i;
	int	line_len;
	
	if (buffer == NULL)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return (NULL);
	}
	i = 0;
	while ((bytes_read = read(fd, buffer + i, BUFFER_SIZE)) >= 0)
	{
		i += bytes_read;
		buffer[i] = '\0';
		newline_address = ft_strchr(buffer, '\n');
		if (newline_address != NULL)
		{
			line_len = newline_address - buffer;
			line = get_line(buffer, line_len);
			shift_buffer(&buffer, line_len + 1);
			return (line);
		}
		else
		{
			temp = malloc(sizeof(char) * (BUFFER_SIZE + ft_strlen(buffer) + 1));
			if (temp == NULL)
				return (NULL);
			ft_strlcpy(temp, buffer, BUFFER_SIZE + ft_strlen(buffer) + 1);
			free(buffer);
			buffer = temp;
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_from_file(fd);
	return (line);
}

int	main(void)
{
	int	fd;
	int	fd2;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);

	printf("first call ->\n");
	line = get_next_line(fd);
	printf("%s\n", line);
	printf("first call second file ->\n");
	line = get_next_line(fd2);
	printf("%s\n", line);
	printf("second call ->\n");
	line = get_next_line(fd);
	printf("%s\n", line);
	printf("third call ->\n");
	line = get_next_line(fd);
	printf("%s\n", line);
	printf("third call ->\n");
	line = get_next_line(fd);
	printf("%s\n", line);
	close (fd);
}
