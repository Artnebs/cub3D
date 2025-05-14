/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:54:53 by anebbou           #+#    #+#             */
/*   Updated: 2025/05/14 18:57:44 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gc.h"

void *gc_malloc(t_gc *gc, size_t size)
{
	void *ptr = malloc(size);
	t_node *node;

	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_node));
	if (!node)
		return (free(ptr), NULL);
	node->ptr = ptr;
	node->next = gc->head;
	gc->head = node;
	return (ptr);
}

void gc_free_all(t_gc *gc)
{
	t_node *current = gc->head;
	t_node *tmp;

	while (current)
	{
		tmp = current->next;
		free(current->ptr);
		free(current);
		current = tmp;
	}
	gc->head = NULL;
}

char *gc_strdup(t_gc *gc, const char *s)
{
	size_t len = 0;
	char *copy;

	while (s[len])
		len++;
	copy = gc_malloc(gc, len + 1);
	if (!copy)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		copy[i] = s[i];
	copy[len] = '\0';
	return (copy);
}
