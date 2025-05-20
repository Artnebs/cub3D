/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:54:53 by anebbou           #+#    #+#             */
/*   Updated: 2025/05/20 18:50:42 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/gc.h"

void	*gc_malloc(t_gc *gc, size_t size)
{
	void	*ptr;
	t_node	*node;

	ptr = malloc(size);
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

void	gc_free_all(t_gc *gc)
{
	t_node	*current;
	t_node	*tmp;

	current = gc->head;
	while (current)
	{
		tmp = current->next;
		free(current->ptr);
		free(current);
		current = tmp;
	}
	gc->head = NULL;
}

char	*gc_strdup(t_gc *gc, const char *s)
{
	size_t	len;
	char	*copy;
	size_t	i;

	len = 0;
	while (s[len])
		len++;
	copy = gc_malloc(gc, len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[len] = '\0';
	return (copy);
}

char	**gc_split(t_gc *gc, const char *s, char c)
{
	size_t	i = 0, j = 0, k = 0, count = 0;
	size_t	l = 0;
	char	**tab;

	// Compte le nombre de mots
	while (s && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	tab = gc_malloc(gc, sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (s && s[i] && j < count)
	{
		while (s[i] && s[i] == c)
			i++;
		k = i;
		while (s[i] && s[i] != c)
			i++;
		tab[j] = gc_malloc(gc, i - k + 1);
		if (!tab[j])
			return (NULL);
		while (l < i - k)
		{
			tab[j][l] = s[k + l];
			l++;
		}
		tab[j][i - k] = '\0';
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
