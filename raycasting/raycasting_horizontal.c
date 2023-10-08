/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_horizontal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:29:00 by isidki            #+#    #+#             */
/*   Updated: 2023/10/08 19:28:06 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_wall(double x, double y, t_config *config)
{
	int	i;
	int	j;

	i = (int)floor(x / TILE_SIZE);
	j = (int)floor(y / TILE_SIZE);
	if (i < config->map_width && j < config->map_height && j >= 0 && i >= 0)
	{
		if (config->map[j][i] == '1')
			return (true);
	}
	return (false);
}

void	horizontalDistance(t_ray *ray, t_config *config)
{

	double first_intersection_y = floor(config->player.y / TILE_SIZE) * TILE_SIZE;
	
	if (facing_down(ray->ray_angle)) //ray facing down
		first_intersection_y += TILE_SIZE;
		
	double first_intersection_x = config->player.x + ((first_intersection_y - config->player.y) / tan(ray->ray_angle));
	
	double ystep = TILE_SIZE;
	int d = 0;
	if (!facing_down(ray->ray_angle)) //ray facing up
	{
		d = 1;
		ystep *= -1;
	}

	double xstep = ystep / tan(ray->ray_angle);
	
	if ((facing_left(ray->ray_angle) && xstep > 0) || (!facing_left(ray->ray_angle) && xstep < 0))
	    xstep *= -1;
		
	while (((int)(first_intersection_x / TILE_SIZE)) >= 0 && ((int)(first_intersection_y / TILE_SIZE)) >= 0 && ((int)(first_intersection_x / TILE_SIZE)) < config->map_width && ((int)(first_intersection_y / TILE_SIZE)) < config->map_height)
	{
		if (is_wall(first_intersection_x, first_intersection_y - d, config))
		{
			ray->hit_h = true;
			ray->h_point_hit_x = first_intersection_x;
			ray->h_point_hit_y = first_intersection_y;
			ray->horizontal_distance = sqrt(pow((config->player.x - first_intersection_x), 2) + pow((config->player.y - first_intersection_y), 2));
			break;
		}
		else
		{
			first_intersection_x += xstep;
			first_intersection_y += ystep;
			ray->horizontal_distance = INFINITY;
		}
	}
}