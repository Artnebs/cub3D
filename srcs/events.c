#include "cub3d.h"

int handle_keypress(int keycode, t_cub3d *cub3d)
{
    double old_dir_x;
    double old_plane_x;

    if (keycode == 65307) // ESC
        handle_window_close(cub3d);
    else if (keycode == 119) // W
    {
        if (cub3d->map.map[(int)(cub3d->player.pos_y + cub3d->player.dir_y * MOVE_SPEED)]
            [(int)(cub3d->player.pos_x + cub3d->player.dir_x * MOVE_SPEED)] != '1')
        {
            cub3d->player.pos_x += cub3d->player.dir_x * MOVE_SPEED;
            cub3d->player.pos_y += cub3d->player.dir_y * MOVE_SPEED;
        }
    }
    else if (keycode == 115) // S
    {
        if (cub3d->map.map[(int)(cub3d->player.pos_y - cub3d->player.dir_y * MOVE_SPEED)]
            [(int)(cub3d->player.pos_x - cub3d->player.dir_x * MOVE_SPEED)] != '1')
        {
            cub3d->player.pos_x -= cub3d->player.dir_x * MOVE_SPEED;
            cub3d->player.pos_y -= cub3d->player.dir_y * MOVE_SPEED;
        }
    }
    else if (keycode == 97) // A
    {
        if (cub3d->map.map[(int)(cub3d->player.pos_y - cub3d->player.dir_x * MOVE_SPEED)]
            [(int)(cub3d->player.pos_x + cub3d->player.dir_y * MOVE_SPEED)] != '1')
        {
            cub3d->player.pos_x += cub3d->player.dir_y * MOVE_SPEED;
            cub3d->player.pos_y -= cub3d->player.dir_x * MOVE_SPEED;
        }
    }
    else if (keycode == 100) // D
    {
        if (cub3d->map.map[(int)(cub3d->player.pos_y + cub3d->player.dir_x * MOVE_SPEED)]
            [(int)(cub3d->player.pos_x - cub3d->player.dir_y * MOVE_SPEED)] != '1')
        {
            cub3d->player.pos_x -= cub3d->player.dir_y * MOVE_SPEED;
            cub3d->player.pos_y += cub3d->player.dir_x * MOVE_SPEED;
        }
    }
    else if (keycode == 65361) // Left arrow
    {
        old_dir_x = cub3d->player.dir_x;
        cub3d->player.dir_x = cub3d->player.dir_x * cos(ROTATION_SPEED) -
            cub3d->player.dir_y * sin(ROTATION_SPEED);
        cub3d->player.dir_y = old_dir_x * sin(ROTATION_SPEED) +
            cub3d->player.dir_y * cos(ROTATION_SPEED);
        old_plane_x = cub3d->player.plane_x;
        cub3d->player.plane_x = cub3d->player.plane_x * cos(ROTATION_SPEED) -
            cub3d->player.plane_y * sin(ROTATION_SPEED);
        cub3d->player.plane_y = old_plane_x * sin(ROTATION_SPEED) +
            cub3d->player.plane_y * cos(ROTATION_SPEED);
    }
    else if (keycode == 65363) // Right arrow
    {
        old_dir_x = cub3d->player.dir_x;
        cub3d->player.dir_x = cub3d->player.dir_x * cos(-ROTATION_SPEED) -
            cub3d->player.dir_y * sin(-ROTATION_SPEED);
        cub3d->player.dir_y = old_dir_x * sin(-ROTATION_SPEED) +
            cub3d->player.dir_y * cos(-ROTATION_SPEED);
        old_plane_x = cub3d->player.plane_x;
        cub3d->player.plane_x = cub3d->player.plane_x * cos(-ROTATION_SPEED) -
            cub3d->player.plane_y * sin(-ROTATION_SPEED);
        cub3d->player.plane_y = old_plane_x * sin(-ROTATION_SPEED) +
            cub3d->player.plane_y * cos(-ROTATION_SPEED);
    }
    return (0);
}

int handle_window_close(t_cub3d *cub3d)
{
    mlx_destroy_window(cub3d->data.mlx, cub3d->data.win);
    mlx_destroy_display(cub3d->data.mlx);
    free(cub3d->data.mlx);
    gc_cleanup(cub3d);
    exit(0);
    return (0);
} 