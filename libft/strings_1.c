/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:23:16 by isalama           #+#    #+#             */
/*   Updated: 2023/10/08 20:08:51 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		write(fd, &str[i++], 1);
}

bool	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	if (s1 && s2 && s1[i] != s2[i])
		return (false);
	return (true);
}

bool	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	if (s1[i] != s2[i] && i < n)
		return (false);
	return (true);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char) c)
		{
			return ((char *) &s[i]);
		}
		i--;
	}
	return (NULL);
}
