/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:22:06 by isalama           #+#    #+#             */
/*   Updated: 2023/10/06 16:20:35 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pixel_put(t_config *config, int x, int y, int color)
{
	char	*dst;
    if (x > WIDTH || x < 0 || y > HEIGHT || y < 0)
        return ;
	dst = config->map_data.addr + (y * config->map_data.line_length + x * (config->map_data.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
void    draw_player(t_config *config, int size, int color)
{
    int start_x;
    int start_y;
    start_y = config->player.y - size;
    while (start_y < config->player.y + size)
    {
        start_x = config->player.x - size;
        while (start_x < config->player.x + size)
        {
            if (sqrt(pow(start_x - config->player.x, 2) + pow(start_y - config->player.y, 2)) <= size)
                pixel_put(config, start_x, start_y, color);
            start_x++;
        }
        start_y++;
    }
}

void    init_window(t_config *config)
{
    config->mlx = mlx_init();
    config->win = mlx_new_window(config->mlx, WIDTH, HEIGHT, "cub3d");
    config->map_data.img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
    config->map_data.addr = mlx_get_data_addr(config->map_data.img,
    &config->map_data.bits_per_pixel, &config->map_data.line_length, &config->map_data.endian);
    
    draw_map(config);
    
    locate_player(config);
    draw_player(config, PLAYER_SIZE, to_hex(255, 92, 92));
    
    mlx_hook(config->win, 2, 0, handle_press, config);
    mlx_hook(config->win, 3, 0, key_release, config);
    mlx_loop_hook(config->mlx, draw_minimap, config);
    mlx_put_image_to_window(config->mlx, config->win, config->map_data.img, 0, 0);
    mlx_loop(config->mlx);
}