/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_vertical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:29:40 by isidki            #+#    #+#             */
/*   Updated: 2023/10/08 20:11:36 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	verticalDistance(t_ray *ray, t_config *config)
{
	double intrsect_x = floor(config->player.x / TILE_SIZE) * TILE_SIZE;
	if (!facing_left(ray->ray_angle)) // ray facing right
		intrsect_x += TILE_SIZE;
	double intrsect_y = config->player.y + ((intrsect_x - config->player.x) * tan(ray->ray_angle));
	double xstep = TILE_SIZE;
	int d = 0;
	if (facing_left(ray->ray_angle)) // ray facing left
	{
		xstep *= -1;
		d = 1;
	}
	double ystep = xstep * tan(ray->ray_angle);
	if ((facing_down(ray->ray_angle) && ystep < 0) || (!facing_down(ray->ray_angle) && ystep > 0))
		ystep *= -1;

	while (((int)(intrsect_x / TILE_SIZE)) >= 0 && ((int)(intrsect_y / TILE_SIZE)) >= 0 && ((int)(intrsect_x / TILE_SIZE)) < config->map_width && ((int)(intrsect_y / TILE_SIZE)) < config->map_height)
	{
		if (is_wall(intrsect_x - d, intrsect_y, config))
		{
		   ray->hit_v = true;
		   ray->v_point_hit_x = intrsect_x;
		   ray->v_point_hit_y = intrsect_y;
		   ray->vertical_distance = sqrt(pow((config->player.x - intrsect_x), 2) + pow((config->player.y - intrsect_y), 2));
			break;
		}
		else
		{
			intrsect_x += xstep;
			intrsect_y += ystep;
			ray->vertical_distance = INFINITY;
		}
	}
}
