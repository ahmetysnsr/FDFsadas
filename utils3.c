/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:47:11 by asari             #+#    #+#             */
/*   Updated: 2025/12/05 04:45:28 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int	get_z_range(t_map *map)
{
	int	x;
	int	y;
	int	min;
	int	max;

	y = -1;
	max = -2147483648;
	min = 2147483647;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (!map->matrix[y][x].is_valid)
				continue ;
			if (map->matrix[y][x].z > max)
				max = map->matrix[y][x].z;
			if (map->matrix[y][x].z < min)
				min = map->matrix[y][x].z;
		}
	}
	return (max - min);
}

float	cal_scale(t_map *map, t_view *v)
{
	float	scale_x;
	float	scale_y;
	int		z_range;

	scale_x = (v->win_w * 0.5) / (map->width + map->height);
	z_range = get_z_range(map);
	if (z_range == 0)
		scale_y = 1000.0;
	else
		scale_y = (v->win_h * 0.4) / z_range;
	if (scale_x < scale_y)
		return (scale_x);
	return (scale_y);
}

void	img_put_pixel(t_img *img, int x, int y, int color)
{
	int		bpp;
	int		max_x;
	char	*p;

	if (x < 0 || y < 0)
		return ;
	if (y >= 800)
		return ;
	bpp = img->bpp / 8;
	max_x = img->line_len / bpp;
	if (x >= max_x)
		return ;
	p = img->data + y * img->line_len + x * bpp;
	if (p < img->data)
		return ;
	if (p + bpp > img->data + (y + 1) * img->line_len)
		return ;
	*(unsigned int *)p = (unsigned int)color;
}

t_vector	project_iso(int x, int y, int z, t_view *v)
{
	t_vector	p;
	float		xr;
	float		yr;

	yr = ((x + y) * sinf(v->angle)) - (z * v->zscale);
	xr = (x - y) * cosf(v->angle);
	p.x = (int)(xr * v->scale) + v->offset_x;
	p.y = (int)(yr * v->scale) + v->offset_y;
	return (p);
}

int	my_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}
