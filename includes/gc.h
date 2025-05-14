/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:54:21 by anebbou           #+#    #+#             */
/*   Updated: 2025/05/14 18:54:26 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>

typedef struct s_node
{
	void			*ptr;
	struct s_node	*next;
}	t_node;

typedef struct s_gc
{
	t_node	*head;
}	t_gc;

void	*gc_malloc(t_gc *gc, size_t size);
void	gc_free_all(t_gc *gc);
char	*gc_strdup(t_gc *gc, const char *s);
char	**gc_split(t_gc *gc, const char *s, char c);

#endif
