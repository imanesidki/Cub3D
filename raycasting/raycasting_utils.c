/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:26:50 by isalama           #+#    #+#             */
/*   Updated: 2023/10/10 21:27:27 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_wall(double x, double y, t_config *config)
{
	int	i;
	int	j;

	i = (int)floor(x / TILE_SIZE);
	j = (int)floor(y / TILE_SIZE);
	if (i < config->map_width && j < config->map_height && j >= 0 && i >= 0)
	{
		if (config->map[j][i] == '1')
			return (true);
	}
	return (false);
}
