/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:37:28 by isalama           #+#    #+#             */
/*   Updated: 2023/10/10 22:15:16 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_map(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == '1')
				draw_tiles(config, j * TILE_SIZE, i * TILE_SIZE,
					to_hex(config->c[0], config->c[1], config->c[2]));
			else if (config->map[i][j] == '0')
				draw_tiles(config, j * TILE_SIZE, i * TILE_SIZE,
					to_hex(config->f[0], config->f[1], config->f[2]));
			j++;
		}
		i++;
	}
}

void	set_to_zero(t_ray *ray)
{
	ray->h_point_hit_x = -1;
	ray->h_point_hit_y = -1;
	ray->v_point_hit_x = -1;
	ray->v_point_hit_y = -1;
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

void	dda(t_config *config, double X1, double Y1)
{
	double	Xinc;
	double	Yinc;
	int		i;
	double	dx;
	double	dy;
	double	steps;
	double	X;
	double	Y;

	dx = X1 - config->player.x;
	dy = Y1 - config->player.y;
	if (fabs(dx) >= fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	if (steps != 0)
	{
		Xinc = dx / (double)steps;
		Yinc = dy / (double)steps;
	}
	X = config->player.x;
	Y = config->player.y;
	i = 0;
	while (i <= steps)
	{
		pixel_put(config, X, Y, to_hex(0, 0, 0));
		X += Xinc;
		Y += Yinc;
		i++;
	}
}

bool	facing_down(double angle)
{
	return (angle > 0 && angle < M_PI);
}

bool	facing_left(double angle)
{
	return (angle > 0.5 * M_PI && angle < 1.5 * M_PI);
}

int	draw_minimap(t_config *config)
{
	int		i;
	double	y;
	double	x;
	double	increment;
	double	angle;
	t_ray	ray;
	double  finalDistance;

	mlx_clear_window(config->mlx, config->win);
	mlx_destroy_image(config->mlx, config->map_data.img);
	config->map_data.img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	config->map_data.addr = mlx_get_data_addr(config->map_data.img,
			&config->map_data.bits_per_pixel, &config->map_data.line_length, &config->map_data.endian);
	move_player(config);
	
	increment = (VIEW_RANGE * M_PI / 180) / WIDTH;
	normalize_angle(&config->player.angle);
	angle = config->player.angle - ((VIEW_RANGE * M_PI / 180) / 2);
	normalize_angle(&angle);

	finalDistance = 0;
	i = 0;
	while (i < WIDTH)
	{
		set_to_zero(&ray);
		ray.ray_angle = (angle);
		normalize_angle(&(ray.ray_angle));
		horizontal_distance(&ray, config);
		verticalDistance(&ray, config);
		x = 0;
		y = 0;
		if (ray.horizontal_distance <= ray.vertical_distance && ray.hit_h)
		{
			finalDistance = ray.horizontal_distance;
			y = ray.h_point_hit_y;
			x = ray.h_point_hit_x;
		}
		else if (ray.hit_v)
		{
			finalDistance = ray.vertical_distance;
			y = ray.v_point_hit_y;
			x = ray.v_point_hit_x;
		}
		

		double distance_to_projection_plan = (WIDTH / 2) / tan((VIEW_RANGE * M_PI / 180) / 2);
		finalDistance = finalDistance * cos(config->player.angle - angle);
		double wall_strip_height = (TILE_SIZE / finalDistance) * distance_to_projection_plan;
		double wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
		double wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
		
		
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		if (wall_bottom_pixel > HEIGHT)
			wall_bottom_pixel = HEIGHT;

		// draw ceiling
		int top = 0;
		while (top < wall_top_pixel)
		{
			pixel_put(config, i, top, to_hex(51, 177, 255));
			top++;
		}
		
		// draw wall
		while (wall_top_pixel < wall_bottom_pixel)
		{
			pixel_put(config, i, wall_top_pixel, to_hex(54, 75, 75));
			wall_top_pixel++;
		}
		
		// draw floor
		int bottom = wall_bottom_pixel;
		while (bottom < HEIGHT)
		{
			pixel_put(config, i, bottom, to_hex(41, 41, 41));
			bottom++;
		}
		
		
		angle += increment;
		i++;
	}
	mlx_put_image_to_window(config->mlx, config->win, config->map_data.img, 0, 0);
	return (0);
}
