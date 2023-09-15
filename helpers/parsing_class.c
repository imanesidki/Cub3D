/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_class.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:02:13 by isalama           #+#    #+#             */
/*   Updated: 2023/09/15 22:03:50 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool parse_configs_helper(char *line, int mode, t_config *config){
    if(mode == 0){
        if(ft_strncmp(line, "NO", 2)){
            config->no_texture = ft_strdup(line);
            return (true);
        } else if(ft_strncmp(line, "SO", 2)){
            config->so_texture = ft_strdup(line);
            return (true);
        } else if(ft_strncmp(line, "WE", 2)){
            config->we_texture = ft_strdup(line);
            return (true);
        } else if(ft_strncmp(line, "EA", 2)){
            config->ea_texture = ft_strdup(line);
            return (true);
        }
    }
    if(mode == 1){
        return (!has_extension(line, ".xpm"));
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
        } else return (false);
    }
    return (true);
}

void parse_configs(int fd, t_config *config){
    int total_attrs;
    char *line;
    int i;
    bool found_map;

    total_attrs = 0;
    line = get_next_line(fd);
    while (line){
        if (parse_configs_helper(line, 0, config)){
            if (parse_configs_helper(line, 1, config)){
                show_error("Error\nMap textures are not valid, invalid extension.\n");
                exit(1);
            }
            total_attrs++;
        } else if((line[0] == 'F' || line[0] == 'C') && line[1] == ' '){
            if (!parse_colors(line, config, line[0] == 'F')){
                show_error("Error\nMap colors are not valid\n");
                exit(1);
            }
            total_attrs++;
        } else {
            i = 0;
            found_map = false;
            while(line[i]){
                if (line[i] == '1' || line[i] == '0')
                    found_map = true;
                i++;
            }
            if (found_map)
                break;
        }
        free(line);
        line = get_next_line(fd);
    }
    if (total_attrs != 6){
        show_error("Error\nMap attributes are not valid\n");
        exit(1);
    }
}

void parse_map(int fd){
    close(fd);
}

void validate_map(char *path, t_config *config){
    int fd;

    if (!has_extension(path, ".cub")){
        show_error("Error\nMap file is not valid, check the extension\n");
        exit(1);
    }
    fd = open(path, O_RDONLY);
    if (fd == -1){
        show_error("Error\nSpecified map doesn't exist, or doesn't have enough permissions.\n");
        exit(1);
    }
    parse_configs(fd, config);
    parse_map(fd);
}