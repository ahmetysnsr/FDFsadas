/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:39:19 by asari             #+#    #+#             */
/*   Updated: 2025/12/05 03:48:38 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		result;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str++ - 48);
	}
	return (result * sign);
}

int	ft_atoi_hex(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	if (!str)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	while (str[i])
	{
		result = result * 16;
		if (str[i] >= '0' && str[i] <= '9')
			result += str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			result += str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			result += str[i] - 'A' + 10;
		else
			break ;
		i++;
	}
	return (result);
}

void	free_matrix(t_map *map)
{
	int	y;

	if (!map->matrix)
		return ;
	y = 0;
	while (y < map->height)
	{
		if (map->matrix[y])
			free(map->matrix[y]);
		y++;
	}
	free(map->matrix);
	map->matrix = NULL;
}
