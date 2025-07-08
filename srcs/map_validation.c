#include "cub3d.h"

static int  is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static int  check_map_chars(t_cub3d *cub3d)
{
    int i;
    int j;
    int player_found;

    player_found = 0;
    i = 0;
    while (i < cub3d->map.height)
    {
        j = 0;
        while (j < cub3d->map.width)
        {
            if (cub3d->map.map[i][j] == 'N' || cub3d->map.map[i][j] == 'S' ||
                cub3d->map.map[i][j] == 'E' || cub3d->map.map[i][j] == 'W')
            {
                if (player_found)
                    return (0);
                player_found = 1;
                cub3d->player.pos_x = j + 0.5;
                cub3d->player.pos_y = i + 0.5;
                if (cub3d->map.map[i][j] == 'N')
                {
                    cub3d->player.dir_x = 0;
                    cub3d->player.dir_y = -1;
                }
                else if (cub3d->map.map[i][j] == 'S')
                {
                    cub3d->player.dir_x = 0;
                    cub3d->player.dir_y = 1;
                }
                else if (cub3d->map.map[i][j] == 'E')
                {
                    cub3d->player.dir_x = 1;
                    cub3d->player.dir_y = 0;
                }
                else if (cub3d->map.map[i][j] == 'W')
                {
                    cub3d->player.dir_x = -1;
                    cub3d->player.dir_y = 0;
                }
            }
            else if (!is_valid_char(cub3d->map.map[i][j]))
                return (0);
            j++;
        }
        i++;
    }
    return (player_found);
}

static int  check_walls(t_cub3d *cub3d)
{
    int i;
    int j;

    i = 0;
    while (i < cub3d->map.height)
    {
        j = 0;
        while (j < cub3d->map.width)
        {
            if (cub3d->map.map[i][j] == '0' || cub3d->map.map[i][j] == 'N' ||
                cub3d->map.map[i][j] == 'S' || cub3d->map.map[i][j] == 'E' ||
                cub3d->map.map[i][j] == 'W')
            {
                if (i == 0 || i == cub3d->map.height - 1 || j == 0 ||
                    j == cub3d->map.width - 1)
                    return (0);
                if (cub3d->map.map[i - 1][j] == ' ' || cub3d->map.map[i + 1][j] == ' ' ||
                    cub3d->map.map[i][j - 1] == ' ' || cub3d->map.map[i][j + 1] == ' ')
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int validate_map(t_cub3d *cub3d)
{
    if (!cub3d->map.north_texture || !cub3d->map.south_texture ||
        !cub3d->map.east_texture || !cub3d->map.west_texture)
        return (0);
    
    if (!check_map_chars(cub3d))
        return (0);
    
    if (!check_walls(cub3d))
        return (0);
    
    return (1);
} 