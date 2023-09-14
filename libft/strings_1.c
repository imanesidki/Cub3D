/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:23:16 by isalama           #+#    #+#             */
/*   Updated: 2023/09/14 18:22:40 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_putstr_fd(char *str, int fd)
{
    int i;

    i = 0;
    while (str[i])
        write(fd, &str[i++], 1);
}

bool ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (false);
        i++;
    }
    if (s1[i] != s2[i])
        return (false);
    return (true);
}