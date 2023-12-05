#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

size_t  ft_strlen(char *s);
int	ft_strchr(int c, char *buffer);
char    *ft_strjoin(char *stash, char *buff);

#endif


