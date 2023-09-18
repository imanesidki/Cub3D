/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:35:57 by isalama           #+#    #+#             */
/*   Updated: 2023/09/17 18:00:01 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int handle_press(int keycode, t_config *config)
{
    if (keycode == 0)
        config->player.left = true;
    if (keycode == 2)
        config->player.right = true;
    if (keycode == 13)
        config->player.up = true;
    if (keycode == 1)
        config->player.down = true;
    if (keycode == 123)
        config->player.dir_left = true;
    if (keycode == 124)
        config->player.dir_right = true;
    return 0;
}

int key_release(int keycode, t_config *config)
{
    if (keycode == 0)
        config->player.left = false;
    if (keycode == 2)
        config->player.right = false;
    if (keycode == 13)
        config->player.up = false;
    if (keycode == 1)
        config->player.down = false;
    if (keycode == 123)
        config->player.dir_left = false;
    if (keycode == 124)
        config->player.dir_right = false;
        
    return 0;
}

void move_player(t_config *config)
{
    if (config->player.left)
        config->player.x -= 2;
        
    if (config->player.right)
        config->player.x += 2;
        
    if (config->player.up)
        config->player.y -= 2;

    if (config->player.down)
        config->player.y += 2;
        
    if (config->player.dir_left)
        config->player.angle -= 8;
        
    if (config->player.dir_right)
        config->player.angle += 8;
}

void locate_player(t_config *config){
    int i = 0;
    while(config->map[i]){
        int j = 0;
        while(config->map[i][j]){
            if(config->map[i][j] == 'N' || config->map[i][j] == 'S' || config->map[i][j] == 'E' || config->map[i][j] == 'W'){
                config->player.x = j * 32;
                config->player.y = i * 32;
                return;
            }
            j++;
        }
        i++;
    }
}