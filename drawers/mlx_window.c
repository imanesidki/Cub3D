/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:22:06 by isalama           #+#    #+#             */
/*   Updated: 2023/09/18 23:33:16 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_direction_line(t_config *config){
    double player_x = config->player.x;
    double player_y = config->player.y;
    double endX = player_x + 32 * cos(config->player.angle);
    double endY = player_y + 32 * sin(config->player.angle);
    
    double deltaX = endX - player_x;
    double deltaY = endY - player_y;
    
    double steps;
    if (fabs(deltaX) >= fabs(deltaY))
        steps = fabs(deltaX);
    else
        steps = fabs(deltaY);
    
    double Xinc = deltaX / steps;
    double Yinc = deltaY / steps;
    
    double X = player_x;
    double Y = player_y;

    int i = 0;
    while (i <= steps)
    {
        pixel_put(config, X, Y, to_hex(255, 255, 255));
        X += Xinc;
        Y += Yinc;
        i++;
    }

}

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
    
    size = 16 + 10;
    i = x - 10;
    while (i < x + 10)
    {
        j = y - 10;
        while (j < y + 10)
        {
            pixel_put(config, i, j, color);
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