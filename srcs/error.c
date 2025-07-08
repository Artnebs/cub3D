#include "cub3d.h"

typedef struct s_garbage
{
    void            *ptr;
    struct s_garbage    *next;
} t_garbage;

void    error_exit(t_cub3d *cub3d, const char *message)
{
    if (cub3d)
    {
        if (cub3d->data.mlx)
        {
            if (cub3d->data.win)
                mlx_destroy_window(cub3d->data.mlx, cub3d->data.win);
            if (cub3d->data.img)
                mlx_destroy_image(cub3d->data.mlx, cub3d->data.img);
            mlx_destroy_display(cub3d->data.mlx);
            free(cub3d->data.mlx);
        }
        free_textures(cub3d);
        gc_cleanup(cub3d);
    }
    write(2, "Error\n", 6);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    exit(1);
}

void    *gc_malloc(t_cub3d *cub3d, size_t size)
void    gc_free(t_cub3d *cub3d, void *ptr)
void    gc_cleanup(t_cub3d *cub3d)

cub3d->data.addr = gc_malloc(cub3d, WINDOW_WIDTH * WINDOW_HEIGHT * 4); 

result = gc_malloc(cub3d, len1 + len2 + 1); 