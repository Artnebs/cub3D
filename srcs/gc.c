/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:25 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/23 17:08:30 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*gc_malloc(t_cub3d *cub3d, size_t size)
{
	void		*ptr;
	t_garbage	*new;

	if (!cub3d)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		error_exit(cub3d, "Memory allocation failed");
	new = malloc(sizeof(t_garbage));
	if (!new)
	{
		free(ptr);
		error_exit(cub3d, "Memory allocation failed");
	}
	new->ptr = ptr;
	new->next = cub3d->garbage;
	cub3d->garbage = new;
	return (ptr);
}

void	gc_free(t_cub3d *cub3d, void *ptr)
{
	t_garbage	*current;
	t_garbage	*prev;

	if (!ptr || !cub3d)
		return ;
	current = cub3d->garbage;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				cub3d->garbage = current->next;
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	gc_cleanup(t_cub3d *cub3d)
{
	t_garbage	*current;
	t_garbage	*next;

	if (!cub3d)
		return ;
	current = cub3d->garbage;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	cub3d->garbage = NULL;
}
