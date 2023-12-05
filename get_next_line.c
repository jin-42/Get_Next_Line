/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <fsulvac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:52:36 by fsulvac           #+#    #+#             */
/*   Updated: 2023/12/05 15:15:28 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//char *get_next_line(int fd);

/*
	Return value : if stash is empty or fd < 0 or readed has error return NULL, return new stash
*/
# include "get_next_line.h"

char	*read_to_stash(char *stash, int fd)
{
	char	*buffer;
	size_t	readed;
	if (BUFFER_SIZE <= 0 || fd < 0 )
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1 || readed == 0)
			return (free(buffer), NULL);
		buffer[readed] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (ft_strchr('\n', stash) == 1)
			return (free(buffer), stash);
	}
	free(buffer);
	return (stash);
}

char *stash_to_line(char *stash)
{
	char	*line;
	size_t 	i;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	line = (char *)malloc(sizeof(char *) * (i + 2I)); // if they are \n
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0'; 
	return (line);
}

char *clean_stash(char *stash)
{
	char *cleaned;
	size_t i;
	size_t	j;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		i++;
	if (i == ft_strlen(stash))
		return (NULL);
	j = 0;
	cleaned = (char *)malloc(sizeof(char) * (ft_strlen(stash) - 1 + i));
	if (!cleaned)
		return (NULL);
	while (stash[i] != '\0')
	{
		cleaned[j] = stash[i];
		i++;
		j++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}
char *get_next_line(int fd)
{
	char	*line;
	static char *stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(stash, fd);
	if (!stash)
		return (NULL);
	line = stash_to_line(stash);
	stash = clean_stash(stash);
	return (line);
}
#include "get_next_line.h"
#include <fcntl.h>  // Ajoutez cette ligne pour inclure les déclarations de open et O_RDONLY

int main(void)
{
    int fd;
    char *line;

    fd = open("note.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return (1);
    }

    while ((line = get_next_line(fd)))
    {
        printf("%s\n", line);
        free(line);
    }

    close(fd);

    return (0);
}

