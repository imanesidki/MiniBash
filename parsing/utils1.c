/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:35:50 by isidki            #+#    #+#             */
/*   Updated: 2023/09/02 00:43:46 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	char_in_set(char *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
	return ((void *) dst);
}

static int	count_digit(int n)
{
	int	nbr;

	nbr = 0;
	if (n < 0)
		nbr++;
	while (n)
	{
		nbr++;
		n /= 10;
	}
	return (nbr);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;

	nb = n;
	i = count_digit(n);
	if (n == 0)
		return (ft_strdup("0"));
	str = ft_malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	if (nb < 0)
		nb *= -1;
	str[i] = '\0';
	while (--i >= 0)
	{
		str[i] = (nb % 10) + 48;
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
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
	int len1;
	int len2;
	
	if (!s1 || !s2)
		return ;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	write(fd, "minishell: ", 11);
	write(fd, s1, len1);
	write(fd, ": ", 1);
	write(fd, s2, len2);
	write(fd, "\n", 1);
	printf("hna|%d|\n",g_glb.exit_status);
	g_glb.exit_status = i;
}