/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 22:48:26 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/28 22:48:30 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	**free_table(char **tab, int i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
	return (NULL);
}

static char	*push(char *str, int begin, int end)
{
	int		i;
	char	*temp;

	i = 0;
	temp = malloc(sizeof(char) * (end - begin + 1));
	if (!temp)
		return (NULL);
	while (begin < end)
	{
		temp[i] = str[begin];
		i++;
		begin++;
	}
	temp[i] = '\0';
	return (temp);
}

static int	sep(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count_words(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (!sep(str[i], charset)
			&& (sep(str[i + 1], charset) || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split_set(char *str, char *charset)
{
	char	**ret;
	int		begin;
	int		word;
	int		i;

	ret = malloc(sizeof(char *) * (count_words(str, charset) + 1));
	if (!ret)
		return (NULL);
	i = -1;
	word = -1;
	while (str[++i] != '\0')
	{
		if (!sep(str[i], charset)
			&& (i == 0 || sep(str[i - 1], charset)))
			begin = i;
		if ((i != 0 && sep(str[i], charset) && !sep(str[i - 1], charset))
			|| (str[i + 1] == '\0' && !sep(str[i], charset)))
			ret[++word] = push(str, begin, i + (!sep(str[i], charset)));
		if (word != -1 && !ret[word])
			return (free_table(ret, word));
	}
	ret[++word] = 0;
	return (ret);
}
