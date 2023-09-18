/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:37:28 by isalama           #+#    #+#             */
/*   Updated: 2023/09/18 17:56:42 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void update_map(t_config *config)
{
    int i = 0;
    while(config->map[i]){
        int j = 0;
        while(config->map[i][j]){
            if(config->map[i][j] == '1')
                draw_tiles(config, j * 32, i * 32, to_hex(config->c[0], config->c[1], config->c[2]));
            else
                draw_tiles(config, j * 32, i * 32, to_hex(config->f[0], config->f[1], config->f[2]));
            j++;
        }
        i++;
    }
}

int draw_minimap(t_config *config){
    mlx_clear_window(config->mlx, config->win);
    mlx_destroy_image(config->mlx, config->map_data.img);
    config->map_data.img = mlx_new_image(config->mlx, 800, 400);
    config->map_data.addr = mlx_get_data_addr(config->map_data.img,
    &config->map_data.bits_per_pixel, &config->map_data.line_length, &config->map_data.endian);
    move_player(config);
    update_map(config);
    draw_player(config, config->player.x, config->player.y, to_hex(255, 92, 92));
    draw_direction_line(config);
    mlx_put_image_to_window(config->mlx, config->win, config->map_data.img, 0, 0);
    return 0;
}