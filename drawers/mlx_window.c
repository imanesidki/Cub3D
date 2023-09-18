/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:22:06 by isalama           #+#    #+#             */
/*   Updated: 2023/09/17 21:57:02 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pixel_put(t_config *config, int x, int y, int color)
{
	char	*dst;

	dst = config->map_data.addr + (y * config->map_data.line_length + x * (config->map_data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    draw_tiles(t_config *config, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < 32)
    {
        j = 0;
        while (j < 32)
        {
            pixel_put(config, x + i, y + j, color);
            j++;
        }
        i++;
    }
}
void    draw_player(t_config *config, int x, int y, int color)
{
    int i;
    int j;
    int size;
    
    size = 32 / 2 + 10;
    i = size - 10;
    while (i < size)
    {
        j = size - 10;
        while (j < size)
        {
            pixel_put(config, x + i, y + j, color);
            j++;
        }
        i++;
    }
}

void    init_window(t_config *config)
{
    config->mlx = mlx_init();
    config->win = mlx_new_window(config->mlx, 800, 400, "cub3d");
    config->map_data.img = mlx_new_image(config->mlx, 800, 400);
    config->map_data.addr = mlx_get_data_addr(config->map_data.img,
    &config->map_data.bits_per_pixel, &config->map_data.line_length, &config->map_data.endian);
    
    update_map(config);
    locate_player(config);
    
    draw_player(config, config->player.x, config->player.y, to_hex(255, 92, 92));
    
    mlx_hook(config->win, 2, 0, handle_press, config);
    mlx_hook(config->win, 3, 0, key_release, config);
    mlx_loop_hook(config->mlx, draw_minimap, config);
    mlx_put_image_to_window(config->mlx, config->win, config->map_data.img, 0, 0);
    mlx_loop(config->mlx);
}