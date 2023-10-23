/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:37:38 by isalama           #+#    #+#             */
/*   Updated: 2023/10/23 22:28:37 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_attributes_invalid(t_config *config, int *i)
{
	return (ft_strlen(config->map_tmp[*i]) > 3
		&& !is_noso_textures_valid(config, *i)
		&& !is_eawe_textures_valid(config, *i)
		&& !is_map_colors_valid(config, *i));
}

/*
	Allow only the following characters, and make sure we allow new lines as well
	to support multi-line attributes.
*/
bool	allowed_attribute(char *line, t_config *config)
{
	while (is_space(*line))
		(line)++;
	if ((line[0] == 'C' && config->c[0] != -1)
		|| (line[0] == 'F' && config->f[0] != -1)
		|| (line[0] == 'N' && config->no_texture)
		|| (line[0] == 'S' && config->so_texture)
		|| (line[0] == 'W' && config->we_texture)
		|| (line[0] == 'E' && config->ea_texture))
		return (false);
	return (ft_strlen(line) <= 0 || line[0] == 'N' || line[0] == 'W' \
	|| line[0] == 'S' || line[0] == 'E' || line[0] == 'C' \
	|| line[0] == 'F');
}
