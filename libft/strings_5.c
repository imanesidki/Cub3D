/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:17:47 by isalama           #+#    #+#             */
/*   Updated: 2023/09/18 15:50:32 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	calculate_start(char *s1, char *set)
{
	int	i;

	i = 0;
	while (ft_strchr(set, s1[i]) != NULL)
		i++;
	return (i);
}

static int	calculate_end(char *s1, char *set)
{
	int	i;

	i = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) != NULL)
		i--;
	return (i);
}

static char	*get_trimmed_str(int start, int size, char *original_str)
{
	int		i;
	int		allocation_index;
	char	*allocation;

	i = 0;
	allocation_index = 0;
	allocation = malloc(size + 1);
	if (!allocation)
		return (NULL);
	while (size > 0)
	{
		allocation[allocation_index] = (char) original_str[start];
		start++;
		allocation_index++;
		size--;
	}
	allocation[allocation_index] = '\0';
	return (allocation);
}

char	*ft_strtrim(char *s1, char *set)
{
	int	start;
	int	end;
	int		true_len;
	int	size_indexer;

	true_len = 0;
	size_indexer = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return ((char *) s1);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	start = calculate_start(s1, set);
	end = calculate_end(s1, set);
	if (start > end)
		return (ft_strdup(""));
	while (size_indexer < ft_strlen(s1))
	{
		if (size_indexer >= start && size_indexer <= end)
			true_len++;
		size_indexer++;
	}
	return (get_trimmed_str(start, true_len, (char *) s1));
}
