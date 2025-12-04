#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_point
{
	int z;
	int color;
    int is_valid;
}	t_point;

typedef struct s_map
{
	int width;
	int height;
	t_point **matrix;
}	t_map;

typedef struct s_view {
    int win_w;
    int win_h;
    float scale;
    float zscale;
    float angle;
    int offset_x;
    int offset_y;
} t_view;

typedef struct s_img {
    void *img;
    char *data;
    int   bpp;
    int   line_len;
    int   endian;
} t_img;

typedef struct s_fdf
{
    void    *mlx;
    void    *win;
    t_map   *map;
}   t_fdf;

typedef struct s_bresenham
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_bresenham;

char	**ft_split(char *s, char c);
void	free_split(char **split);
void	clean_newline(char *line);
void	render_map(void *mlx, void *win, t_map *map);
void	free_split_and_line(char *line, char **split);
int		process_lines(int fd, int *height, int *width);
int		get_map_data(int *height, int *width, char *filename);
int		fill_map(t_map *map, int height, int width, char *filename);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
int		ft_isspace(char c);
int		ft_atoi_hex(char *str);
void 	free_matrix(t_map *map);
void	flush_gnl(int fd);
void	render_map(void *mlx, void *win, t_map *map);
int	check_extension(char *filename);


