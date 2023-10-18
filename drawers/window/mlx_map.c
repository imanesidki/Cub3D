/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:37:28 by isalama           #+#    #+#             */
/*   Updated: 2023/10/18 16:10:25 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_game(t_config *config)
{
	mlx_clear_window(config->mlx, config->win);
	mlx_destroy_image(config->mlx, config->map_data.img);
	config->map_data.img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	config->map_data.addr = mlx_get_data_addr(config->map_data.img,
			&config->map_data.bits_per_pixel,
			&config->map_data.line_length, &config->map_data.endian);
	move_player(config);
	config->drawing.increment = (VIEW_RANGE * M_PI / 180) / WIDTH;
	normalize_angle(&config->player.angle);
	config->drawing.angle = config->player.angle
		- ((VIEW_RANGE * M_PI / 180) / 2);
	normalize_angle(&config->drawing.angle);
	config->drawing.final_dist = 0;
}

void	draw_wall_c_f(t_config *cfg, int i)
{
	int	top;
	int	bottom;

	top = 0;
	while (top < cfg->drawing.wall_top_pixel)
	{
		pixel_put(cfg, i, top, to_hex(cfg->c[0], cfg->c[1], cfg->c[2]));
		top++;
	}
	while (cfg->drawing.wall_top_pixel < cfg->drawing.wall_bottom_pixel)
	{
		cfg->drawing.y_offset = cfg->tex[cfg->drawing.texture]->height * \
		(cfg->drawing.wall_top_pixel + (cfg->drawing.wall_strip_height / 2)
				- (HEIGHT / 2)) / cfg->drawing.wall_strip_height;
		pixel_put(cfg, i, cfg->drawing.wall_top_pixel, get_pixel_color(cfg, \
		cfg->drawing.x_offset, cfg->drawing.y_offset, cfg->drawing.texture));
		cfg->drawing.wall_top_pixel++;
	}
	bottom = cfg->drawing.wall_bottom_pixel;
	while (bottom < HEIGHT)
	{
		pixel_put(cfg, i, bottom, to_hex(cfg->f[0],
				cfg->f[1], cfg->f[1]));
		bottom++;
	}
}

void	set_projection_values(t_config *config)
{
	config->drawing.dist_to_project = (WIDTH / 2)
		/ tan((VIEW_RANGE * M_PI / 180) / 2);
	config->drawing.final_dist = config->drawing.final_dist
		* cos(config->player.angle - config->drawing.angle);
	config->drawing.wall_strip_height = (TILE_SIZE
			/ config->drawing.final_dist) * config->drawing.dist_to_project;
	config->drawing.wall_top_pixel = (HEIGHT / 2)
		- (config->drawing.wall_strip_height / 2);
	config->drawing.wall_bottom_pixel = (HEIGHT / 2)
		+ (config->drawing.wall_strip_height / 2);
	if (config->drawing.wall_top_pixel < 0)
		config->drawing.wall_top_pixel = 0;
	if (config->drawing.wall_bottom_pixel > HEIGHT)
		config->drawing.wall_bottom_pixel = HEIGHT;
}

void	calculate_views(t_config *config, t_ray ray)
{
	double	y;
	double	x;

	if (ray.h_dist <= ray.v_dist && ray.hit_h)
	{
		config->drawing.final_dist = ray.h_dist;
		y = ray.h_point_hit_y;
		x = ray.h_point_hit_x;
		if (ray.ray_angle > 0 && ray.ray_angle < M_PI)
			config->drawing.texture = 1;
		else
			config->drawing.texture = 0;
		config->drawing.x_offset = fmod(ray.h_point_hit_x, 32)
			* ((double)config->tex[config->drawing.texture]->width / 32);
		return ;
	}
	config->drawing.final_dist = ray.v_dist;
	y = ray.v_point_hit_y;
	x = ray.v_point_hit_x;
	if (ray.ray_angle > M_PI_2 && ray.ray_angle < 3 * M_PI_2)
		config->drawing.texture = 3;
	else
		config->drawing.texture = 2;
	config->drawing.x_offset = fmod(ray.v_point_hit_y, 32)
		* ((double)config->tex[config->drawing.texture]->width / 32);
}

int	draw_game(t_config *config)
{
	int		i;
	t_ray	ray;

	init_game(config);
	i = 0;
	while (i < WIDTH)
	{
		initialize_ray_vars(&ray);
		ray.ray_angle = (config->drawing.angle);
		normalize_angle(&(ray.ray_angle));
		horizontal_distance(&ray, config);
		vertical_distance(&ray, config);
		calculate_views(config, ray);
		set_projection_values(config);
		draw_wall_c_f(config, i);
		config->drawing.angle += config->drawing.increment;
		i++;
	}
	mlx_put_image_to_window(config->mlx, config->win,
		config->map_data.img, 0, 0);
	return (0);
}
