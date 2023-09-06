/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:19:15 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/06 01:51:16 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	is_identifier(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

t_garbage	*get_garbage_collector(void)
{
	static t_garbage	grb;

	return (&grb);
}

void	*ft_malloc(size_t size)
{
	t_garbage	*last;
	void		*allocated;

	allocated = malloc(size);
	if (!allocated)
	{
		write(2, "malloc error!\n", 14);
		exit(1);
	}
	last = get_garbage_collector();
	while (last->next)
		last = last->next;
	last->next = malloc(sizeof(t_garbage));
	if (!last->next)
	{
		write(2, "malloc error!\n", 14);
		exit(1);
	}
	last->next->ptr = allocated;
	last->next->is_freed = 0;
	last->next->next = NULL;
	return (allocated);
}

void	ft_free(void *ptr)
{
	t_garbage	*grb;

	if (!ptr)
		return ;
	grb = get_garbage_collector();
	while (grb)
	{
		if (grb->ptr == ptr)
		{
			if (grb->is_freed == 0)
			{
				free(ptr);
				grb->is_freed = 1;
			}
		}
		grb = grb->next;
	}
}
