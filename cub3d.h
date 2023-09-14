/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:19:50 by isalama           #+#    #+#             */
/*   Updated: 2023/09/14 18:23:09 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif


// ---> START STRUCTURE
typedef struct  s_window
{
    void    *mlx;
    void    *win;
}               t_window;


// ---> START FUNCTIONS
//      ---> libft
void    ft_putstr_fd(char *str, int fd);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	*ft_substr(char *s, int start, int len);
bool    ft_strcmp(char *s1, char *s2);

//      ---> get_next_line
char	*get_next_line(int fd);
char	*get_next_line_utils(int fd);

// ---> helpers
//      ---> strings
void    show_error(char *str);

//     ---> parsers
void    parse_configs(char *str);

#endif