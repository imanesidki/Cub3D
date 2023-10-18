/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:36:55 by isalama           #+#    #+#             */
/*   Updated: 2023/10/16 21:13:44 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

bool	not_a_wall(double x, double y, t_config *config)
{
	if (x < 0 || ((int)x / TILE_SIZE) >= config->map_width
		|| (y) < 0 || ((int)y / TILE_SIZE) >= config->map_height)
		return (false);
	if ((config->map[(int)(y / TILE_SIZE)]
		[(int)(x / TILE_SIZE)] != '1'
			&& config->map[(int)(y / TILE_SIZE)]
			[(int)(x / TILE_SIZE)] != 'x'))
		return (true);
	return (false);
}

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
		if (not_a_wall(new_x, new_y, config))
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
		if (not_a_wall(new_x, new_y, config))
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
		if (not_a_wall(new_x, new_y, config))
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
		if (not_a_wall(new_x, new_y, config))
		{
			config->player.x = new_x;
			config->player.y = new_y;
		}
	}
}
