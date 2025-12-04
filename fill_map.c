/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:14:38 by asari             #+#    #+#             */
/*   Updated: 2025/12/04 16:41:32 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "GNL/get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

t_point	**allocate_matrix(int height, int width)
{
	int		i;
	int		j;
	t_point	**matrix;

	matrix = malloc(sizeof(t_point *) * height);
	if (matrix == NULL)
		return (NULL);
	i = 0;
	while (i < height)
	{
		matrix[i] = malloc(sizeof(t_point) * width);
		if (!matrix[i])
		{
			while (--i >= 0)
				free(matrix[i]);
			free(matrix);
			return (NULL);
		}
		j = 0;
		while (j < width)
		{
			matrix[i][j].is_valid = 0;
			matrix[i][j].z = 0;
			matrix[i][j].color = 0;
			j++;
		}
		i++;
	}
	return (matrix);
}

static void	parse_point_data(char *s, t_point *point)
{
	char	*comma;

	point->z = ft_atoi(s);
	comma = ft_strchr(s, ',');
	if (comma)
		point->color = ft_atoi_hex(comma + 1);
	else
		point->color = 0xFFFFFF;
}

static void	process_row(t_point *row_points, char **split, int width)
{
	int	x;
	int	split_ended;

	x = 0;
	split_ended = 0;
	while (x < width)
	{
		if (!split_ended && split[x])
		{
			parse_point_data(split[x], &row_points[x]);
			row_points[x].is_valid = 1;
		}
		else
		{
			split_ended = 1;
			row_points[x].z = 0;
			row_points[x].color = 0;
			row_points[x].is_valid = 0;
		}
		x++;
	}
}

int	fill_map_helper(int fd, int height, int width, t_map *map)
{
	char	*line;
	char	**split;
	int		y;

	y = 0;
	while (y < height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		clean_newline(line);
		split = ft_split(line, ' ');
		if (!split)
		{
			free(line);
			flush_gnl(fd);
			return (0);
		}
		process_row(map->matrix[y], split, width);
		free_split_and_line(line, split);
		y++;
	}
	flush_gnl(fd);
	return (1);
}

int	fill_map(t_map *map, int height, int width, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	map->matrix = allocate_matrix(height, width);
	if (!map->matrix)
	{
		close(fd);
		return (0);
	}
	map->height = height;
	map->width = width;
	if (!fill_map_helper(fd, height, width, map))
	{
		free_matrix(map);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
