/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:13:22 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 03:19:41 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *source)
{
	char	*dst;
	int		i;

	i = ft_strlen(source);
	dst = (char *)ft_malloc(i + 1);
	if (!dst)
		return (NULL);
	ft_memcpy((void *)dst, (void *)source, i);
	*(dst + i) = '\0';
	return (dst);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putstr_fd(int fd, char *s)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen (s);
	write (fd, s, len);
}

void	ft_putstring_fd(int fd, char *s1, char *s2, int i)
{
	int	len1;
	int	len2;

	if (!s1 || !s2)
		return ;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	write(fd, "minishell: ", 11);
	write(fd, s1, len1);
	write(fd, ": ", 1);
	write(fd, s2, len2);
	write(fd, "\n", 1);
	g_glb.exit_status = i;
}
