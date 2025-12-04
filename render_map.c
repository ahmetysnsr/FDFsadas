/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:35:02 by asari             #+#    #+#             */
/*   Updated: 2025/12/03 11:35:02 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "fdf.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

static void	project_iso(float x, float y, float z, t_view *v, int *sx, int *sy)
{
	float xr = (x - y) * cosf(v->angle);
	float yr = (x + y) * sinf(v->angle) - z * v->zscale;
	*sx = (int)(xr * v->scale) + v->offset_x;
	*sy = (int)(yr * v->scale) + v->offset_y;
}
static void project_parallel(float x, float y, float z, t_view *v, int *sx, int *sy)
{
	*sx = (int)(x * v->scale) + v->offset_x;
	*sy = (int)(y * v->scale) - (z * v->zscale) + v->offset_y;
}
static void img_put_pixel(t_img *img, int x, int y, int color)
{
	if (x < 0 || y < 0)
		return;
	int bpp = img->bpp / 8;
	int max_x = img->line_len / bpp;
	if (x >= max_x)
		return;
	char *p = img->data + y * img->line_len + x * bpp;
	if (p < img->data)
		return;
	if (p + bpp > img->data + (y + 1) * img->line_len)
		return;
	*(unsigned int *)p = (unsigned int)color;
}

static void bresenham_img(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;

	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		img_put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
    }
}

static void compute_view(const t_map *map, t_view *v)
{
	float base;
	v->win_w = 1200;
	v->win_h = 800;
	base = (map->width > map->height) ? map->width : map->height;
	v->scale = (base == 0) ? 1.0f : (float)(v->win_w * 0.35f) / base;
	v->zscale = 0.25f;
	v->angle = 0.523599f;
	v->offset_x = v->win_w / 2;
	v->offset_y = v->win_h / 2;
}

static void draw_wireframe(void *mlx, void *win, t_map *map, t_view *v)
{
    t_img img;
    img.img = mlx_new_image(mlx, v->win_w, v->win_h);
    img.data = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            int sx, sy;
            project_iso(x, y, map->matrix[y][x].z, v, &sx, &sy);
            if (x + 1 < map->width) {
                int sx2, sy2;
                project_iso(x + 1, y, map->matrix[y][x + 1].z, v, &sx2, &sy2);
                int color = map->matrix[y][x].color;
                bresenham_img(&img, sx, sy, sx2, sy2, color);
            }
            if (y + 1 < map->height) {
                int sx2, sy2;
                project_iso(x, y + 1, map->matrix[y + 1][x].z, v, &sx2, &sy2);
                int color = map->matrix[y][x].color;
                bresenham_img(&img, sx, sy, sx2, sy2, color);
            }
        }
    }
    mlx_put_image_to_window(mlx, win, img.img, 0, 0);
    mlx_destroy_image(mlx, img.img);
}

void	render_map(void *mlx, void *win, t_map *map)
{
    t_view v;

    if (!mlx || !win || !map || !map->matrix)
        return;
    compute_view(map, &v);
    draw_wireframe(mlx, win, map, &v);
}
