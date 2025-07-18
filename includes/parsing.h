/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeanb <jeanb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:43:31 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/18 16:07:58 by jeanb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "gc.h"

struct	s_game;

typedef struct s_texture {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*path;
}	t_texture;

typedef struct s_map {
	char	**grid;
	int		width;
	int		height;
}	t_map;

int		parse_map_file(char *filename, struct s_game *game);
int		parse_texture_line(struct s_game *game, char *line);
int		parse_color_line(t_gc *gc, char *line, int *color);
int		validate_map(char **grid);

#endif
