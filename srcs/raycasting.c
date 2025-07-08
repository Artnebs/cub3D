#include "cub3d.h"

void    init_raycasting(t_cub3d *cub3d)
{
    cub3d->player.plane_x = 0.66;
    cub3d->player.plane_y = 0.0;
}

static void draw_vertical_line(t_cub3d *cub3d, int x, int draw_start, int draw_end, int color)
{
    int y;

    y = draw_start;
    while (y < draw_end)
    {
        if (y >= 0 && y < WINDOW_HEIGHT)
            *(int *)(cub3d->data.addr + (y * cub3d->data.line_length + x * (cub3d->data.bits_per_pixel / 8))) = color;
        y++;
    }
}

static void draw_wall_texture(t_cub3d *cub3d, int x, int draw_start, int draw_end,
    double wall_x, int tex_x, int side, int tex_num)
{
    int y;
    int tex_y;
    int color;
    double step;
    double tex_pos;

    step = 1.0 * TEXTURE_HEIGHT / (draw_end - draw_start);
    tex_pos = (draw_start - WINDOW_HEIGHT / 2 + (draw_end - draw_start) / 2) * step;
    
    y = draw_start;
    while (y < draw_end)
    {
        tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
        tex_pos += step;
        
        if (y >= 0 && y < WINDOW_HEIGHT)
        {
            color = get_texture_color(&cub3d->map.textures[tex_num], tex_x, tex_y);
            if (side == 1)
                color = (color >> 1) & 8355711; // Make color darker for y-sides
            *(int *)(cub3d->data.addr + (y * cub3d->data.line_length + x * (cub3d->data.bits_per_pixel / 8))) = color;
        }
        y++;
    }
}

int render_frame(t_cub3d *cub3d)
{
    int x;
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    int hit;
    int side;
    double perp_wall_dist;
    int line_height;
    int draw_start;
    int draw_end;
    double wall_x;
    int tex_x;
    int tex_num;

    x = 0;
    while (x < WINDOW_WIDTH)
    {
        camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
        ray_dir_x = cub3d->player.dir_x + cub3d->player.plane_x * camera_x;
        ray_dir_y = cub3d->player.dir_y + cub3d->player.plane_y * camera_x;

        map_x = (int)cub3d->player.pos_x;
        map_y = (int)cub3d->player.pos_y;

        delta_dist_x = fabs(1 / ray_dir_x);
        delta_dist_y = fabs(1 / ray_dir_y);

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (cub3d->player.pos_x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - cub3d->player.pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (cub3d->player.pos_y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - cub3d->player.pos_y) * delta_dist_y;
        }

        hit = 0;
        while (!hit)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }

            if (cub3d->map.map[map_y][map_x] == '1')
                hit = 1;
        }

        if (side == 0)
            perp_wall_dist = (map_x - cub3d->player.pos_x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - cub3d->player.pos_y + (1 - step_y) / 2) / ray_dir_y;

        line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
        draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_end >= WINDOW_HEIGHT)
            draw_end = WINDOW_HEIGHT - 1;

        if (side == 0)
            wall_x = cub3d->player.pos_y + perp_wall_dist * ray_dir_y;
        else
            wall_x = cub3d->player.pos_x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        tex_x = (int)(wall_x * TEXTURE_WIDTH);
        if (side == 0 && ray_dir_x > 0)
            tex_x = TEXTURE_WIDTH - tex_x - 1;
        if (side == 1 && ray_dir_y < 0)
            tex_x = TEXTURE_WIDTH - tex_x - 1;

        if (side == 0)
            tex_num = (ray_dir_x > 0) ? 2 : 3; // East or West
        else
            tex_num = (ray_dir_y > 0) ? 1 : 0; // South or North

        draw_wall_texture(cub3d, x, draw_start, draw_end, wall_x, tex_x, side, tex_num);
        x++;
    }
    mlx_put_image_to_window(cub3d->data.mlx, cub3d->data.win, cub3d->data.img, 0, 0);
    return (0);
} 