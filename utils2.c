/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:51:28 by asari             #+#    #+#             */
/*   Updated: 2025/12/04 17:47:37 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"
#include "GNL/get_next_line.h"

void	flush_gnl(int fd)
{
	char	*temp;

	temp = get_next_line(fd);
	while (temp)
	{
		free(temp);
		temp = get_next_line(fd);
	}
}

int	check_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 4)
		return (0);
	if (filename[len - 4] == '.' && filename[len - 3] == 'f'
		&& filename[len - 2] == 'd' && filename[len - 1] == 'f')
		return (1);
	return (0);
}

int	ft_ternary(int condition, int true_val, int false_val)
{
	if (condition)
		return (true_val);
	return (false_val);
}
