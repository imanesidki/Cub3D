/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:19:45 by isalama           #+#    #+#             */
/*   Updated: 2023/09/16 20:59:42 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_window(t_config *config)
{
    config->mlx = mlx_init();
    config->win = mlx_new_window(config->mlx, 800, 400, "cub3d");
    config->map_data.img = mlx_new_image(config->mlx, 800, 400);
    config->map_data.addr = mlx_get_data_addr(config->map_data.img,
    &config->map_data.bits_per_pixel, &config->map_data.line_length, &config->map_data.endian);
    
    update_map(config);
    locate_player(config);
    
    draw_player(config, config->player.x, config->player.y, to_hex(205, 117, 255));
    
    mlx_hook(config->win, 2, 0, handle_press, config);
    mlx_hook(config->win, 3, 0, key_release, config);
    mlx_loop_hook(config->mlx, draw_minimap, config);
    mlx_put_image_to_window(config->mlx, config->win, config->map_data.img, 0, 0);
    mlx_loop(config->mlx);
}

int main(int argc, char **argv)
{
    t_config    *config;

    config = malloc(sizeof(t_config));
    config->map = malloc(sizeof(char *) * 5); // allocate memory for the map (5 lines)
        
    // this is an experimental map, will change when the map parsing is done
    config->map[0] = "111111111";
    config->map[1] = "1W0000001";
    config->map[2] = "100010001";
    config->map[3] = "100001001";
    config->map[4] = "111111111";
    config->map[5] = NULL;
    
    config->player.up = false;
    config->player.down = false;
    config->player.left = false;
    config->player.right = false;
    
    if (argc != 2) {
        show_error("Error\nEnter a valid map file\n");
        return (1);
    }
    
    validate_map(argv[1], config);
    
    { // this is just for testing purposes
        ft_putstr_fd("Captured configs:\n\n", 1);
        printf("NO Texture: %s\n", config->no_texture);
        printf("SO Texture: %s\n", config->so_texture);
        printf("WE Texture: %s\n", config->we_texture);
        printf("EA Texture: %s\n", config->ea_texture);
        printf("Floor color: %d, %d, %d\n", config->f[0], config->f[1], config->f[2]);
        printf("Ceiling color: %d, %d, %d\n", config->c[0], config->c[1], config->c[2]);
    }
    
    ft_putstr_fd("\nThe game is running...\n", 1);
    init_window(config);
}