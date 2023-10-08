/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class_getline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:21:41 by isalama           #+#    #+#             */
/*   Updated: 2023/10/08 20:05:43 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	gnl_strlen(const char *str)
{
	int	l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}

int	ft_new_line(const char *str)
{
	while (str && *str && str++)
		if (*str == '\n')
			return (0);
	return (1);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		l;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		*s1 = 0;
	}
	l = gnl_strlen(s1) + gnl_strlen(s2);
	str = (char *)malloc(l + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[l] = 0;
	return (free(s1), str);
}

static char	*rtn_l(char	*ln)
{
	int		i;
	char	*l;

	if (!*ln)
		return (NULL);
	i = 0;
	while (ln[i] && ln[i] != '\n')
		i++;
	if (ln[i] == '\0')
		l = (char *)malloc(i + 1);
	else
		l = (char *)malloc(i + 2);
	i = -1;
	while (ln[++i] && ln[i] != '\n')
		l[i] = ln[i];
	l[i] = 0;
	return (l);
}

static char	*rtn_p(char	*pos)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	while (pos[i] && pos[i] != '\n')
		i++;
	if (!pos[i])
		return (free(pos), NULL);
	p = (char *)malloc(gnl_strlen(pos) - i + 1);
	if (!p)
		return (NULL);
	j = 0;
	while (pos[++i])
		p[j++] = pos[i];
	p[j] = 0;
	return (free(pos), p);
}

char	*get_next_line(int fd)
{
	int			rd;
	char		*line;
	char		*buffer;
	static char	*position;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	rd = 1;
	while (ft_new_line(position) && rd)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
			return (free(buffer), NULL);
		buffer[rd] = 0;
		position = gnl_strjoin(position, buffer);
	}
	line = rtn_l(position);
	return (position = rtn_p(position), free(buffer), line);
}
