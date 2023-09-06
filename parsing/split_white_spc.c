/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_white_spc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:21:01 by isidki            #+#    #+#             */
/*   Updated: 2023/09/06 01:47:05 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_strings(char *str, char *charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check_separator(str[i], charset))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && !check_separator(str[i], charset))
			i++;
	}
	return (count);
}

int	ft_strlen_sep(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] && !check_separator(str[i], charset))
		i++;
	return (i);
}

char	*ft_word(char *str, char *charset)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_strlen_sep(str, charset);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_white_spc(char *str, char *charset)
{
	char	**strings;
	int		i;
	int		j;

	i = 0;
	j = 0;
	strings = (char **)ft_calloc(sizeof(char *),
			(count_strings(str, charset) + 1));
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check_separator(str[i], charset))
			str++;
		if (str[i] != '\0')
		{
			strings[j] = ft_word(str, charset);
			j++;
		}
		while (str[i] && !check_separator(str[i], charset))
			str++;
	}
	strings[j] = 0;
	return (strings);
}
