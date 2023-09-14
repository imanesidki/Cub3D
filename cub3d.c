/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:19:45 by isalama           #+#    #+#             */
/*   Updated: 2023/09/14 18:16:46 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_window(void)
{
    void    *mlx;
    void    *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 500, 500, "cub3d");
    mlx_loop(mlx);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        show_error("Error\nEnter a valid map file\n");
        return (1);
    }
    
    parse_configs(argv[1]);
    
    ft_putstr_fd("The game is running...\n", 1);
    
    init_window();
}