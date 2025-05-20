/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:43:31 by anebbou           #+#    #+#             */
/*   Updated: 2025/05/20 18:21:25 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "gc.h"

struct	s_game;

typedef struct s_texture {
	char	*path;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
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
