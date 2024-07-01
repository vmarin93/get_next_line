/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmarin <vmarin@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:41:49 by vmarin            #+#    #+#             */
/*   Updated: 2024/07/01 17:41:51 by vmarin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	if (dst == NULL || src == NULL)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

char	*ft_strdup(const char *buffer)
{
	char	*new_buffer;
	int		i;

	if (buffer == NULL)
		return (NULL);
	new_buffer = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	if (new_buffer == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0')
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	new_buffer[i] = '\0';
	return (new_buffer);
}
