/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 01:48:47 by isidki            #+#    #+#             */
/*   Updated: 2023/09/06 01:49:09 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
		ft_free(str);
	str = NULL;
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
		free(str);
	str = NULL;
}
