/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:43:31 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/23 16:22:11 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "cub3d.h"

int		parse_map_file(char *filename, t_cub3d *game);
int		parse_texture_line(t_cub3d *game, char *line);
int		parse_color_line(t_cub3d *cub3d, char *line, int *color);

#endif
