/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:22:36 by isalama           #+#    #+#             */
/*   Updated: 2023/10/11 12:05:22 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	free_config_struct(config);
	if (get_error(err))
		printf("%s", get_error(err)); 
	exit(1);
}
