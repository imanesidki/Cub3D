/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:02:13 by isalama           #+#    #+#             */
/*   Updated: 2023/09/23 17:54:08 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool parse_configs_helper(char *line, int mode, t_config *config){
    char *trimmed;
    
    trimmed = ft_strdup(ft_strtrim(line + 2, " \t"));
    if(mode == 0){
        if(ft_strncmp(line, "NO", 2) && is_space(line[2]))
		{
            config->no_texture = trimmed;
            return (true);
        }
		if(ft_strncmp(line, "SO", 2) && is_space(line[2]))
		{
            config->so_texture = trimmed;
            return (true);
        }
		if(ft_strncmp(line, "WE", 2) && is_space(line[2]))
		{
            config->we_texture = trimmed;
            return (true);
        }
		if(ft_strncmp(line, "EA", 2) && is_space(line[2]))
		{
            config->ea_texture = trimmed;
            return (true);
        }
    }
    if(mode == 1){
        return (!has_extension(trimmed, ".xpm"));
    }
    return (false);
}

bool parse_colors(char *input, t_config *config, bool mode) {
	int i = 0;
	int count = 0;
	char **rgb = NULL;
	char *colors = ft_strchr(input, ' ');
	if(colors){
		colors++;
		i = 0;
		while (colors[i]){
			if(colors[i] == ',') count++;
			if (count > 2) return (false);
			i++;
		}
		rgb = ft_split(colors, ',');
		if(rgb){
			i = 0;
			while(rgb[i]){
				if (!ft_isdigit(rgb[i][0]) || ft_atoi(rgb[i]) > 255 || ft_atoi(rgb[i]) < 0)
					return (false);
				i++;
			}
			i = 0;
			while(rgb[i]){
				if (mode)
					config->f[i] = ft_atoi(rgb[i]);
				else
					config->c[i] = ft_atoi(rgb[i]);
				i++;
			}
		}
		else
			return (false);
	}
	return (true);
}

char *parse_configs(int fd, t_config *config){
	int total_attrs;
	char *line;
	int i;
	bool found_map;

    total_attrs = 0;
    line = get_next_line(fd);
    while (line){
        if (parse_configs_helper(line, 0, config))
		{
            if (parse_configs_helper(line, 1, config))
			{
                show_error("Error\nMap textures are not valid, invalid extension.\n");
                exit(1);
            }
            total_attrs++;
        }
		else if((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
		{
            if (!parse_colors(line, config, line[0] == 'F')){
                show_error("Error\nMap colors are not valid\n");
                exit(1);
            }
            total_attrs++;
        }
		else
		{
            i = 0;
            found_map = false;
            while(line[i]){
                if (line[i] == '1' || line[i] == '0'){
                    found_map = true;
                } else if (line[i] != ' '){
                    show_error("Error\nMap is not valid.\n--> Affected line: ");
                    ft_putstr_fd(line, 1);
                    exit(1);
                }
                i++;
            }
            if (found_map)
                break;
        }
        free(line);
        line = get_next_line(fd);
    }
    if (total_attrs != 6){
        show_error("Error\nMap attributes are not valid.\n--> Affected line: ");
        ft_putstr_fd(line, 1);
        exit(1);
    }
	return (line);
}



void	check_chars_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != ' ' && line[i] != '\t')
		{  
			//free map
			show_error("Error!\ninvalid character in map\n");
			exit(1);
		}
		i++;
	}
}

char *ft_strdup_line(char *line, int len)
{
	int		i;
	char	*allocation;

	i = 0;
	allocation = malloc(len + 1);
	if (!allocation)
		return (NULL);
	while (i < len)
	{
		if (is_space(line[i]) || i >= ft_strlen(line))
			allocation[i] = 'x';
		else
			allocation[i] = line[i];
		i++;
	}
	allocation[i] = '\0';
	return (allocation);
}

void	parse_map(char *line1, char*path, t_config *co)
{
	char    *line;
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1){
		show_error("Error\nSpecified map doesn't exist, or doesn't have enough permissions.\n");
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, line1))
			break ;
		free(line);
		line = get_next_line(fd);			
	}
	co->map = (char **)malloc(sizeof(char *) * (co->map_height + 1));
	i = 0;
	while (line)
	{
		check_chars_map(line);
		co->map[i++] = ft_strdup_line(line, co->map_width);
		free(line);
		line = get_next_line(fd);
	}
	co->map[i] = NULL;
	free(line);
	close(fd);
}

void calculate_longest_line(int fd, char *line, t_config *config)
{
	int len;
	int j;

	len = 0;
	j = 0;
	while(line)
	{
		j++;
		if (ft_strlen(line) > len)
			len = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	config->map_width = len;
	config->map_height = j;
}

void	check_map_surroundings(t_config *config){
	int i;
	int j;

	i = 0;
	while (i < config->map_height)
	{
		j = 0;
		while (j < config->map_width)
		{
			if(config->map[i][j] != '1' && config->map[i][j] != 'x'){
				if((i - 1 < 0 || i + 1 >= config->map_height) || j - 1 < 0 || j + 1 >= config->map_width){
					printf("Error\nMap is not valid, invalid surroundings, check map[%d][%d]\n", i, j);
					exit(1);
				}
				if (config->map[i + 1][j] == 'x' || config->map[i - 1][j] == 'x' || config->map[i][j + 1] == 'x' || config->map[i][j - 1] == 'x')
				{
					printf("Error\nMap is not valid, invalid surroundings, check map[%d][%d]\n", i, j);
					exit(1);
				}
			}

			j++;
		}
		i++;
	}
	if (config->player.x == -1 || config->player.y == -1)
	{
		show_error("Error\nMap is not valid, it doesn't have a player.\n");
		exit(1);
	}
}

void	validate_map(char *path, t_config *config)
{
	int	fd;
	char *line;

	if (!has_extension(path, ".cub")){
		show_error("Error\nMap file is not valid, check the extension\n");
		exit(1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1){
		show_error("Error\nSpecified map doesn't exist, or doesn't have enough permissions.\n");
		exit(1);
	}
	line = parse_configs(fd, config);
	char *lin;
	lin = ft_strdup(line);
	calculate_longest_line(fd, lin, config);
	parse_map(line, path, config);
	check_map_surroundings(config);
	print_map(*config);
}

void	print_map(t_config config)
{
	int	i;

	printf("---------- IT'S WORKING !! -----------\n");
	i = 0;
	while(config.map[i]){
		printf("%s\n",config.map[i]);
		i++;
	}
	printf("--------------------------------------\n");
}