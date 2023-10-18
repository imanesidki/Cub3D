/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_basics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:22:36 by isalama           #+#    #+#             */
/*   Updated: 2023/10/18 15:33:56 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	to_hex(int r, int g, int b)
{
	unsigned int	hex;

	hex = (r << 16) | (g << 8) | b;
	return (hex);
}

char	*get_error(int err_code)
{
	if (err_code == 0)
		return ("Error\nInvalid map\n");
	if (err_code == 1)
		return ("Error\nInvalid attributes\n");
	if (err_code == 2)
		return ("Error\nMap not closed\n");
	if (err_code == 3)
		return ("Error\nInvalid textures\n");
	if (err_code == 4)
		return ("Error\nInvalid extension\n");
	if (err_code == 5)
		return ("Malloc failure");
	return (NULL);
}

void	ft_exit(t_config *config, int err)
{
	if (err == 7)
		exit(1);
	clear_resources(config);
	if (get_error(err))
		printf("%s", get_error(err));
	exit(1);
}
 