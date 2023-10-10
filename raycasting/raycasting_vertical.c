/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_vertical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:29:40 by isidki            #+#    #+#             */
/*   Updated: 2023/10/10 22:53:13 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_intercept_v(t_ray *ray, int d, t_config *config)
{
	while (((int)(ray->v_intrsct_x / TILE_SIZE)) >= 0
		&& ((int)(ray->v_intrsct_y / TILE_SIZE)) >= 0
		&& ((int)(ray->v_intrsct_x / TILE_SIZE)) < config->map_width
		&& ((int)(ray->v_intrsct_y / TILE_SIZE)) < config->map_height)
	{
		if (is_wall(ray->v_intrsct_x - d, ray->v_intrsct_y, config))
		{
			ray->hit_v = true;
			ray->v_point_hit_x = ray->v_intrsct_x;
			ray->v_point_hit_y = ray->v_intrsct_y;
			ray->v_dist = sqrt(pow((config->player.x - ray->v_intrsct_x), 2)
					+ pow((config->player.y - ray->v_intrsct_y), 2));
			break ;
		}
		else
		{
			ray->v_intrsct_x += ray->v_xstep;
			ray->v_intrsct_y += ray->v_ystep;
			ray->v_dist = INFINITY;
		}
	}
}

void	vertical_distance(t_ray *ray, t_config *config)
{
	int	d;

	ray->v_intrsct_x = floor(config->player.x / TILE_SIZE) * TILE_SIZE;
	if (!facing_left(ray->ray_angle))
		ray->v_intrsct_x += TILE_SIZE;
	ray->v_intrsct_y = config->player.y + ((ray->v_intrsct_x
				- config->player.x) * tan(ray->ray_angle));
	ray->v_xstep = TILE_SIZE;
	d = 0;
	if (facing_left(ray->ray_angle))
	{
		ray->v_xstep *= -1;
		d = 1;
	}
	ray->v_ystep = ray->v_xstep * tan(ray->ray_angle);
	if ((facing_down(ray->ray_angle) && ray->v_ystep < 0)
		|| (!facing_down(ray->ray_angle) && ray->v_ystep > 0))
		ray->v_ystep *= -1;
	find_intercept_v(ray, d, config);
}
