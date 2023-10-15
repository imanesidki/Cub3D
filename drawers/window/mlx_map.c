/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:37:28 by isalama           #+#    #+#             */
/*   Updated: 2023/10/15 18:30:43 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	draw_game(t_config *config)
{
	int		i;
	double	y;
	double	x;
	double	increment;
	double	angle;
	t_ray	ray;
	double  finalDistance;
	int		x_offset = 0;
	int		y_offset = 0;
	int texture = 0;

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
		initialize_ray_vars(&ray);
		ray.ray_angle = (angle);
		normalize_angle(&(ray.ray_angle));
		horizontal_distance(&ray, config);
		vertical_distance(&ray, config);
		x = 0;
		y = 0;
		if (ray.h_dist <= ray.v_dist && ray.hit_h)
		{
			finalDistance = ray.h_dist;
			y = ray.h_point_hit_y;
			x = ray.h_point_hit_x;
			if (ray.ray_angle > 0 && ray.ray_angle < M_PI)
				texture = 1;
			else
				texture = 0;
			x_offset = fmod(ray.h_point_hit_x, 32) * ((double)config->tex[texture]->width / 32);
		}
		else
		{
			finalDistance = ray.v_dist;
			y = ray.v_point_hit_y;
			x = ray.v_point_hit_x;
			if (ray.ray_angle > M_PI_2 && ray.ray_angle < 3 * M_PI_2)
				texture = 3;
			else
				texture = 2;
			x_offset = fmod(ray.v_point_hit_y, 32) * ((double)config->tex[texture]->width / 32);
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

		int top = 0;
		while (top < wall_top_pixel)
		{
			pixel_put(config, i, top, to_hex(config->c[0], config->c[1], config->c[2]));
			top++;
		}
		
		while (wall_top_pixel < wall_bottom_pixel)
		{
			y_offset = config->tex[texture]->height * (wall_top_pixel + (wall_strip_height / 2) - (HEIGHT / 2)) / wall_strip_height;
			
			pixel_put(config, i, wall_top_pixel, get_pixel_color(config, x_offset, y_offset, texture));
			wall_top_pixel++;
		}
		
		int bottom = wall_bottom_pixel;
		while (bottom < HEIGHT)
		{
			pixel_put(config, i, bottom, to_hex(config->f[0], config->f[1], config->f[1]));
			bottom++;
		}
		
		
		angle += increment;
		i++;
	}
	mlx_put_image_to_window(config->mlx, config->win, config->map_data.img, 0, 0);
	return (0);
}
