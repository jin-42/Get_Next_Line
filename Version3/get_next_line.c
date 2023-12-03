#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);


char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s != '\0')
		s++;
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buff;
	int		readed;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readed = 1;
	while (readed != 0 && !ft_strchr(stash, '\n'))
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
			return (free(buff), NULL);
		buff[readed] = '\0';
		stash = ft_strjoin(stash, buff);
	}
	free(buff);
	return (stash);
}

static char	*substash(char *stash, size_t len)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i])
		i++;
	tmp = (char *)malloc(sizeof(char) * (i - len + 1));
	if (!tmp)
		return (NULL);
	i = len;
	while (stash[i])
	{
		*tmp = stash[i];
		i++;
		tmp++;
	}
	*tmp = '\0';
	free(stash);
	return (tmp - i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*stash_to_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	stash = substash(stash, i);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;
	static char	*stash;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);

	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);

	line = stash_to_line(stash);
	return (line);
}

int main(void)
{
    int fd = open("note.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}

