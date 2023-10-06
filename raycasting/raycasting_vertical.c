/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_vertical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:29:40 by isidki            #+#    #+#             */
/*   Updated: 2023/10/06 17:33:20 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    verticalDistance(t_ray *ray, t_config *config)
{
    
    double first_intersection_x = floor(config->player.x / 32) * 32;
    if (!facing_left(ray->ray_angle)) // ray facing right
        first_intersection_x += 32;
    double first_intersection_y = config->player.y + ((first_intersection_x - config->player.x) / tan(ray->ray_angle));
    double xstep = 32;
    if (facing_left(ray->ray_angle)) // ray facing left
    {
        xstep *= -1;
        first_intersection_x--;
    } 
    double ystep = 32 * tan(ray->ray_angle);
    if (((ray->ray_angle > 0 && ray->ray_angle < M_PI) && ystep < 0) || (!(ray->ray_angle > 0 && ray->ray_angle < M_PI) && ystep > 0))
        ystep *= -1;
   while (((int)(first_intersection_x / 32)) >= 0 && ((int)(first_intersection_y / 32)) >= 0 && ((int)(first_intersection_x / 32)) < config->map_width && ((int)(first_intersection_y / 32)) < config->map_height)
    {
        if (is_wall(first_intersection_x, first_intersection_y, config))
        {
           
           ray->hit_v = true;
            break;
        }
       
        first_intersection_x += xstep;
        first_intersection_y += ystep;
    }
    ray->v_point_hit_x = first_intersection_x;
    ray->v_point_hit_y = first_intersection_y;
    ray->vertical_distance = sqrt(pow((config->player.x - first_intersection_x), 2) + pow((config->player.y - first_intersection_y), 2));
}
