/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:28:01 by tpaaso            #+#    #+#             */
/*   Updated: 2023/01/26 16:26:27 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
 * It takes a line of the map, and converts it into a string of the 
 * same length as the map's width.
 * @return A string of characters.
 */
char	*copy_line(char *line, t_map *data)
{
	char	*str;
	int		i;
	int		x;

	i = 0;
	x = 0;
	str = (char *)malloc(sizeof(char) * (unsigned long)data->x_max + 1);
	if (str == NULL)
		ft_exit("malloc error");
	while (i < (int)ft_strlen(line))
	{
		while (x <= (i + 1) * BITS - 1)
		{
			str[x] = line[i];
			x++;
		}
		i++;
	}
	while (x - 1 < data->x_max)
	{
		str[x - 1] = '0';
		x++;
	}
	str[x - 1] = '\0';
	return (str);
}

/*
 * It opens the file, reads the first line, and then reads the rest 
 * of the file to determine the size of the map.
 */
void	map_len(char *file, t_map *data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (get_next_line(fd, &line) <= 0)
		ft_exit("error; invalid file");
	if (line == NULL)
		ft_exit("error");
	data->x_max = (int)ft_strlen(line) * BITS;
	free(line);
	while (get_next_line(fd, &line))
	{
		i++;
		if ((int)ft_strlen(line) * BITS > data->x_max)
			data->x_max = (int)ft_strlen(line) * BITS;
		free(line);
	}
	if (data->x_max <= 2 * BITS || i < 2
		|| data->x_max >= LIMIT * BITS || i > LIMIT - 1)
		ft_exit("error; invalid map");
	i++;
	fd = close(fd);
	data->y_max = i * BITS;
}

/*
 * It takes a string and fills it with '#' characters
 * @param line the line that is being filled with #'s
 */
void	fill_gaps(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\0')
		ft_exit("error; empty line");
	while (line [i] != '\0')
	{
		line[i] = '0';
		i++;
	}
}

/*
 * It reads the map file,
 * and fills the data->map array with the map.
 * @param file the name of the file to be read
 */
void	read_map(char *file, t_map *data)
{
	int		fd;
	char	*line;
	int		i;
	int		y;

	i = 0;
	y = 0;
	map_len(file, data);
	data->map = (char **)malloc(sizeof(char *) * (unsigned long)data->y_max);
	if (data->map == NULL)
		ft_exit("malloc error");
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (line[0] == ' ')// || y == 0 || y > data->y_max - BITS * 2)
			fill_gaps(line);
		while (y <= (i + 1) * BITS - 1)
		{
			data->map[y] = copy_line(line, data);
			y++;
		}
		i++;
		free(line);
	}
	fd = close(fd);
}
