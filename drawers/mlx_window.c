/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:22:06 by isalama           #+#    #+#             */
/*   Updated: 2023/09/16 19:29:11 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pixel_put(t_config *config, int x, int y, int color)
{
	char	*dst;

	dst = config->map_data.addr + (y * config->map_data.line_length + x * (config->map_data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    draw_tiles(t_config *config, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < 32)
    {
        j = 0;
        while (j < 32)
        {
            pixel_put(config, x + i, y + j, color);
            j++;
        }
        i++;
    }
}
void    draw_player(t_config *config, int x, int y, int color)
{
    int i;
    int j;
    int size;
    
    size = 32 / 2 + 5;
    i = 32 / 2 - 5;
    while (i < size)
    {
        j = 32 / 2 - 5;
        while (j < size)
        {
            pixel_put(config, x + i, y + j, color);
            j++;
        }
        i++;
    }
}