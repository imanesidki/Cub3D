/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:22:36 by isalama           #+#    #+#             */
/*   Updated: 2023/10/21 18:50:09 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	to_hex(int r, int g, int b)
{
	unsigned int	hex;

	hex = (r << 16) | (g << 8) | b;
	return (hex);
}

void	invalid_surroundings_error(t_config *config, int i, int j)
{
	if ((i - 1 < 0 || i + 1 >= config->map_height)
		|| j - 1 < 0 || j + 1 >= config->map_width)
	{
		printf("Error\nMap is not valid, invalid surroundings");
		printf(", check map[%d][%d]\n", i, j);
		ft_exit(config, 99);
	}
	if (config->map[i + 1][j] == 'x'
		|| config->map[i - 1][j] == 'x'
		|| config->map[i][j + 1] == 'x'
		|| config->map[i][j - 1] == 'x')
	{
		printf("Error\nMap is not valid, invalid surroundings");
		printf(", check map[%d][%d]\n", i, j);
		ft_exit(config, 99);
	}
}

char	*get_error(int err_code)
{
	if (err_code == 0)
		return ("Error\nInvalid map\n");
	if (err_code == 1)
		return ("Error\nInvalid attributes\n");
	if (err_code == 2)
		return ("Error\nMap not closed\n");
	if (err_code == 3)
		return ("Error\nInvalid textures\n");
	if (err_code == 4)
		return ("Error\nInvalid extension\n");
	if (err_code == 5)
		return ("Error\nMalloc failure\n");
	if (err_code == 6)
		return ("Error\nFailed to open map file\n");
	if (err_code == 7)
		return ("Error\nInvalid player\n");
	if (err_code == 8)
		return ("Error\nInvalid colors\n");
	return (NULL);
}

void	ft_exit(t_config *config, int err)
{
	if (err == 3 || err == 7)
	{
		printf("%s", get_error(err));
		exit(1);
	}
	clear_resources(config);
	if (get_error(err))
		printf("%s", get_error(err));
	exit(1);
}

void	check_valid_map_chars(t_config *config, int i, int j, int *players_size)
{
	if (config->map_tmp[i][j] != 'N' && config->map_tmp[i][j] != 'W'
		&& config->map_tmp[i][j] != 'E'
		&& config->map_tmp[i][j] != 'S'
		&& config->map_tmp[i][j] != ' '
		&& config->map_tmp[i][j] != '1'
		&& config->map_tmp[i][j] != '0')
		ft_exit(config, 0);
	if (config->map_tmp[i][j] == 'N' || config->map_tmp[i][j] == 'W'
		|| config->map_tmp[i][j] == 'E'
		|| config->map_tmp[i][j] == 'S')
		(*players_size)++;
}
