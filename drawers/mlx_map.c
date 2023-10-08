/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 20:37:28 by isalama           #+#    #+#             */
/*   Updated: 2023/10/08 19:28:20 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void    draw_direction_line(t_config *config, double angle, double distance)
// {
//     double player_x = config->player.x;
//     double player_y = config->player.y;
//     double endX = player_x + distance * cos(angle);
//     double endY = player_y + distance * sin(angle);
    
//     double deltaX = endX - player_x;
//     double deltaY = endY - player_y;
    
//     double steps;
//     if (fabs(deltaX) >= fabs(deltaY))
//         steps = fabs(deltaX);
//     else
//         steps = fabs(deltaY);

//     double Xinc = deltaX / steps;
//     double Yinc = deltaY / steps;

//     double X = player_x;
//     double Y = player_y;

//     int i = 0;
//     while (i <= steps)
//     {
//         pixel_put(config, X, Y, to_hex(0, 0, 0));
//         X += Xinc;
//         Y += Yinc;
//         i++;
//     }
// }

void draw_map(t_config *config)
{
    int i = 0;
    while(config->map[i]){
        int j = 0;
        while(config->map[i][j]){
            if(config->map[i][j] == '1')
                draw_tiles(config, j * TILE_SIZE, i * TILE_SIZE, to_hex(config->c[0], config->c[1], config->c[2]));
            else if(config->map[i][j] == '0')
                draw_tiles(config, j * TILE_SIZE, i * TILE_SIZE, to_hex(config->f[0], config->f[1], config->f[2]));
            j++;
        }
        i++;
    }
}

void set_to_zero(t_ray *ray)
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

void normalize_angle(double *angle)
{
    // if ((*angle * 180 / M_PI) >= 360)
    //     *angle -= 2 * M_PI;
    // else if ((*angle * 180 / M_PI) < 0)
    //     *angle += 2 * M_PI;
    
    *angle = *angle * 180 / M_PI; // to degree
    *angle = fmod(*angle, 360);
    if (*angle < 0)
        *angle += 360;
    *angle = *angle * M_PI / 180; // to radian
}

void DDA(t_config *config, double X0, double Y0, double X1, double Y1) 
{ 
    // calculate dx & dy 
    double dx = X1 - X0; 
    double dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    double steps;
     if (fabs(dx) >= fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
  
    double Xinc; 
    double Yinc; 
    // calculate increment in x & y for each steps 
    if (steps != 0)
    {
        Xinc = dx / (double)steps; 
        Yinc = dy / (double)steps; 
    }
    // Put pixel for each step 
    double X = X0; 
    double Y = Y0; 
    int i = 0;
    while (i <= steps)
    { 
       pixel_put(config, X, Y, to_hex(0,0,0));
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
        i++;
    } 
} 

bool facing_down(double angle)
{
    return (angle > 0 && angle < M_PI);
}
bool facing_left(double angle)
{
    return (angle > 0.5 * M_PI && angle < 1.5 * M_PI);
}

int draw_minimap(t_config *config)
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
        // if (facing_down(ray.ray_angle))
        //     printf("facing down\n");
        // else 
        //     printf("facing up\n");
            
        // if (facing_left(ray.ray_angle))
        //     printf("facing left\n");
        // else 
        //     printf("facing right\n");
        x = 0;
        y = 0;
            
        if (ray.horizontal_distance <= ray.vertical_distance && ray.hit_h)
        {
            finalDistance = ray.horizontal_distance;
            y = ray.h_point_hit_y;
            x = ray.h_point_hit_x;
            // DDA(config,config->player.x, config->player.y,  x, y);
        }
        else if (ray.hit_v)
        {
            finalDistance = ray.vertical_distance;
            y = ray.v_point_hit_y;
            x = ray.v_point_hit_x;
            // DDA(config,config->player.x, config->player.y,  x, y);
        }
        DDA(config,config->player.x, config->player.y,  x, y);
            // if(finalDistance != INFINITY)
        // printf("%f\n" , finalDistance);
        angle += increment;
        i++;
    } 
    mlx_put_image_to_window(config->mlx, config->win, config->map_data.img, 0, 0);
    return 0;
}