/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:14:51 by isalama           #+#    #+#             */
/*   Updated: 2023/10/11 11:58:25 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	to_hex(int r, int g, int b)
{
	unsigned int	hex;

	hex = (r << 16) | (g << 8) | b;
	return (hex);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_config_struct(t_config *config)
{
	if (config->ea_texture)
		free(config->ea_texture);
	if (config->so_texture)
		free(config->so_texture);
	if (config->we_texture)
		free(config->we_texture);
	if (config->no_texture)
		free(config->no_texture);
	free_tab(config->map);
	free_tab(config->map_clone);
	free(config);
}
