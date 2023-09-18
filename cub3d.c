/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:19:45 by isalama           #+#    #+#             */
/*   Updated: 2023/09/18 18:09:07 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_config    *config;
    
    config = malloc(sizeof(t_config));
    config->map = malloc(sizeof(char *) * 11); // allocate memory for the map (5 lines)
        
    // this is an experimental map, will change when the map parsing is done
    config->map[0] = "1111111111111111111111";
    config->map[1] = "1000000000000000000001";
    config->map[2] = "1000000000W00000000001";
    config->map[3] = "1000000000000000000001";
    config->map[4] = "1000000100000000000001";
    config->map[5] = "1000000000000000000001";
    config->map[6] = "1000000000000000000001";
    config->map[7] = "1000000001000000000001";
    config->map[8] = "1000000000000000000001";
    config->map[9] = "1000000000000000000001";
    config->map[10] = "1111111111111111111111";
    config->map[11] = NULL;
    
    config->player.up = false;
    config->player.down = false;
    config->player.left = false;
    config->player.right = false;
    config->player.dir_left = false;
    config->player.dir_right = false;
    config->player.angle = 90 * (M_PI / 180);
    
    if (argc != 2) {
        show_error("Error\nEnter a valid map file\n");
        return (1);
    }
    
    validate_map(argv[1], config);
    
    { // this is just for testing purposes
        ft_putstr_fd("Captured configs:\n\n", 1);
        printf("NO Texture: [%s]\n", config->no_texture);
        printf("SO Texture: [%s]\n", config->so_texture);
        printf("WE Texture: [%s]\n", config->we_texture);
        printf("EA Texture: [%s]\n", config->ea_texture);
        printf("Floor color: %d, %d, %d\n", config->f[0], config->f[1], config->f[2]);
        printf("Ceiling color: %d, %d, %d\n", config->c[0], config->c[1], config->c[2]);
    }
    
    ft_putstr_fd("\nThe game is running...\n", 1);
    init_window(config);
}