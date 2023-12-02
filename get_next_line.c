/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <fsulvac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:01:35 by fsulvac           #+#    #+#             */
/*   Updated: 2023/12/02 13:58:26 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    t_list *node = ft_create_elem(NULL);
    char *line;
    size_t readed;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    from_read_to_list(fd, &readed, &node);
    line = extract_list_to_str(&node);
    return line;
}

int from_read_to_list(int fd, size_t *readed, t_list **node)
{
    char buff[BUFFER_SIZE + 1];

    while (1)
    {
        *readed = read(fd, buff, BUFFER_SIZE);
        buff[*readed] = '\0';
        (*node)->data = ft_strdup(buff);
        (*node)->next = ft_create_elem(NULL);
        *node = (*node)->next;

        if (search_line_in_buffer(buff) == 1)
            return 1;
        if (*readed < BUFFER_SIZE)
            return 0;
    }
}

char *extract_list_to_str(t_list **node)
{
    char *line;
    size_t i;
	char	*tmp_str;

    line = malloc(sizeof(char) * (ft_list_size(*node) * BUFFER_SIZE + 1));
    if (!line)
        return (NULL);
    i = 0;
    while (*node != NULL)
    {
		tmp_str = (*node)->data;
        while (i < BUFFER_SIZE)
        {
			if (*(tmp_str) == '\n')
			{	
				*line++ = '\n';
				return (*line = '\0', line);		
			}
            *line++ = *tmp_str++;
            i++;
        }
        i = 0;
        *node = (*node)->next;
    }
    *line = '\0';
    return line;
}


char *free_list(t_list **node)
{
    char *line = NULL;

    while (*node != NULL && search_line_in_buffer((*node)->data) != 1)
    {
        t_list *temp = *node;
        *node = (*node)->next;

        if (line == NULL)
        {
            line = temp->data;
            temp->data = NULL;
        }

        free(temp->data);
        free(temp);
    }

    return line;
}

#include <fcntl.h>  // Pour open et close

int main(void)
{
    int fd;
    char *line;

    fd = open("note.txt", O_RDONLY);  // Remplacez "example.txt" par le nom de votre fichier.
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        // Faites quelque chose avec la ligne, par exemple l'afficher.
        printf("%s\n", line);
        free(line);
    }

    close(fd);

    return 0;
}
