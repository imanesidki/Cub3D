/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:02:13 by isalama           #+#    #+#             */
/*   Updated: 2023/10/08 20:34:40 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	read_file(char *path, t_config *config)
{
	int		map_size;
	int		fd;
	int		i;
	char	*line;

	i = 0;
	map_size = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(1);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		map_size++;
		line = get_next_line(fd);
	}
	close(fd);
	config->map_clone = malloc((map_size + 1) * sizeof(char *));
	if (!config->map_clone)
		exit(1);
	config->map_clone[map_size] = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit(config, 0);
	while (map_size)
	{
		config->map_clone[i] = get_next_line(fd);
		map_size--;
		i++;
	}
	close(fd);
}

bool	is_rgb_valid(char *str, int *color, t_config *config)
{
	int		i;
	int		j;
	bool	is_valid;

	if (!str || ft_strlen(str) < 5)
		return (free(str), false);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		return (free(str), false);
	config->colors = ft_split(str, ',');
	if (!config->colors)
		return (free(str), false);
	i = 0;
	is_valid = true;
	while (config->colors[i] && i < 3)
	{
		if (ft_atoi_rgb(config->colors[i]) < 0
			|| ft_atoi_rgb(config->colors[i]) > 255)
			is_valid = false;
		color[i] = ft_atoi_rgb(config->colors[i]);
		i++;
	}
	if (is_valid && (config->colors[i] || i != 3))
		is_valid = false;
	free_tab(config->colors);
	free(str);
	return (is_valid);
}

bool	validate_attrs(char *line)
{
	return (!(ft_strlen(line) > 0 && line[0] != 'N'
			&& line[0] != 'W' && line[0] != 'S'
			&& line[0] != 'E' && line[0] != 'C' && line[0] != 'F'));
}

void parse_map_attrs(t_config *config)
{
	int	i;

	i = 0;
	while (config->map_clone[i] && validate_attrs(config->map_clone[i]))
	{
		if (ft_strlen(config->map_clone[i]) > 3)
		{
			if (ft_strncmp(config->map_clone[i], "NO ", 3))
			{
				if (config->no_texture)
					ft_exit(config, 1);
				config->no_texture = trim_sp(ft_substr(config->map_clone[i], 3, ft_strlen(config->map_clone[i]) - 3));
				if (!config->no_texture)
					ft_exit(config, 1);
			}
			else if (ft_strncmp(config->map_clone[i], "SO ", 3))
			{
				if (config->so_texture)
					ft_exit(config, 1);
				config->so_texture = trim_sp(ft_substr(config->map_clone[i], 3, ft_strlen(config->map_clone[i]) - 3));
				if (!config->so_texture)
					ft_exit(config, 1);
			}
			else if (ft_strncmp(config->map_clone[i], "EA ", 3))
			{
				if (config->ea_texture)
					ft_exit(config, 1);
				config->ea_texture = trim_sp(ft_substr(config->map_clone[i], 3, ft_strlen(config->map_clone[i]) - 3));
				if (!config->ea_texture)
					ft_exit(config, 1);
			}
			else if (ft_strncmp(config->map_clone[i], "WE ", 3))
			{
				if (config->we_texture)
					ft_exit(config, 1);
				config->we_texture = trim_sp(ft_substr(config->map_clone[i], 3, ft_strlen(config->map_clone[i]) - 3));
				if (!config->we_texture)
					ft_exit(config, 1);
			}
			else if (ft_strncmp(config->map_clone[i], "F ", 2))
			{
				if (!is_rgb_valid(trim_sp(ft_substr(config->map_clone[i], 2, ft_strlen(config->map_clone[i]) - 2)), config->f, config))
					ft_exit(config, 1);
			}
			else if (ft_strncmp(config->map_clone[i], "C ", 2))
			{
				if (!is_rgb_valid(trim_sp(ft_substr(config->map_clone[i], 2, ft_strlen(config->map_clone[i]) - 2)), config->c, config))
					ft_exit(config, 1);
			}
		}
		i++;
	}
	config->map_start = i;
	if (!config->no_texture || !config->so_texture || !config->ea_texture || !config->we_texture)
		ft_exit(config, 1);
	i = 0;
	while (i < 3)
	{
		if (config->f[i] == -1 || config->c[i] == -1)
			ft_exit(config, 1);
		i++;
	}
}

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
			if (config->map_clone[i][j] != 'N' && config->map_clone[i][j] != 'W' && config->map_clone[i][j] != 'E' &&
				config->map_clone[i][j] != 'S' && config->map_clone[i][j] != ' ' && config->map_clone[i][j] != '1' && config->map_clone[i][j] != '0')
				ft_exit(config, 0);
			if (config->map_clone[i][j] == 'N' || config->map_clone[i][j] == 'W' || config->map_clone[i][j] == 'E' || config->map_clone[i][j] == 'S')
				players_size++;
			j++;
		}
		if (j > config->longest_map_line)
			config->longest_map_line = j;
		i++;
	}
	if (players_size != 1)
		ft_exit(config, 0);
	config->map_end = i;
}

void	fill_map(t_config *config)
{
	int	j;
	int	i;
	int	i2;

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
	i = config->map_start;
	i2 = 0;
	while (config->map_clone[i])
	{
		j = 0;
		while (config->map_clone[i][j])
		{
			if (!is_space(config->map_clone[i][j]))
				config->map[i2][j] = config->map_clone[i][j];
			j++;
		}
		i2++;
		i++;
	}
	free_tab(config->map_clone);
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
			if (config->map[i][j] == '0' || config->map[i][j] == 'N' || config->map[i][j] == 'S'
				|| config->map[i][j] == 'E' || config->map[i][j] == 'W')
			{
				if ((i - 1 < 0 || i + 1 >= config->map_height) || j - 1 < 0 || j + 1 >= config->map_width)
				{
					printf("Error\nMap is not valid, invalid surroundings, check map[%d][%d]\n", i, j);
					ft_exit(config, 99);
				}
				if (config->map[i + 1][j] == 'x' || config->map[i - 1][j] == 'x' || config->map[i][j + 1] == 'x' || config->map[i][j - 1] == 'x')
				{
					printf("Error\nMap is not valid, invalid surroundings, check map[%d][%d]\n", i, j);
					ft_exit(config, 99);
				}
			}
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
