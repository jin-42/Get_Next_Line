/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <fsulvac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:02:36 by fsulvac           #+#    #+#             */
/*   Updated: 2023/11/30 16:26:52 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
    char            *data;
    struct s_list   *next;
}   t_list;

char    *get_next_line(int fd);
int     from_read_to_list(int fd, size_t *readed, t_list **node);
char    *extract_list_to_str(t_list **node);
char    *free_list(t_list **node);
t_list  *ft_create_elem(void *data);
int     search_line_in_buffer(char *buffer);
int     ft_list_size(t_list *begin_list);
char    *ft_strdup(const char *src);

#endif
