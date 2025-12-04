/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:39:14 by asari             #+#    #+#             */
/*   Updated: 2025/12/04 00:41:28 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include "GNL/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"



//RENK KODLARI KONTROL EDİLECEK DOĞRU RENK KODLARI VERİLİYOR MU?
//ESC VE X İÇİN SAFE ÇIKIŞ VERİLMESİ GEREKİYOR MEMORY FREELER VS.
//GEREKSİZ KÜTÜPHANE KONTROLU SAĞLANACAK
//RENDER MAP DOSYASI NORMA UYGUN HALE GETİRİLECEK
//NOKTALAR ARASI ÇİZGİ ÇEKERKEN SOL VE ALT NOKTALARDA RENK KARMAŞASI !?
//MAKEFİLE YAZILACAK
int main(int argc, char **argv)
{
    t_map   map;
    int     height;
    int     width;

    if (argc != 2)
        return (1);
    if (!get_map_data(&height, &width, argv[1]))
        return (1);
    if (!fill_map(&map, height, width, argv[1]))
        return (1);
    void *mlx = mlx_init();
    if (!mlx) {
        free_matrix(&map);
        return (1);
    }
    void *win = mlx_new_window(mlx, 1200, 800, "FDF");
    if (!win)
	{
        free_matrix(&map);
        free(mlx);
        return (1);
    }
    render_map(mlx, win, &map);
    mlx_key_hook(win, (int (*)(int, void *))NULL, NULL);
    mlx_hook(win, 17, 0, (int (*)(void *))NULL, NULL);
    mlx_loop(mlx);
    free_matrix(&map);
    return 0;
}
