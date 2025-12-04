/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:40:34 by asari             #+#    #+#             */
/*   Updated: 2025/08/23 15:51:16 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*free_and_return(char **pointer)
{
	free(*pointer);
	*pointer = NULL;
	return (NULL);
}

char	*ft_loop(int fd, char **stash, char **buffer)
{
	ssize_t	readed_char;

	readed_char = 1;
	while (!ft_is_in_newline(*stash) && readed_char != 0)
	{
		readed_char = read(fd, *buffer, BUFFER_SIZE);
		if (readed_char == -1)
		{
			free_and_return(stash);
			free(*buffer);
			return (NULL);
		}
		(*buffer)[readed_char] = '\0';
		*stash = ft_strjoin_and_free(*stash, *buffer);
		if (!*stash)
			return (free_and_return(buffer));
	}
	free(*buffer);
	if (!*stash || (*stash)[0] == '\0')
	{
		if (*stash)
			free_and_return(stash);
		return (NULL);
	}
	return (*stash);
}

char	*ft_get_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_remove_first_line(char *stash)
{
	char	*new_stash;
	int		i;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free_and_return(&stash));
	new_stash = ft_strdup(stash + i + 1);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash = NULL;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (free_and_return(&stash));
	if (stash == NULL)
	{
		stash = malloc(1);
		if (!stash)
			return (free_and_return(&buffer));
		stash[0] = '\0';
	}
	if (ft_loop(fd, &stash, &buffer) == NULL)
		return (NULL);
	line = ft_get_line(stash);
	if (!line)
		return (free_and_return(&stash));
	stash = ft_remove_first_line(stash);
	return (line);
}
