/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:35:57 by isalama           #+#    #+#             */
/*   Updated: 2023/09/16 20:36:38 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int handle_press(int keycode, t_config *config)
{
    if (keycode == 0)
    {
        ft_putstr_fd("Moving left\n", 1);
        config->player.left = true;
    }
    if (keycode == 2)
    {
        ft_putstr_fd("Moving right\n", 1);
        config->player.right = true;
    }
    if (keycode == 13)
    {
        ft_putstr_fd("Moving up\n", 1);
        config->player.up = true;
    }
    if (keycode == 1)
    {
        ft_putstr_fd("Moving down\n", 1);
        config->player.down = true;
    }
    return 0;
}

int key_release(int keycode, t_config *config)
{
    if (keycode == 0)
    {
        ft_putstr_fd("Stop moving left\n", 1);
        config->player.left = false;
    }
    if (keycode == 2)
    {
        ft_putstr_fd("Stop moving right\n", 1);
        config->player.right = false;
    }
    if (keycode == 13)
    {
        ft_putstr_fd("Stop moving up\n", 1);
        config->player.up = false;
    }
    if (keycode == 1)
    {
        ft_putstr_fd("Stop moving down\n", 1);
        config->player.down = false;
    }
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