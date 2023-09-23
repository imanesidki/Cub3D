/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:37:28 by isalama           #+#    #+#             */
/*   Updated: 2023/09/23 17:55:20 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_direction_line(t_config *config, double angle){
    double player_x = config->player.x;
    double player_y = config->player.y;
    double endX = player_x + 32 * cos(angle);
    double endY = player_y + 32 * sin(angle);
    
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
        pixel_put(config, X, Y, to_hex(0, 0, 0));
        X += Xinc;
        Y += Yinc;
        i++;
    }
}

void draw_map(t_config *config)
{
    int i = 0;
    while(config->map[i]){
        int j = 0;
        while(config->map[i][j]){
            if(config->map[i][j] == '1')
                draw_tiles(config, j * 32, i * 32, to_hex(config->c[0], config->c[1], config->c[2]));
            else if(config->map[i][j] == '0')
                draw_tiles(config, j * 32, i * 32, to_hex(config->f[0], config->f[1], config->f[2]));
            j++;
        }
        i++;
    }
}

int draw_minimap(t_config *config){
    

    mlx_clear_window(config->mlx, config->win);
    mlx_destroy_image(config->mlx, config->map_data.img);
    config->map_data.img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
    config->map_data.addr = mlx_get_data_addr(config->map_data.img,
    &config->map_data.bits_per_pixel, &config->map_data.line_length, &config->map_data.endian);
    move_player(config);
    draw_map(config);
    draw_player(config, PLAYER_SIZE, to_hex(255, 92, 92));
    double increment = (VIEW_RANGE * M_PI / 180) / WIDTH;
    double angle = config->player.angle - (VIEW_RANGE * M_PI / 180) / 2;
    while(angle < config->player.angle + (VIEW_RANGE * M_PI / 180) / 2) {
        
        draw_direction_line(config, angle);
        angle += increment;
    }
    
    mlx_put_image_to_window(config->mlx, config->win, config->map_data.img, 0, 0);
    return 0;
}