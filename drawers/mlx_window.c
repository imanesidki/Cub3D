/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:22:06 by isalama           #+#    #+#             */
/*   Updated: 2023/10/14 17:48:40 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pixel_put(t_config *config, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH || x < 0 || y > HEIGHT || y < 0)
		return ;
	dst = config->map_data.addr + (y * config->map_data.line_length
			+ x * (config->map_data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_textures(t_config *config)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		config->tex[i] = malloc(sizeof(t_textures));
		if (!config->tex[i])
			ft_exit(config, 7);
		config->tex[i]->img = mlx_xpm_file_to_image(config->mlx,
				config->textures[i], &config->tex[i]->width,
				&config->tex[i]->height);
		if (!config->tex[i]->img)
			ft_exit(config, 7);
		config->tex[i]->addr = mlx_get_data_addr(config->tex[i]->img,
				&config->tex[i]->bits_per_pixel,
				&config->tex[i]->line_length, &config->tex[i]->endian);
		if (!config->tex[i]->addr)
			ft_exit(config, 7);
		i++;
	}
}

void	init_window(t_config *config)
{
	config->mlx = mlx_init();
	config->win = mlx_new_window(config->mlx, WIDTH, HEIGHT, "cub3d");
	config->map_data.img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	config->map_data.addr = mlx_get_data_addr(config->map_data.img,
			&config->map_data.bits_per_pixel, &config->map_data.line_length,
			&config->map_data.endian);
	init_textures(config);
	locate_player(config);
	mlx_hook(config->win, 2, 0, handle_press, config);
	mlx_hook(config->win, 3, 0, key_release, config);
	mlx_loop_hook(config->mlx, draw_game, config);
	mlx_put_image_to_window(config->mlx, config->win,
		config->map_data.img, 0, 0);
	mlx_loop(config->mlx);
}
