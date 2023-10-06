/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_horizontal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:29:00 by isidki            #+#    #+#             */
/*   Updated: 2023/10/06 16:43:51 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool is_wall(double x, double y, t_config *config)
{
	int i;
	int j;

	i = (int)(x / 32);
	j = (int)(y / 32);
	if (i < config->map_width && j < config->map_height && j >= 0 && i >= 0)
	{
		if (config->map[j][i] == '1')
			return true;
	}
	return false;
}

void    horizontalDistance(t_ray *ray, t_config *config)
{

	
	double first_intersection_y = floor(config->player.y / 32) * 32;
	
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI) //ray facing down
		first_intersection_y += 32;
		
	double first_intersection_x = config->player.x + ((first_intersection_y - config->player.y) / tan(ray->ray_angle));
	
	double ystep = 32;
	// if (!(ray->ray_angle > 0 && ray->ray_angle < M_PI))
	//     ystep *= -1;
	if (!(ray->ray_angle > 0 && ray->ray_angle < M_PI)) //ray facing up
	{
		ystep *= -1;
		first_intersection_y--;
	}
	
	double xstep = ystep / tan(ray->ray_angle);
	
	// if ((!(ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI) && xstep > 0) || ((ray->ray_angle < 0.5 * M_PI || ray->ray_angle > 1.5 * M_PI) && xstep < 0))
	//     xstep *= -1;
		
	while (((int)(first_intersection_x / 32)) >= 0 && ((int)(first_intersection_y / 32)) >= 0 && ((int)(first_intersection_x / 32)) < config->map_width && ((int)(first_intersection_y / 32)) < config->map_height)
	{
		if (is_wall(first_intersection_x, first_intersection_y, config))
		{
			ray->hit_h = true;
			break;
		}
		first_intersection_x += xstep;
		first_intersection_y += ystep;
	}
	ray->h_point_hit_x = first_intersection_x;
	ray->h_point_hit_y = first_intersection_y;
	ray->horizontal_distance = sqrt(pow((config->player.x - first_intersection_x), 2) + pow((config->player.y - first_intersection_y), 2));
	// if (!hit_wall)
	// 	ray->horizontal_distance = INFINITY;
   // if we hit a wall then (hit_wall = true) and (ray->h_point_hit_x = first_intersection_x) and (ray->h_point_hit_y = first_intersection_y)
   // and (ray->horizontal_distance = distance_between_player_and_wall)
   // else if we didnt hit a wall then (ray->horizontal_distance = INT_MAX)
}