#include "get_next_line.h"
#include <stdlib.h>

void	clean_list(t_list **list)
{
	t_list	*last_node;
	t_list	*fresh_node;
	int	i;
	char	*temp;

	last_node = find_last_node(*list);
	if (last_node == NULL)
		return ;
	i = 0;
	while (last_node->content[i] != '\n' && last_node->content[i] != '\0')
		i++;
	if (last_node->content[i] == '\n')
		i++;
	temp = ft_strdup(&last_node->content[i]);
	if (temp == NULL)
		return ;
	fresh_node = malloc(sizeof(t_list));
	if (fresh_node == NULL)
	{
		free(temp);
		return ;
	}

	fresh_node->content = temp;
	fresh_node->next = NULL;

	free_memory(list, fresh_node);
}

char	*get_line(t_list *list)
{
	int	line_len;
	char	*line;

	if (list == NULL)
		return (NULL);
	line_len = get_line_len(list);
	line = malloc(sizeof(char) * (line_len + 1));
	if (line == NULL)
		return (NULL);
	fill_line(list, line);
	return(line);
}

void	append_to_list(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
	{
		free(buffer);
		return ;
	}
	new_node->content = buffer;
	new_node->next = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		last_node = find_last_node(*list);
		if (last_node != NULL)
			last_node->next = new_node;
	}
}

void	read_from_file(t_list **list, int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	while (!find_newline(*list))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		append_to_list(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	read_from_file(&list, fd);
	if (list == NULL)
		return (NULL);
	line = get_line(list);
	clean_list(&list);
	return (line);
}
