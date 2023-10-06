/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:19:45 by isalama           #+#    #+#             */
/*   Updated: 2023/10/06 16:56:51 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_variables_rest(t_config *config)
{
    int i = 0;
    while (i < 3)
    {
        config->f[i] = -1;
        config->c[i] = -1;
        i++;
    }
}

void init_variables(t_config *config)
{
    config->player.up = false;
    config->player.down = false;
    config->player.left = false;
    config->player.right = false;
    config->player.dir_left = false;
    config->player.dir_right = false;
    config->ea_texture = NULL;
    config->so_texture = NULL;
    config->we_texture = NULL;
    config->no_texture = NULL;
    config->colors = NULL;
    config->map_start = 0;
    config->player.angle = M_PI_2;
    config->longest_map_line = 0;
}

void leaker(void){
    system("leaks cub3d");
}

int main(int argc, char **argv)
{
    t_config    *config;
    // atexit(leaker);
    config = malloc(sizeof(t_config));
    if (argc != 2)
        ft_exit(config, 0);
    if(!config)
        ft_exit(config, 5);
    init_variables(config);
    init_variables_rest(config);
    validate_map(argv[1], config);
    init_window(config);
}