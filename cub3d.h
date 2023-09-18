/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:19:50 by isalama           #+#    #+#             */
/*   Updated: 2023/09/18 17:56:58 by isalama          ###   ########.fr       */
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
typedef struct s_map_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_map_data;

typedef struct s_player
{
	bool		up;
	bool		down;
	bool		left;
	bool		right;
	bool		dir_left;
	bool		dir_right;
	double		angle;

	int			x;
	int			y;
}	t_player;

typedef struct s_config
{
	t_map_data	map_data;
	t_player	player;

	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;

	int			f[3];
	int			c[3];
	char		**map;

	void		*mlx;
	void		*win;
}	t_config;


// ---> START FUNCTIONS
//		---> libft
void			ft_putstr_fd(char *str, int fd);
char			*ft_strdup(char *s1);
int				ft_strlen(char *s);
int				ft_tablen(char **tab);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchr(char *s, int c);
char			*ft_substr(char *s, int start, int len);
bool			ft_strcmp(char *s1, char *s2);
bool			ft_strncmp(char *s1, char *s2, int n);
char			**ft_split(char *s, char c);
int				ft_atoi(char *str);
bool			ft_isdigit(char c);
char			*ft_strrchr(char *s, int c);
bool			is_space(char str);
char			*ft_strtrim(char *s1, char *set);

//		---> get_next_line
char			*get_next_line(int fd);
char			*get_next_line_utils(int fd);

// ---> helpers
//		---> strings
void			show_error(char *str);
bool			has_extension(char *filename, char *extension);

//      ---> parsers
void			validate_map(char *str, t_config *config);

//      ---> utils
unsigned int	to_hex(int r, int g, int b);

// ---> drawers
//      ---> mlx_window
void			init_window(t_config *config);
void			pixel_put(t_config *config, int x, int y, int color);
void			draw_tiles(t_config *config, int x, int y, int color);
void			draw_player(t_config *config, int x, int y, int color);
void			draw_direction_line(t_config *config);

//      ---> mlx_player
int				handle_press(int keycode, t_config *config);
int				key_release(int keycode, t_config *config);
void			move_player(t_config *config);
void			locate_player(t_config *config);

//      ---> mlx_map
void			update_map(t_config *config);
int				draw_minimap(t_config *config);

#endif