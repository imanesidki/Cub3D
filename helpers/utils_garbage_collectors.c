/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_garbage_collectors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:14:51 by isalama           #+#    #+#             */
/*   Updated: 2023/10/15 18:45:35 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	free_textures_struct(t_config *config)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(config->tex[i]);
		i++;
	}
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
	free_tab(config->textures);
	free_textures_struct(config);
	free(config);
}
