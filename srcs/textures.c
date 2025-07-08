#include "cub3d.h"

static int  load_single_texture(t_cub3d *cub3d, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(cub3d->data.mlx, path,
        &texture->width, &texture->height);
    if (!texture->img)
        return (0);
    
    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
        &texture->line_length, &texture->endian);
    if (!texture->addr)
    {
        mlx_destroy_image(cub3d->data.mlx, texture->img);
        return (0);
    }
    
    if (texture->width != TEXTURE_WIDTH || texture->height != TEXTURE_HEIGHT)
    {
        mlx_destroy_image(cub3d->data.mlx, texture->img);
        return (0);
    }
    
    return (1);
}

int load_textures(t_cub3d *cub3d)
{
    if (!load_single_texture(cub3d, &cub3d->map.textures[0], cub3d->map.north_texture))
        return (0);
    if (!load_single_texture(cub3d, &cub3d->map.textures[1], cub3d->map.south_texture))
        return (0);
    if (!load_single_texture(cub3d, &cub3d->map.textures[2], cub3d->map.east_texture))
        return (0);
    if (!load_single_texture(cub3d, &cub3d->map.textures[3], cub3d->map.west_texture))
        return (0);
    return (1);
}

void    free_textures(t_cub3d *cub3d)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (cub3d->map.textures[i].img)
            mlx_destroy_image(cub3d->data.mlx, cub3d->map.textures[i].img);
        i++;
    }
}

int get_texture_color(t_texture *texture, int x, int y)
{
    int color;
    char    *pixel;

    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return (0);
    
    pixel = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    color = *(int *)pixel;
    return (color);
} 