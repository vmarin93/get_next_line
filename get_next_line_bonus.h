/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarin <vmarin@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:40:57 by vmarin            #+#    #+#             */
/*   Updated: 2024/07/01 17:56:48 by vmarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1 
# endif

char	*get_next_line(int fd);
int		ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
size_t	ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s);

#endif
