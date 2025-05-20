/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:39:29 by anebbou           #+#    #+#             */
/*   Updated: 2025/05/20 18:20:53 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"
# include "parsing.h"
# include "player.h"
# include "raycast.h"
# include "gc.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_img		frame;
	t_map		map;
	t_player	player;
	t_texture	textures[4]; // 0:N 1:S 2:E 3:W
	int			floor_color;
	int			ceiling_color;
	t_gc		gc;
}	t_game;

#endif
