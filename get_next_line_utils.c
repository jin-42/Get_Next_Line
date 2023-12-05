/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <fsulvac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:21:21 by fsulvac           #+#    #+#             */
/*   Updated: 2023/12/04 17:57:47 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr(int c, char *buffer)
{
	while (*buffer != (char)c && *buffer != '\0')
		buffer++;
	if (*buffer == (char)c)
		return 1;
	return (0);
}

char	*ft_strjoin(char *stash, char *buff)
{
	char	*s;
	size_t	i;
	size_t 	j;

	if (!buff)
		return (NULL);
	else if (!stash)
		s = (char *)malloc(sizeof(char) * (ft_strlen(buff) + 1));
	else 
		s = (char *)malloc(sizeof(char) * (ft_strlen(buff) + ft_strlen(stash) + 1));
	if (!s)
		return (NULL);
	i = 0;
	if (stash != NULL)
	{
		while (stash[i] != '\0')
		{
				s[i] = stash[i];
				i++;
		}
	}
	j = 0;
	while (buff[j])
	{
		s[i + j] = buff[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}
