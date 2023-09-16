/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:19:39 by isalama           #+#    #+#             */
/*   Updated: 2023/09/16 22:14:28 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

static int	process_result(char *str, int sign, int position)
{
	unsigned long	result;

	result = 0;
	while (ft_isdigit(str[position]))
	{
		result *= 10;
		result += (str[position] - '0');
		position++;
	}
	return (result * sign);
}

bool	is_space(char str)
{
	if (str)
		return (str == 32 || (str >= 9 && str <= 13));
	return (false);
}

static int	has_sign(char str)
{
	return (str == '-' || str == '+');
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (has_sign(str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (process_result((char *)str, sign, i));
}

bool	has_extension(char *filename, char *extension)
{
	int	i;
	int	j;

	i = ft_strlen(filename) - 1;
	j = ft_strlen(extension) - 1;
	if (filename[i] == '\n')
		i--;
	while (j >= 0)
	{
		if (filename[i] != extension[j]){
			printf("- ❌ Parsing failed, affected line   ---->  %s\n", filename);
			return (false);
		}
		i--;
		j--;
	}
	return (true);
}