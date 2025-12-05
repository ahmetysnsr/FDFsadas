/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:35:02 by asari             #+#    #+#             */
/*   Updated: 2025/12/05 04:45:16 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx-linux/mlx.h"

void	trace_line(t_img *img, t_vector p1, t_vector p2, int color)
{
	t_bresenham	b;

	b.x0 = p1.x;
	b.y0 = p1.y;
	b.x1 = p2.x;
	b.y1 = p2.y;
	b.color = color;
	bresenham_img(img, &b);
}

void	bresenham_img(t_img *img, t_bresenham *b)
{
	int	e2;

	b->dx = my_abs(b->x1 - b->x0);
	b->dy = -my_abs(b->y1 - b->y0);
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

void	process_map_loops(t_img *img, t_map *map, t_view *v)
{
	int			i[2];
	t_vector	curr;

	i[1] = -1;
	while (++i[1] < map->height)
	{
		i[0] = -1;
		while (++i[0] < map->width)
		{
			if (!map->matrix[i[1]][i[0]].is_valid)
				continue ;
			curr = project_iso(i[0], i[1], map->matrix[i[1]][i[0]].z, v);
			if (i[0] + 1 < map->width && map->matrix[i[1]][i[0] + 1].is_valid)
				trace_line(img, curr, project_iso(i[0] + 1, i[1], \
				map->matrix[i[1]][i[0] + 1].z, v), \
				map->matrix[i[1]][i[0]].color);
			if (i[1] + 1 < map->height && map->matrix[i[1] + 1][i[0]].is_valid)
				trace_line(img, curr, project_iso(i[0], i[1] + 1, \
				map->matrix[i[1] + 1][i[0]].z, v), \
				map->matrix[i[1]][i[0]].color);
		}
	}
}

void	draw_wireframe(void *mlx, void *win, t_map *map, t_view *v)
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
