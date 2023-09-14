/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:23:13 by isalama           #+#    #+#             */
/*   Updated: 2023/09/14 18:15:09 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*allocation;

	i = 0;
	allocation = malloc(ft_strlen(s1) + 1);
	if (!allocation)
		return (NULL);
	while (s1[i] != '\0')
	{
		allocation[i] = s1[i];
		i++;
	}
	allocation[i] = '\0';
	return (allocation);
}

int	ft_strlen(char *s)
{
	int	index;
	
	if(!s)
		return (0);
	index = 0;
	while (s[index] != '\0')
		index++;
	return (index);
}

char	*ft_strchr(char *s, int c)
{
	int	strlen;
	int	i;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	i = 0;
	while (i <= strlen)
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*allocation;
	int		s1_index;
	int		s2_index;

	s1_index = 0;
	s2_index = 0;
	if (!s1)
		s1 = ft_strdup("");
	allocation = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!allocation)
		return (NULL);
	while (s1[s1_index] != '\0')
	{
		allocation[s1_index] = s1[s1_index];
		s1_index++;
	}
	free(s1);
	while (s2[s2_index] != '\0')
		allocation[s1_index++] = s2[s2_index++];
	allocation[s1_index] = '\0';
	if (allocation[0] == '\0')
		return (free(allocation), NULL);
	return (allocation);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*allocation;
	int		i;
	int		true_length;

	i = 0;
	true_length = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (NULL);
	while (s[start + true_length] != '\0' && true_length < len)
		true_length++;
	allocation = malloc(true_length + 1);
	if (!allocation)
		return (NULL);
	while (i < true_length)
	{
		allocation[i] = s[start + i];
		i++;
	}
	allocation[i] = '\0';
	return (allocation);
}
