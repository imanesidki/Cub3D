/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:16:40 by isalama           #+#    #+#             */
/*   Updated: 2023/09/14 22:30:14 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	int	len_tab(char *str, char c)
{
	int	indexer;
	int	total_words;

	indexer = 0;
	total_words = 0;
	if (ft_strlen(str) == 0)
		return (0);
	if (str[indexer] != c)
		total_words++;
	while (str[indexer])
	{
		if (str[indexer] == c && str[indexer + 1] && str[indexer + 1] != c)
			total_words++;
		indexer++;
	}
	return (total_words);
}

static void	ft_free(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

static char	**ft_return(char **tab, char *s, char c, int total_words)
{
	int		tab_index;
	int		word_start;
	int		word_length;

	tab_index = 0;
	word_start = 0;
	word_length = 0;
	while (tab_index < total_words)
	{
		while (s[word_start] == c)
			word_start++;
		while (s[word_start + word_length] && s[word_start + word_length] != c)
			word_length++;
		tab[tab_index] = ft_substr(s, word_start, word_length);
		if (!tab[tab_index])
		{
			ft_free(tab, tab_index);
			return (NULL);
		}
		word_start += word_length;
		word_length = 0;
		tab_index++;
	}
	tab[tab_index] = NULL;
	return (tab);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		total_words;

	total_words = len_tab(s, c);
	tab = malloc(sizeof(char *) * (total_words + 1));
	if (!tab)
		return (NULL);
	return (ft_return (tab, s, c, total_words));
}
