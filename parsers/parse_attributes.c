/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_attributes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:08:11 by isalama           #+#    #+#             */
/*   Updated: 2023/10/18 21:17:07 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	validate_textures_1(t_config *config, int i)
{
	if (ft_strncmp(config->map_clone[i], "NO ", 3))
	{
		if (config->no_texture)
			ft_exit(config, 1);
		config->no_texture = trim_sp(ft_substr(config->map_clone[i], 3,
					ft_strlen(config->map_clone[i]) - 3));
		if (!config->no_texture)
			ft_exit(config, 1);
		return (true);
	}
	else if (ft_strncmp(config->map_clone[i], "SO ", 3))
	{
		if (config->so_texture)
			ft_exit(config, 1);
		config->so_texture = trim_sp(ft_substr(config->map_clone[i], 3,
					ft_strlen(config->map_clone[i]) - 3));
		if (!config->so_texture)
			ft_exit(config, 1);
		return (true);
	}
	return (false);
}

bool	validate_textures_2(t_config *config, int i)
{
	if (ft_strncmp(config->map_clone[i], "EA ", 3))
	{
		if (config->ea_texture)
			ft_exit(config, 1);
		config->ea_texture = trim_sp(ft_substr(config->map_clone[i],
					3, ft_strlen(config->map_clone[i]) - 3));
		if (!config->ea_texture)
			ft_exit(config, 1);
		return (true);
	}
	else if (ft_strncmp(config->map_clone[i], "WE ", 3))
	{
		if (config->we_texture)
			ft_exit(config, 1);
		config->we_texture = trim_sp(ft_substr(config->map_clone[i],
					3, ft_strlen(config->map_clone[i]) - 3));
		if (!config->we_texture)
			ft_exit(config, 1);
		return (true);
	}
	return (false);
}

bool	validate_textures_3(t_config *config, int i)
{
	if (ft_strncmp(config->map_clone[i], "F ", 2))
	{
		if (config->f[0] != -1)
			ft_exit(config, 1);
		if (!is_rgb_valid(trim_sp(ft_substr(config->map_clone[i], 2, \
			ft_strlen(config->map_clone[i]) - 2)), config->f, config))
			ft_exit(config, 1);
		return (true);
	}
	else if (ft_strncmp(config->map_clone[i], "C ", 2))
	{
		if (config->c[0] != -1)
			ft_exit(config, 1);
		if (!is_rgb_valid(trim_sp(ft_substr(config->map_clone[i], 2, \
			ft_strlen(config->map_clone[i]) - 2)), config->c, config))
			ft_exit(config, 1);
		return (true);
	}
	return (false);
}

void	set_textures_data(t_config *config)
{
	int	i;

	i = 0;
	if (!config->no_texture || !config->so_texture
		|| !config->ea_texture || !config->we_texture)
		ft_exit(config, 3);
	config->textures = malloc(sizeof(char *) * 5);
	config->textures[0] = ft_strdup(config->no_texture);
	config->textures[1] = ft_strdup(config->so_texture);
	config->textures[2] = ft_strdup(config->ea_texture);
	config->textures[3] = ft_strdup(config->we_texture);
	config->textures[4] = NULL;
	while (i < 3)
	{
		if (config->f[i] == -1 || config->c[i] == -1)
			ft_exit(config, 3);
		i++;
	}
}

void	parse_map_attrs(t_config *config)
{
	int	i;

	i = 0;
	while (config->map_clone[i] && validate_attrs(config->map_clone[i]))
	{
		if (ft_strlen(config->map_clone[i]) > 3)
		{
			if (!validate_textures_1(config, i)
				&& !validate_textures_2(config, i)
				&& !validate_textures_3(config, i))
				printf("Error baby!\n");
		}
		i++;
	}
	config->map_start = i;
	set_textures_data(config);
}
