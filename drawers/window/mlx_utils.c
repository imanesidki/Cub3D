/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:25:12 by isalama           #+#    #+#             */
/*   Updated: 2023/10/15 18:28:57 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	initialize_ray_vars(t_ray *ray)
{
	ray->h_point_hit_x = -1;
	ray->h_point_hit_y = -1;
	ray->v_point_hit_x = -1;
	ray->v_point_hit_y = -1;
	ray->h_intrsct_x = 0;
	ray->h_intrsct_y = 0;
	ray->v_intrsct_x = 0;
	ray->v_intrsct_y = 0;
	ray->h_xstep = 0;
	ray->h_ystep = 0;
	ray->v_xstep = 0;
	ray->v_ystep = 0;
	ray->h_dist = INFINITY;
	ray->v_dist = INFINITY;
	ray->ray_angle = M_PI_2;
	ray->hit_h = false;
	ray->hit_v = false;
}

void	normalize_angle(double *angle)
{
	*angle = *angle * 180 / M_PI;
	*angle = fmod(*angle, 360);
	if (*angle < 0)
		*angle += 360;
	*angle = *angle * M_PI / 180;
}

int	get_pixel_color(t_config *config, double off_x, double off_y, int texture)
{
	int	color;
	int	x;
	int	y;

	x = roundf(off_x);
	y = roundf(off_y);
	color = *(unsigned int *)(config->tex[texture]->addr + (y * \
	config->tex[texture]->line_length + x * \
	(config->tex[texture]->bits_per_pixel / 8)));
	return (color);
}
