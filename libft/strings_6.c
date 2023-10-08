/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:58:29 by isalama           #+#    #+#             */
/*   Updated: 2023/10/08 20:10:25 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*trim_sp(char *str)
{
	return (ft_strtrim(str, " \t"));
}

int	ft_atoi_rgb(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (is_space(str[i]))
		i++;
	while (ft_isdigit(str[i]))
	{
		result *= 10;
		result += (str[i] - '0');
		i++;
	}
	if ((str[i] && !ft_isdigit(str[i])))
		return (-1);
	return (result);
}

bool	has_extension(char *filename, char *extension)
{
	int	i;
	int	j;

	i = ft_strlen(filename) - 1;
	j = ft_strlen(extension) - 1;
	while (j >= 0 && i >= 0)
	{
		if (filename[i] != extension[j])
			return (false);
		i--;
		j--;
	}
	return (true);
}
