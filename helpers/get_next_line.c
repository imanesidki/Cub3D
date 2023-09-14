/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:21:41 by isalama           #+#    #+#             */
/*   Updated: 2023/09/14 18:11:53 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_linebreak_position(char *working_string)
{
	int	index;

	index = 0;
	if (!working_string)
		return (0);
	while (working_string[index] != '\0' && working_string[index] != '\n')
		index++;
	if (working_string[index] == '\n')
		index++;
	return (index);
}

char	*read_file_into(char *working_string, int fd)
{
	char	*buffer;
	int		read_size;

	read_size = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (read_size != 0)
	{
		if (ft_strchr(working_string, '\n'))
			break ;
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
			return (free(working_string), free(buffer), NULL);
		buffer[read_size] = '\0';
		working_string = ft_strjoin(working_string, buffer);
	}
	free (buffer);
	return (working_string);
}

char	*get_single_line(char *working_string)
{
	int	index;

	index = get_linebreak_position(working_string);
	if (index == 0)
		return (NULL);
	return (ft_substr(working_string, 0, index));
}

char	*get_the_rest(char *working_string)
{
	int		index;
	char	*str;

	index = get_linebreak_position(working_string);
	if (index == 0)
		return (NULL);
	str = ft_substr(working_string, index, ft_strlen(working_string));
	free(working_string);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*working_string;
	char		*single_line;

	if (fd < 0 	|| BUFFER_SIZE <= 0)
		return (NULL);
	working_string = read_file_into(working_string, fd);
	single_line = get_single_line(working_string);
	working_string = get_the_rest(working_string);
	return (single_line);
}
