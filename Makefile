NAME        = fdf

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

MLX_PATH    = ./minilibx-linux
MLX_LIB     = $(MLX_PATH)/libmlx.a

SRCS        = fill_map.c \
              ft_split.c \
              get_map_data.c \
              main.c \
              render_map.c \
              utils.c \
              utils2.c \
              utils3.c \
              GNL/get_next_line.c \
              GNL/get_next_line_utils.c

OBJS        = $(SRCS:.c=.o)


MLX_FLAGS   = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
INCLUDES    = -I. -I$(MLX_PATH)

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@make -C $(MLX_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Temizlik kuralları
clean:
	rm -f $(OBJS)
	@make clean -C $(MLX_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re