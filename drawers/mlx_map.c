/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:37:28 by isalama           #+#    #+#             */
/*   Updated: 2023/10/04 14:24:14 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_direction_line(t_config *config, double angle, double distance){
    double player_x = config->player.x;
    double player_y = config->player.y;
    double endX = player_x + distance * cos(angle);
    double endY = player_y + distance * sin(angle);
    
    double deltaX = endX - player_x;
    double deltaY = endY - player_y;
    
    double steps;
    if (fabs(deltaX) >= fabs(deltaY))
        steps = fabs(deltaX);
    else
        steps = fabs(deltaY);

    double Xinc = deltaX / steps;
    double Yinc = deltaY / steps;

    double X = player_x;
    double Y = player_y;

    int i = 0;
    while (i <= steps)
    {
        pixel_put(config, X, Y, to_hex(0, 0, 0));
        X += Xinc;
        Y += Yinc;
        i++;
    }
}

void draw_map(t_config *config)
{
    int i = 0;
    while(config->map[i]){
        int j = 0;
        while(config->map[i][j]){
            if(config->map[i][j] == '1')
                draw_tiles(config, j * 32, i * 32, to_hex(config->c[0], config->c[1], config->c[2]));
            else if(config->map[i][j] == '0')
                draw_tiles(config, j * 32, i * 32, to_hex(config->f[0], config->f[1], config->f[2]));
            j++;
        }
        i++;
    }
}

void set_to_zero(t_ray *ray)
{
    ray->h_point_hit_x = 0;
    ray->h_point_hit_y = 0;
    ray->v_point_hit_x = 0;
    ray->v_point_hit_y = 0;
    ray->horizontal_distance = 0;
    ray->vertical_distance = 0;
    ray->ray_angle = 0;
}

// void verticalDistance(t_ray *ray)
// {
    // bool hit_wall = false;
    // double first_intersection_x =  ?
    // double first_intersection_y =  ?
    
    
    // double xstep =  ?
    // double ystep =  ?
    /*
        while (it didn't hit a wall)
        {
            if (is_wall(first_intersection_x, first_intersection_y))
                break;
            first_intersection_x += xstep;
            first_intersection_y += ystep;
        }
    */
   
   // if we hit a wall then (hit_wall = true) and (ray->v_point_hit_x = first_intersection_x) and (ray->v_point_hit_y = first_intersection_y)
   // and (ray->vertical_distance = distance_between_player_and_wall)
   // else if we didn't hit a wall then (ray->vertical_distance = INT_MAX)
// }

// void horizontalDistance(t_ray *ray)
// {
    // bool hit_wall = false;
    // double first_intersection_x =  ?
    // double first_intersection_y =  ?
    
    
    // double xstep =  ?
    // double ystep =  ?
    /*
        while (it didn't hit a wall)
        {
            if (is_wall(first_intersection_x, first_intersection_y))
                break;
            first_intersection_x += xstep;
            first_intersection_y += ystep;
        }
    */
   
   // if we hit a wall then (hit_wall = true) and (ray->h_point_hit_x = first_intersection_x) and (ray->h_point_hit_y = first_intersection_y)
   // and (ray->horizontal_distance = distance_between_player_and_wall)
   // else if we didn't hit a wall then (ray->horizontal_distance = INT_MAX)
// }





int draw_minimap(t_config *config){
    

    mlx_clear_window(config->mlx, config->win);
    mlx_destroy_image(config->mlx, config->map_data.img);
    config->map_data.img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
    config->map_data.addr = mlx_get_data_addr(config->map_data.img,
    &config->map_data.bits_per_pixel, &config->map_data.line_length, &config->map_data.endian);
    move_player(config);
    draw_map(config);
    draw_player(config, PLAYER_SIZE, to_hex(255, 92, 92));
    double increment = (VIEW_RANGE * M_PI / 180) / WIDTH;
    double angle = config->player.angle - (VIEW_RANGE * M_PI / 180) / 2;
        
    // t_ray ray; TODO
    
    // double finalDistance;  TODO
    while(angle < config->player.angle + (VIEW_RANGE * M_PI / 180) / 2) {
        
        
        // set_to_zero(&ray); TODO
        // ray.ray_angle = angle; TODO
        // verticalDistance(&ray); TODO
        // horizontalDistance(&ray); TODO
        
        // if (ray.horizontal_distance <= ray.vertical_distance) TODO
        //     finalDistance = ray.horizontal_distance; TODO
        // else TODO
        //     finalDistance = ray.vertical_distance; TODO

        draw_direction_line(config, angle, 50.0 /*finalDistance*/);
        angle += increment;
    }
    
    mlx_put_image_to_window(config->mlx, config->win, config->map_data.img, 0, 0);
    return 0;
}