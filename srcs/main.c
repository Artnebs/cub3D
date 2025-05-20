/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:27:32 by jmader            #+#    #+#             */
/*   Updated: 2025/05/20 15:47:20 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	game.gc.head = NULL;
	if (argc != 2)
		return (printf("Usage: %s <file.cub>\n", argv[0]), 1);
	ft_bzero(&game, sizeof(t_game));
	if (parse_map_file(argv[1], &game) == -1)
		return (1);
	printf("Textures loaded:\n");
	printf("NO: %s\n", game.textures[0].path);
	printf("SO: %s\n", game.textures[1].path);
	printf("EA: %s\n", game.textures[2].path);
	printf("WE: %s\n", game.textures[3].path);
	printf("Floor color: %#06x\n", game.floor_color);
	printf("Ceiling color: %#06x\n", game.ceiling_color);
	gc_free_all(&game.gc);
	return (0);
}
