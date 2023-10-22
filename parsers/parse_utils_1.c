/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:37:28 by isalama           #+#    #+#             */
/*   Updated: 2023/10/22 22:38:00 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
	This is the second part of init_map_file_reader() function.
	Now we can allocate the memory then read the file to save it
	in the map_tmp variable so we can play with it later instead
	of using get_next_line() every time we need to read the map.
*/
void	read_map_file(t_config *config, char *path, int map_size)
{
	int		i;
	int		fd;

	i = 0;
	config->map_tmp = malloc((map_size + 1) * sizeof(char *));
	if (!config->map_tmp)
		ft_exit(config, 5);
	config->map_tmp[map_size] = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit(config, 0);
	while (map_size)
	{
		config->map_tmp[i] = get_next_line(fd);
		map_size--;
		i++;
	}
	close(fd);
}

/*
	This function is splitted into 2 parts:
	The following first part is responsible for caluclating
	the map height (size) so we can allocate the memory for it
	in the second part read_map_file().
*/
void	init_map_file_reader(char *path, t_config *config)
{
	int		map_size;
	int		fd;
	char	*line;

	map_size = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit(config, 6);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		map_size++;
		line = get_next_line(fd);
	}
	close(fd);
	read_map_file(config, path, map_size);
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
