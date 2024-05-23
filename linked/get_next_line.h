#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_list
{
	char	*content;
	struct	s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*ft_strdup(char *str);
int	find_newline(t_list *list);
t_list	*find_last_node(t_list *list);
int	get_line_len(t_list *list);
void	fill_line(t_list *list, char *line);
void	free_memory(t_list **list, t_list *fresh_node);

#endif
