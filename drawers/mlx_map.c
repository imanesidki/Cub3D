/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:37:28 by isalama           #+#    #+#             */
/*   Updated: 2023/10/08 20:16:55 by isidki           ###   ########.fr       */
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
	ray->horizontal_distance = INFINITY;
	ray->vertical_distance = INFINITY;
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

void dda(t_config *config, double X0, double Y0, double X1, double Y1)
{
	double dx = X1 - X0;
	double dy = Y1 - Y0;

	double steps;
	if (fabs(dx) >= fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	double Xinc;
	double Yinc;
	if (steps != 0)
	{
		Xinc = dx / (double)steps;
		Yinc = dy / (double)steps;
	}
	double X = X0;
	double Y = Y0;
	int i = 0;
	while (i <= steps)
	{
		pixel_put(config, X, Y, to_hex(0,0,0));
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
	mlx_clear_window(config->mlx, config->win);
	mlx_destroy_image(config->mlx, config->map_data.img);
	config->map_data.img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	config->map_data.addr = mlx_get_data_addr(config->map_data.img,
		&config->map_data.bits_per_pixel, &config->map_data.line_length, &config->map_data.endian);
	move_player(config);
	draw_map(config);
	draw_player(config, PLAYER_SIZE, to_hex(255, 92, 92));

	double increment = (VIEW_RANGE * M_PI / 180) / WIDTH;
	normalize_angle(&config->player.angle);
	double angle = config->player.angle - ((VIEW_RANGE * M_PI / 180) / 2);
	normalize_angle(&angle);
	t_ray   ray;
	double  finalDistance = 0;
	// printf("%f\n", (config->player.angle  * 180 / M_PI));
	double y;
	double x;
	int i = 0;
	while (i < WIDTH) // i < NUM_RAYS
	{     
		set_to_zero(&ray);
		ray.ray_angle = (angle);
		normalize_angle(&(ray.ray_angle));
		horizontalDistance(&ray, config);
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
		dda(config, config->player.x, config->player.y, x, y);
		angle += increment;
		i++;
	}
	mlx_put_image_to_window(config->mlx, config->win, config->map_data.img, 0, 0);
	return (0);
}
