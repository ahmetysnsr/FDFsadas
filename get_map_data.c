/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:59:33 by asari             #+#    #+#             */
/*   Updated: 2025/12/02 13:59:33 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"
#include <unistd.h>
#include <fcntl.h>
#include "GNL/get_next_line.h"

void	free_split_and_line(char *line, char **split)
{
	free_split(split);
	free(line);
}

void	clean_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i > 0 && line[i - 1] == '\n')
		line[i - 1] = '\0';
}

static int	count_words(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	process_lines(int fd, int *height, int *width)
{
	char	*line;
	char	**split;

	*height = 0;
	*width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		clean_newline(line);
		split = ft_split(line, ' ');
		if (*height == 0)
			*width = count_words(split);
		else if (count_words(split) != *width)
		{
			free_split_and_line(line, split);
			return (0);
		}
		(*height)++;
		free_split_and_line(line, split);
	}
	return (1);
}

int	get_map_data(int *height, int *width, char *filename)
{
	int	fd;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		*height = 0;
		*width = 0;
		return (0);
	}
	if (!process_lines(fd, height, width))
	{
		flush_gnl(fd);
		close(fd);
		*height = 0;
		*width = 0;
		return (0);
	}
	close(fd);
	return (1);
}
