/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:36:55 by isalama           #+#    #+#             */
/*   Updated: 2023/10/10 21:45:52 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	player_move_left(t_config *config)
{
	double	new_x;
	double	new_y;

	if (config->player.left)
	{
		new_x = config->player.x - cos(config->player.angle 
				+ (M_PI / 2)) * PLAYER_SPEED;
		new_y = config->player.y - sin(config->player.angle
				+ (M_PI / 2)) * PLAYER_SPEED;
		if (config->map[(int)(new_y / TILE_SIZE)]
		[(int)(new_x / TILE_SIZE)] != '1'
			&& config->map[(int)(new_y / TILE_SIZE)]
			[(int)(new_x / TILE_SIZE)] != 'x')
		{
			config->player.x = new_x;
			config->player.y = new_y;
		}
	}
}

void	player_move_right(t_config *config)
{
	double	new_x;
	double	new_y;

	if (config->player.right)
	{
		new_x = config->player.x + cos(config->player.angle
				+ (M_PI / 2)) * PLAYER_SPEED;
		new_y = config->player.y + sin(config->player.angle
				+ (M_PI / 2)) * PLAYER_SPEED;
		if (config->map[(int)(new_y / TILE_SIZE)]
		[(int)(new_x / TILE_SIZE)] != '1'
			&& config->map[(int)(new_y / TILE_SIZE)]
			[(int)(new_x / TILE_SIZE)] != 'x')
		{
			config->player.x = new_x;
			config->player.y = new_y;
		}
	}
}

void	player_move_up(t_config *config)
{
	double	new_x;
	double	new_y;

	if (config->player.up)
	{
		new_x = config->player.x + cos(config->player.angle) * PLAYER_SPEED;
		new_y = config->player.y + sin(config->player.angle) * PLAYER_SPEED;
		if (config->map[(int)(new_y / TILE_SIZE)]
		[(int)(new_x / TILE_SIZE)] != '1'
		&& config->map[(int)(new_y / TILE_SIZE)]
		[(int)(new_x / TILE_SIZE)] != 'x')
		{
			config->player.x = new_x;
			config->player.y = new_y;
		}
	}
}

void	player_move_down(t_config *config)
{
	double	new_x;
	double	new_y;

	if (config->player.down)
	{
		new_x = config->player.x - cos(config->player.angle) * PLAYER_SPEED;
		new_y = config->player.y - sin(config->player.angle) * PLAYER_SPEED;
		if (config->map[(int)(new_y / TILE_SIZE)]
		[(int)(new_x / TILE_SIZE)] != '1'
		&& config->map[(int)(new_y / TILE_SIZE)]
		[(int)(new_x / TILE_SIZE)] != 'x')
		{
			config->player.x = new_x;
			config->player.y = new_y;
		}
	}
}
