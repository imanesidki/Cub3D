/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:36:21 by isalama           #+#    #+#             */
/*   Updated: 2023/10/21 16:39:21 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
	Here, we're checking for 3 things:
	1. If there's an empty line inside the map, exit.
	2. If the map contains characters other than the allowed ones, exit.
	3. If the player is assigned more than once, exit.
	
	We also save both the longest map line, and the map end index
	for allocation purposes.
*/
void	init_map_parser(t_config *config)
{
	int	i;
	int	players_size;
	int	j;

	players_size = 0;
	i = config->map_start;
	while (config->map_tmp[i])
	{
		if (config->map_tmp[i][0] == '\0')
			ft_exit(config, 0);
		j = 0;
		while (config->map_tmp[i][j])
		{
			check_valid_map_chars(config, i, j, &players_size);
			j++;
		}
		if (j > config->longest_map_line)
			config->longest_map_line = j;
		i++;
	}
	if (players_size != 1)
		ft_exit(config, 7);
	config->map_end = i;
}

void	fill_map_spaces(t_config *config, int *j)
{
	int	i;
	int	k;

	i = config->map_start;
	k = 0;
	while (config->map_tmp[i])
	{
		(*j) = 0;
		while (config->map_tmp[i][(*j)])
		{
			if (!is_space(config->map_tmp[i][(*j)]))
				config->map[k][(*j)] = config->map_tmp[i][(*j)];
			(*j)++;
		}
		k++;
		i++;
	}
}

void	init_map_filler(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	config->map_height = config->map_end - config->map_start;
	config->map_width = config->longest_map_line;
	config->map = malloc((config->map_height + 1) * sizeof(char *));
	if (!config->map)
		ft_exit(config, 5);
	config->map[config->map_height] = NULL;
	while (i < config->map_height)
	{
		config->map[i] = malloc((config->longest_map_line + 1) * sizeof(char));
		if (!config->map[i])
			ft_exit(config, 5);
		j = 0;
		while (j < config->longest_map_line)
		{
			config->map[i][j] = 'x';
			j++;
		}
		config->map[i][j] = '\0';
		i++;
	}
	fill_map_spaces(config, &j);
}

void	check_surroundings(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == '0' || config->map[i][j] == 'N' ||
				config->map[i][j] == 'S'
				|| config->map[i][j] == 'E' || config->map[i][j] == 'W')
				invalid_surroundings_error(config, i, j);
			j++;
		}
		i++;
	}
}

void	init_map_validator(char *path, t_config *config)
{
	if (!has_extension(path, ".cub"))
		ft_exit(config, 4);
	init_map_file_reader(path, config);
	init_map_attrs_validator(config);
	init_map_parser(config);
	init_map_filler(config);
	check_surroundings(config);
}
