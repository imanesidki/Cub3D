/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:08:04 by isalama           #+#    #+#             */
/*   Updated: 2023/10/19 21:38:28 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_map(t_config *config)
{
	int	i;
	int	players_size;
	int	j;

	players_size = 0;
	i = config->map_start;
	while (config->map_clone[i])
	{
		if (config->map_clone[i][0] == '\0')
			ft_exit(config, 0);
		j = 0;
		while (config->map_clone[i][j])
		{
			check_chars_inmap(config, i, j, &players_size);
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

void	fill_map_space(t_config *config, int *j)
{
	int	i;
	int	k;

	i = config->map_start;
	k = 0;
	while (config->map_clone[i])
	{
		(*j) = 0;
		while (config->map_clone[i][(*j)])
		{
			if (!is_space(config->map_clone[i][(*j)]))
				config->map[k][(*j)] = config->map_clone[i][(*j)];
			(*j)++;
		}
		k++;
		i++;
	}
}

void	fill_map(t_config *config)
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
	fill_map_space(config, &j);
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

void	validate_map(char *path, t_config *config)
{
	if (!has_extension(path, ".cub"))
		ft_exit(config, 4);
	read_file(path, config);
	parse_map_attrs(config);
	parse_map(config);
	fill_map(config);
	check_surroundings(config);
}
