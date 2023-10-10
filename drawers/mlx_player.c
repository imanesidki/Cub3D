/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:35:57 by isalama           #+#    #+#             */
/*   Updated: 2023/10/10 21:46:05 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_press(int keycode, t_config *config)
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
	return (0);
}

int	key_release(int keycode, t_config *config)
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
	return (0);
}

void	move_player(t_config *config)
{
	player_move_left(config);
	player_move_right(config);
	player_move_up(config);
	player_move_down(config);
	if (config->player.dir_left)
		config->player.angle -= ROTATION_SPEED * (M_PI / 180);
	if (config->player.dir_right)
		config->player.angle += ROTATION_SPEED * (M_PI / 180);
}

void	locate_player(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == 'N' || config->map[i][j] == 'S'
				|| config->map[i][j] == 'E' || config->map[i][j] == 'W')
			{
				config->player.x = j * TILE_SIZE + (TILE_SIZE / 2);
				config->player.y = i * TILE_SIZE + (TILE_SIZE / 2);
				config->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
