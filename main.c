/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:39:14 by asari             #+#    #+#             */
/*   Updated: 2025/12/04 16:31:18 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include "GNL/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"



//ESC VE X İÇİN SAFE ÇIKIŞ VERİLMESİ GEREKİYOR MEMORY FREELER VS. +
//GEREKSİZ KÜTÜPHANE KONTROLU SAĞLANACAK
//RENDER MAP DOSYASI NORMA UYGUN HALE GETİRİLECEK
//MAKEFİLE YAZILACAK +?
// MLX NULL KONTROL
// COS SİN 
// DOSYA ALINAN DOSYA İSMİ .fdf ile bitmesi gerekiyor. +
// .h ifndef
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
    t_map   map;
    t_fdf   fdf;
    int     height;
    int     width;

    if (argc != 2)
        return (1);
    if (!check_extension(argv[1]))
		return (1);
    if (!get_map_data(&height, &width, argv[1]))
        return (1);
    if (!fill_map(&map, height, width, argv[1]))//burada hata alırsa üst taraftan kaynaklı memory leak
        return (1);
    fdf.mlx = mlx_init();
    if (!fdf.mlx)
    {
        free_matrix(&map);
        return (1);
    }
    fdf.win = mlx_new_window(fdf.mlx, 1200, 800, "FDF - 42");
    if (!fdf.win)
    {
        free_matrix(&map);
        free(fdf.mlx);
        return (1);
    }
    fdf.map = &map;
    render_map(fdf.mlx, fdf.win, &map);
    mlx_hook(fdf.win, 2, 1L << 0, handle_input, &fdf);
    mlx_hook(fdf.win, 17, 0, close_program, &fdf);
    mlx_loop(fdf.mlx);
    return (0);
}
