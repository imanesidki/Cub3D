/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:35:57 by isalama           #+#    #+#             */
/*   Updated: 2023/09/19 22:35:04 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int handle_press(int keycode, t_config *config)
{
	if (keycode == 0)
		config->player.left = true;
	else if (keycode == 2)
		config->player.right = true;
	else if (keycode == 13)
		config->player.up = true;
	else if (keycode == 1)
		config->player.down = true;
	else if (keycode == 123)
		config->player.dir_left = true;
	else if (keycode == 124)
		config->player.dir_right = true;
	else if (keycode == 53)
		exit(0);
	return 0;
}

int key_release(int keycode, t_config *config)
{
	if (keycode == 0)
		config->player.left = false;
	else if (keycode == 2)
		config->player.right = false;
	if (keycode == W_KEY)
		config->player.up = false;
	else if (keycode == S_KEY)
		config->player.down = false;
	else if (keycode == LEFT_ARROW)
		config->player.dir_left = false;
	else if (keycode == RIGHT_ARROW)
		config->player.dir_right = false;
	return 0;
}

void move_player(t_config *config)
{
	double new_x;
	double new_y;
	if (config->player.left){
		new_x = config->player.x - cos(config->player.angle + (M_PI / 2)) * PLAYER_SPEED;
		new_y = config->player.y - sin(config->player.angle + (M_PI / 2)) * PLAYER_SPEED;
		if (config->map[(int)(new_y / 32)][(int)(new_x / 32)] != '1')
		{
			config->player.x = new_x;
			config->player.y = new_y;
		}
	}
	if (config->player.right)
	{
		new_x = config->player.x + cos(config->player.angle + (M_PI / 2)) * PLAYER_SPEED;
		new_y = config->player.y + sin(config->player.angle + (M_PI / 2)) * PLAYER_SPEED;
		if (config->map[(int)(new_y / 32)][(int)(new_x / 32)] != '1')
		{
			config->player.x = new_x;
			config->player.y = new_y;
		}
	}
	if (config->player.up)
	{
		new_x = config->player.x + cos(config->player.angle) * PLAYER_SPEED;
		new_y = config->player.y + sin(config->player.angle) * PLAYER_SPEED;
		if (config->map[(int)(new_y / 32)][(int)(new_x / 32)] != '1')
		{
			config->player.x = new_x;
			config->player.y = new_y;
		}
	}
	if (config->player.down)
	{
		new_x = config->player.x - cos(config->player.angle) * PLAYER_SPEED;
		new_y = config->player.y - sin(config->player.angle) * PLAYER_SPEED;
		if (config->map[(int)(new_y / 32)][(int)(new_x / 32)] != '1')
		{
			config->player.x = new_x;
			config->player.y = new_y;
		}
	}
	if (config->player.dir_left)
		config->player.angle -= ROTATION_SPEED * (M_PI / 180);
	if (config->player.dir_right)
		config->player.angle += ROTATION_SPEED * (M_PI / 180);
}

void locate_player(t_config *config){
	int i = 0;
	while(config->map[i]){
		int j = 0;
		while(config->map[i][j]){
			if(config->map[i][j] == 'N' || config->map[ i][j] == 'S'
				|| config->map[i][j] == 'E' || config->map[i][j] == 'W'){
				config->player.x = j * 32 + 16;
				config->player.y = i * 32 + 16;
				config->map[i][j] = '0';
				return;
			}
			j++;
		}
		i++;
	}
}