/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:49:08 by isalama           #+#    #+#             */
/*   Updated: 2023/10/18 21:19:49 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	read_file_rest(t_config *config, char *path, int map_size)
{
	int		i;
	int		fd;

	i = 0;
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

void	read_file(char *path, t_config *config)
{
	int		map_size;
	int		fd;
	char	*line;

	map_size = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error:\nFailed to open map file.\n");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		map_size++;
		line = get_next_line(fd);
	}
	close(fd);
	read_file_rest(config, path, map_size);
}

bool	is_rgb_string_valid(char *str, t_config *config)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	if (!str || ft_strlen(str) < 5)
		return (free(str), false);
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
		return (free(str), false);
	config->colors = ft_split(str, ',');
	if (!config->colors)
		return (free(str), false);
	return (true);
}

bool	is_rgb_valid(char *str, int *color, t_config *config)
{
	bool	is_valid;
	int		i;

	is_valid = true;
	i = 0;
	if (!is_rgb_string_valid(str, config))
		return (false);
	while (i < 3 && config->colors[i])
	{
		config->colors[i] = trim_sp(config->colors[i]);
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
