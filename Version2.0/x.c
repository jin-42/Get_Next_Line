/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <fsulvac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:01:35 by fsulvac           #+#    #+#             */
/*   Updated: 2023/12/02 17:41:45 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stddef.h>
# define BUFFER_SIZE 5
# include <unistd.h>
# include <stdio.h>
#include <fcntl.h>
typedef struct s_node
{
	char	*data;
	struct s_node *next;
}	t_node;
/*==================================== First Part =====================================*/
char *ft_strdup(char *src)
{
	size_t i;
	char *dup;

	i = 0;
	dup = NULL;
	while (src[i])
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}


t_node *ft_create_node(char *data)
{
	t_node	*node;

	if (!node)
		return (NULL);
	node->data = ft_strdup(data);
	node->next = NULL;
	return (node);
}

int	search_line(char *buff)
{
	int i;

	i = 0;
	while (*buff != '\0')
	{
		if (*buff == '\n')
			return (1);
		i++;
		buff++;
	}
	if (i < BUFFER_SIZE)
		return (2);
	return (0);
}

void read_to_node(int fd, t_node **node) {
	int	readed;
    char *buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    while (1) 
	{
        *node = ft_create_node(buff);
        if (!*node) {
            free(buff);
            return;
        }
        if (search_line(buff) == 1)
            break;
        readed = read(fd, buff, BUFFER_SIZE);
        if (readed <= 0)
            break;
        buff[readed] = '\0';
    }
    free(buff);
}


/*===========================Seconde Part===========================*/

int ft_list_size(t_node *begin_list)
{
	int size;
	t_node *current;

	size = 0;
	current = begin_list;
	while (current)
	{
		size++;
		current = current->next;
	}
	return size;
}

char *node_to_str(t_node **node_tmp)
{
	char	*str;
	char	*data;
	t_node	*node;

	str = malloc(sizeof(char) * (ft_list_size(node) + 1));
	if (!str)
		return (NULL);
	node = *node_tmp;
	while (node != NULL)
	{	
		data = node->data;
		while (*data != '\0')
		{
			*str = *data;
			if (*data == '\n')
				return (++str, *str = '\0', str);
			str++;
			data++;
		}
		free(node->data);
		free(node);
		node = node->next;
	}
	free(node);
	node = node->next;
	return (++str, *str = '\0', str);
}

/*===================Third Part===================*/


char *get_next_line(int fd)
{
	t_node *node;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	// J aimerai cree une liste et dans laquel je met mes data jusau'a avoir soit \n soit EOF
	read_to_node(fd, &node);
	// J extrai jusau'a \n ou EOF dans un str et je renvoiea
	return (node_to_str(&node));
	// Je free tout si j ai eof ou sinon je free jusqu'a \n - 1
}

int main() {
    int fd = open("note.txt", O_RDONLY); // Remplacez "exemple.txt" par votre fichier

    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s\n", line);
        free(line);
    }

    close(fd);

    return 0;
}


