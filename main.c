/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:39:14 by asari             #+#    #+#             */
/*   Updated: 2025/12/05 01:12:13 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include "GNL/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"



//GEREKSİZ KÜTÜPHANE KONTROLU SAĞLANACAK
//RENDER MAP DOSYASI NORMA UYGUN HALE GETİRİLECEK
//MAKEFİLE YAZILACAK +?
// .h ifndef
// Ekran ortalamaıyor grafiği


static int	setup_map(t_map *map, char *filename)
{
	int	height;
	int	width;

	if (!check_extension(filename))
		return (0);
	if (!get_map_data(&height, &width, filename))
		return (0);
	if (!fill_map(map, height, width, filename))
		return (0);
	return (1);
}

static int	setup_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (0);
	fdf->win = mlx_new_window(fdf->mlx, 1200, 800, "FDF - 42");
	if (!fdf->win)
	{
		free(fdf->mlx);
		return (0);
	}
	return (1);
}
int close_program(t_fdf *fdf)
{
	if (fdf->map)
		free_matrix(fdf->map);
	if (fdf->mlx)
	{
		if (fdf->win)
			mlx_destroy_window(fdf->mlx, fdf->win);
		mlx_destroy_display(fdf->mlx); 
		free(fdf->mlx);
	}
	exit(0);
	return (0);
}

int handle_input(int keycode, t_fdf *fdf)
{
    if (keycode == 65307)
        close_program(fdf);
    return (0);
}

int main(int argc, char **argv)
{
	t_map	map;
	t_fdf	fdf;

	if (argc != 2)
		return (1);
	if (!setup_map(&map, argv[1]))
		return (1);
	if (!setup_mlx(&fdf))
	{
		free_matrix(&map);
		return (1);
	}
	fdf.map = &map;
	render_map(fdf.mlx, fdf.win, &map);
	mlx_hook(fdf.win, 2, 1L << 0, handle_input, &fdf);
	mlx_hook(fdf.win, 17, 0, close_program, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
