/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_class.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:02:13 by isalama           #+#    #+#             */
/*   Updated: 2023/09/14 18:48:53 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void parse_configs(char *str){
    int fd;
    int total_attrs;
    char *line;
    int i;
    bool found_map;
    
    total_attrs = 0;
    fd = open(str, O_RDONLY);
    if (fd == -1)
        show_error("Error\nMap file is not valid\n");
   
    line = get_next_line(fd);
    while (line){
        
        if ((line[0] == 'N' && line[1] == 'O') || 
        (line[0] == 'S' && line[1] == 'O') || 
        (line[0] == 'W' && line[1] == 'E') ||
        (line[0] == 'E' && line[1] == 'A') || 
        (line[0] == 'F' && line[1] == ' ') ||
        (line[0] == 'C' && line[1] == ' '))
            total_attrs++;
        else
        {
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
    close(fd);
    if (total_attrs != 6){
        show_error("Error\nMap file is not valid\n");
        exit(1);
    }
}
