#include "get_next_line.h"
#include <unistd.h>

int	find_newline(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list != NULL)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

t_list	*find_last_node(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

int	get_line_len(t_list *list)
{
	int	len;
	int	i;

	len = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

void	fill_line(t_list *list, char *line)
{
	int	i;
	int 	j;

	if (list == NULL)
		return ;
	j = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				line[j] = '\n';
				j++;
				line[j] = '\0';
				return ;

			}
			line[j] = list->content[i];
			j++;
			i++;
		}
		list = list->next;
	}
	line[j] = '\0';
}

void	free_memory(t_list **list, t_list *fresh_node)
{
	t_list	*next_node;

	if (*list == NULL)
		return ;
	while (*list) 
	{
		next_node = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = next_node;
	}
	*list = NULL;
	if (fresh_node->content[0])
		*list = fresh_node;
	else
	{
		free(fresh_node->content);
		free(fresh_node);
	}
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(char	*str)
{
	char	*duplicate;
	size_t	i;

	if (str == NULL)
		return (NULL);
	duplicate = malloc(ft_strlen(str) + 1);
	if (duplicate == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		duplicate[i] = str[i];
		i++;
	}
	duplicate[i] = '\0';
	return(duplicate);
}
