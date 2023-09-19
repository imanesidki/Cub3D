/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:19:45 by isalama           #+#    #+#             */
/*   Updated: 2023/09/19 20:28:06 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_config    *config;
    
    config = malloc(sizeof(t_config));
        
    config->player.up = false;
    config->player.down = false;
    config->player.left = false;
    config->player.right = false;
    config->player.dir_left = false;
    config->player.dir_right = false;
    config->player.angle = 0;
    if (argc != 2) {
        show_error("Error\nEnter a valid map file\n");
        return (1);
    }
    validate_map(argv[1], config);
    init_window(config);
}