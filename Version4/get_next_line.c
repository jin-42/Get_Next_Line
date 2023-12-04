/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <fsulvac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 12:08:43 by fsulvac           #+#    #+#             */
/*   Updated: 2023/12/04 14:39:21 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char *stash_to_line(char *stash)
{
    char *line;
    size_t i;

    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    line = (char *)malloc(sizeof(char) * (i + 1)); // +1 because '\0'
    if (!line)
        return (NULL);
    i = 0;
    while (stash[i] != '\n' && stash[i])
    {
        line[i] = stash[i];
        i++;
    }
    line[i] = '\0';
    return line;
}

char *read_to_stash(int fd, char *stash)
{
    char *buff;
    int readed;

    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buff)
        return (NULL);
    readed = 1;
    while (!ft_strchr(stash, '\n') && readed != 0)
    {
        readed = read(fd, buff, BUFFER_SIZE);
        if (readed == -1)
        {
            free(buff);
            return (NULL);
        }
        buff[readed] = '\0';
        stash = ft_strjoin(stash, buff);
    }
    free(buff);
    return (stash);
}

char *clean_stash(char *stash)
{
    size_t i;
    size_t j;
    char *new_stash;

    if (!stash)
        return (NULL);
    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] == '\n')
        i++;
    j = 0;
    if (i == ft_strlen(stash))
        return (free(stash), NULL);
    new_stash = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
    if (!new_stash)
        return (NULL);
    while (stash[i + j] != '\0')
    {
        new_stash[j] = stash[i + j];
        j++;
    }
    free(stash);
    new_stash[j] = '\0';
    return new_stash;
}

char *get_next_line(int fd)
{
    char *line;
    static char *stash;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    stash = read_to_stash(fd, stash);
    if (!stash)
        return (NULL);
    line = stash_to_line(stash);
    stash = clean_stash(stash);
    return line;
}

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

    line = get_next_line(fd);
    printf("%s\n", line);
    free(line);

    line = get_next_line(fd);
    printf("%s\n", line);
    free(line);
    line = get_next_line(fd);
    printf("%s\n", line);
    free(line);
    close(fd);
    return (0);
}

