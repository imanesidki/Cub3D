/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:19:45 by isalama           #+#    #+#             */
/*   Updated: 2023/09/15 22:02:39 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_window(void)
{
    void    *mlx;
    void    *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 500, 500, "cub3d");
    mlx_loop(mlx);
}

int main(int argc, char **argv)
{
    t_config    *config;

    config = malloc(sizeof(t_config));
    if (!config)
        show_error("Error\nMalloc failed\n");
    if (argc != 2)
    {
        show_error("Error\nEnter a valid map file\n");
        return (1);
    }
    
    validate_map(argv[1], config);
    
    
    ft_putstr_fd("Captured configs:\n\n", 1);
    printf("NO Texture: %s\n", config->no_texture);
    printf("SO Texture: %s\n", config->so_texture);
    printf("WE Texture: %s\n", config->we_texture);
    printf("EA Texture: %s\n", config->ea_texture);
    printf("Floor color: %d, %d, %d\n", config->f[0], config->f[1], config->f[2]);
    printf("Ceiling color: %d, %d, %d\n", config->c[0], config->c[1], config->c[2]);
    
    ft_putstr_fd("\nThe game is running...\n", 1);
    // init_window();
}