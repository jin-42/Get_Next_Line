/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <fsulvac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:26:58 by fsulvac           #+#    #+#             */
/*   Updated: 2023/11/30 16:26:53 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>  // Ajout de l'en-tête pour malloc
#include "get_next_line.h"

t_list *ft_create_elem(void *data)
{
	t_list *new;  // Correction du type de new

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	new->data = data;
	new->next = NULL;
	return (new);
}

int search_line_in_buffer(char *buffer)
{
	size_t buff_size;

	buff_size = 0;
	while (buffer[buff_size] != '\0')
	{
		if (buffer[buff_size] == '\n')
			return (1);
		buff_size++;
	}
	if (buff_size < BUFFER_SIZE)
		return (1);
	return (0);
}

int ft_list_size(t_list *begin_list)
{
	int size;
	t_list *current;

	size = 0;
	current = begin_list;
	while (current)
	{
		size++;
		current = current->next;  // Correction de l'accès à la prochaine structure de la liste
	}
	return size;
}

char *ft_strdup(const char *src)
{
	size_t i;
	char *dup;

	i = 0;
	dup = NULL;
	while (src[i])
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);  // Correction de la valeur de retour en cas d'échec de l'allocation
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';  // Correction de la null-termination
	return (dup);
}
//search in line return 0 false and true 1
