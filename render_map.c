/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:35:02 by asari             #+#    #+#             */
/*   Updated: 2025/12/04 23:58:32 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

static void	project_iso(float x, float y, float z, t_view *v, int *sx, int *sy)
{
	float	xr;
	float	yr;

	yr = ((x + y) * sinf(v->angle) ) - z;
	xr = (x - y) * cosf(v->angle);
	*sx = (int)(xr * v->scale) + v->offset_x;
	*sy = (int)(yr * v->scale) + v->offset_y;
}

static void	img_put_pixel(t_img *img, int x, int y, int color)
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

static void	bresenham_img(t_img *img, t_bresenham *b)
{
	int	e2;

	b->dx = abs(b->x1 - b->x0);
	b->dy = -abs(b->y1 - b->y0);
	b->sx = ft_ternary(b->x0 < b->x1, 1, -1);
	b->sy = ft_ternary(b->y0 < b->y1, 1, -1);
	b->err = b->dx + b->dy;
	while (1)
	{
		img_put_pixel(img, b->x0, b->y0, b->color);
		if (b->x0 == b->x1 && b->y0 == b->y1)
			break ;
		e2 = 2 * b->err;
		if (e2 >= b->dy)
		{
			b->err += b->dy;
			b->x0 += b->sx;
		}
		if (e2 <= b->dx)
		{
			b->err += b->dx;
			b->y0 += b->sy;
		}
	}
}

static float	cal_scale(t_map *map, t_view *v)
{
	float	scale_x;
	float	scale_y;
	float	scale_z;
	int		min;
	int		max;
	int		x;
	int		y;

	scale_x = (v->win_w * 0.40) / map->width;
	scale_y = (v->win_h * 0.40) / map->height;
	y = -1;
	max = -2147483648;
	min = 2147483647;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (!map->matrix[y][x].is_valid)
				continue;
			if (map->matrix[y][x].z > max)
				max = map->matrix[y][x].z;
			if (map->matrix[y][x].z < min)
				min = map->matrix[y][x].z;
		}
	}
	if (max - min == 0)
		scale_z = 1000.0;
	else
		scale_z = (v->win_h * 0.40) / (max - min);
	if (scale_x < scale_y && scale_x < scale_z)
		return (scale_x);
	if (scale_y < scale_z)
		return (scale_y);
	return (scale_z);
}
static void	compute_view(t_map *map, t_view *v)
{
	float	base;
	
	v->win_w = 1200;
	v->win_h = 800;
	base = (map->width > map->height) ? map->width : map->height;
	
	v->scale = cal_scale(map, v);
	v->zscale =	v->scale;
	v->angle = 0.523599f;
	v->offset_x = v->win_w / 2;
	v->offset_y = 350;
}

/*static void	draw_wireframe(void *mlx, void *win, t_map *map, t_view *v)
{
	t_img		img;
	t_bresenham	b;
	int			x;
	int			y;
	int			sx;
	int			sy;
	int			sx2;
	int			sy2;

	img.img = mlx_new_image(mlx, v->win_w, v->win_h);
	if (!img.img)
		return ;
	img.data = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	if (!img.data)
	{
		mlx_destroy_image(mlx, img.img);
		return ;
	}
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->matrix[y][x].is_valid == 1)
			{
				project_iso(x, y, map->matrix[y][x].z, v, &sx, &sy);
				if (x + 1 < map->width && map->matrix[y][x + 1].is_valid == 1)
				{
					project_iso(x + 1, y, map->matrix[y][x + 1].z, v, &sx2, &sy2);
					b.x0 = sx; b.y0 = sy; b.x1 = sx2; b.y1 = sy2;
					b.color = map->matrix[y][x].color;
					bresenham_img(&img, &b);
				}
				if (y + 1 < map->height && map->matrix[y + 1][x].is_valid == 1)
				{
					project_iso(x, y + 1, map->matrix[y + 1][x].z, v, &sx2, &sy2);
					b.x0 = sx; b.y0 = sy; b.x1 = sx2; b.y1 = sy2;
					b.color = map->matrix[y][x].color;
					bresenham_img(&img, &b);
				}
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_destroy_image(mlx, img.img);
}*/

static void	draw_line_helper(t_img *img, int *curr, int *next, int color)
{
	t_bresenham	b;

	b.x0 = curr[0];
	b.y0 = curr[1];
	b.x1 = next[0];
	b.y1 = next[1];
	b.color = color;
	bresenham_img(img, &b);
}

static void	process_map_loops(t_img *img, t_map *map, t_view *v)
{
	int	x;
	int	y;
	int	s[4];

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (!map->matrix[y][x].is_valid)
				continue ;
			project_iso(x, y, map->matrix[y][x].z, v, &s[0], &s[1]);
			if (x + 1 < map->width && map->matrix[y][x + 1].is_valid)
			{
				project_iso(x + 1, y, map->matrix[y][x + 1].z, v, &s[2], &s[3]);
				draw_line_helper(img, s, &s[2], map->matrix[y][x].color);
			}
			if (y + 1 < map->height && map->matrix[y + 1][x].is_valid)
			{
				project_iso(x, y + 1, map->matrix[y + 1][x].z, v, &s[2], &s[3]);
				draw_line_helper(img, s, &s[2], map->matrix[y][x].color);
			}
		}
	}
}

static void	draw_wireframe(void *mlx, void *win, t_map *map, t_view *v)
{
	t_img	img;
		
	img.img = mlx_new_image(mlx, v->win_w, v->win_h);
	if (!img.img)
		return ;
	img.data = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	if (!img.data)
	{
		mlx_destroy_image(mlx, img.img);
		return ;
	}
	process_map_loops(&img, map, v);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_destroy_image(mlx, img.img);
}

void	render_map(void *mlx, void *win, t_map *map)
{
	t_view	v;

	if (!mlx || !win || !map || !map->matrix)
		return ;
	compute_view(map, &v);
	draw_wireframe(mlx, win, map, &v);
}
