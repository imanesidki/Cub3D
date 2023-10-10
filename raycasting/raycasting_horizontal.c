/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_horizontal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:29:00 by isidki            #+#    #+#             */
/*   Updated: 2023/10/10 22:53:01 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_intercept_h(t_ray *ray, int d, t_config *config)
{
	while (((int)(ray->h_intrsct_x / TILE_SIZE)) >= 0
		&& ((int)(ray->h_intrsct_y / TILE_SIZE)) >= 0
		&& ((int)(ray->h_intrsct_x / TILE_SIZE)) < config->map_width
		&& ((int)(ray->h_intrsct_y / TILE_SIZE)) < config->map_height)
	{
		if (is_wall(ray->h_intrsct_x, ray->h_intrsct_y - d, config))
		{
			ray->hit_h = true;
			ray->h_point_hit_x = ray->h_intrsct_x;
			ray->h_point_hit_y = ray->h_intrsct_y;
			ray->h_dist = sqrt(pow((config->player.x - ray->h_intrsct_x), 2)
					+ pow((config->player.y - ray->h_intrsct_y), 2));
			break ;
		}
		else
		{
			ray->h_intrsct_x += ray->h_xstep;
			ray->h_intrsct_y += ray->h_ystep;
			ray->h_dist = INFINITY;
		}
	}
}

void	horizontal_distance(t_ray *ray, t_config *config)
{
	int	d;

	ray->h_intrsct_y = floor(config->player.y / TILE_SIZE) * TILE_SIZE;
	if (facing_down(ray->ray_angle))
		ray->h_intrsct_y += TILE_SIZE;
	ray->h_intrsct_x = config->player.x + ((ray->h_intrsct_y
				- config->player.y) / tan(ray->ray_angle));
	ray->h_ystep = TILE_SIZE;
	d = 0;
	if (!facing_down(ray->ray_angle))
	{
		d = 1;
		ray->h_ystep *= -1;
	}
	ray->h_xstep = ray->h_ystep / tan(ray->ray_angle);
	if ((facing_left(ray->ray_angle) && ray->h_xstep > 0)
		|| (!facing_left(ray->ray_angle) && ray->h_xstep < 0))
		ray->h_xstep *= -1;
	find_intercept_h(ray, d, config);
}
