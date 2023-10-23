/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_attributes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:08:11 by isalama           #+#    #+#             */
/*   Updated: 2023/10/23 22:14:09 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
	You may notice that we are checking for textures nullability twice
	and reversed, it is because we're trying to avoid having multiple
	attributes of the same type. e.g.: if NO is already set, exit.
*/
bool	is_noso_textures_valid(t_config *config, int i)
{
	if (ft_strncmp(config->map_tmp[i], "NO ", 3))
	{
		if (config->no_texture)
			ft_exit(config, 1);
		config->no_texture = trim_sp(ft_substr(config->map_tmp[i], 3,
					ft_strlen(config->map_tmp[i]) - 3));
		config->found_attrs++;
		if (!config->no_texture)
			ft_exit(config, 1);
		return (true);
	}
	else if (ft_strncmp(config->map_tmp[i], "SO ", 3))
	{
		if (config->so_texture)
			ft_exit(config, 1);
		config->so_texture = trim_sp(ft_substr(config->map_tmp[i], 3,
					ft_strlen(config->map_tmp[i]) - 3));
		config->found_attrs++;
		if (!config->so_texture)
			ft_exit(config, 1);
		return (true);
	}
	return (false);
}

bool	is_eawe_textures_valid(t_config *config, int i)
{
	if (ft_strncmp(config->map_tmp[i], "EA ", 3))
	{
		if (config->ea_texture)
			ft_exit(config, 1);
		config->ea_texture = trim_sp(ft_substr(config->map_tmp[i],
					3, ft_strlen(config->map_tmp[i]) - 3));
		config->found_attrs++;
		if (!config->ea_texture)
			ft_exit(config, 1);
		return (true);
	}
	else if (ft_strncmp(config->map_tmp[i], "WE ", 3))
	{
		if (config->we_texture)
			ft_exit(config, 1);
		config->we_texture = trim_sp(ft_substr(config->map_tmp[i],
					3, ft_strlen(config->map_tmp[i]) - 3));
		config->found_attrs++;
		if (!config->we_texture)
			ft_exit(config, 1);
		return (true);
	}
	return (false);
}

bool	is_map_colors_valid(t_config *config, int i)
{
	if (ft_strncmp(config->map_tmp[i], "F ", 2))
	{
		if (config->f[0] != -1)
			ft_exit(config, 8);
		if (!is_rgb_valid(trim_sp(ft_substr(config->map_tmp[i], 2, \
			ft_strlen(config->map_tmp[i]) - 2)), config->f, config))
			ft_exit(config, 8);
		config->found_attrs++;
		return (true);
	}
	else if (ft_strncmp(config->map_tmp[i], "C ", 2))
	{
		if (config->c[0] != -1)
			ft_exit(config, 8);
		if (!is_rgb_valid(trim_sp(ft_substr(config->map_tmp[i], 2, \
			ft_strlen(config->map_tmp[i]) - 2)), config->c, config))
			ft_exit(config, 8);
		config->found_attrs++;
		return (true);
	}
	return (false);
}

/*
	Before we set the textures to their respective variables, we start
	checking if the colors are valid so we don't have to allocate anything
	in case of when textures are valid then exit.
*/
void	set_textures_data(t_config *config)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (config->f[i] == -1 || config->c[i] == -1)
			ft_exit(config, 8);
		i++;
	}
	if (!config->no_texture || !config->so_texture
		|| !config->ea_texture || !config->we_texture)
		ft_exit(config, 3);
	config->textures = malloc(sizeof(char *) * 5);
	config->textures[0] = ft_strdup(config->no_texture);
	config->textures[1] = ft_strdup(config->so_texture);
	config->textures[2] = ft_strdup(config->ea_texture);
	config->textures[3] = ft_strdup(config->we_texture);
	config->textures[4] = NULL;
}

/*
	This function will check if the map attributes are correct. If yes, set the
 	value of [config->map_start] to where we stopped so we can skip the attributes
	later to start reading the map.
*/
void	init_map_attrs_validator(t_config *config)
{
	int		i;
	int		j;

	i = 0;
	while (config->map_tmp[i] && allowed_attribute(config->map_tmp[i]))
	{
		if (config->found_attrs < 6)
			config->map_tmp[i] = trim_sp(config->map_tmp[i]);
		else
		{
			j = 0;
			while (is_space(config->map_tmp[i][j]))
				j++;
			if (config->map_tmp[i][j] == '\0')
			{
				i++;
				continue ;
			}
		}
		if (is_attributes_invalid(config, &i))
			break ;
		i++;
	}
	config->map_start = i;
	set_textures_data(config);
}
