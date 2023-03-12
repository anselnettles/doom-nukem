/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_read_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:04:35 by tturto            #+#    #+#             */
/*   Updated: 2023/03/12 17:15:09 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
    Inserts the values from char *buf into char ***map.
*/
static void	buffer_to_3d_map_array(char *buf, t_map *map)
{
	t_index	i;

	i = (t_index){.i0 = 0, .i1 = 0, .i2 = 0};
	while (*buf != 'A')
	{
		while (*buf != ' ' && *buf != '\n' && *buf != 'A')
		{
			map->map[i.i2][i.i1][i.i0] = *buf;
			i.i0++;
			buf++;
		}
		if (*buf == ' ')
		{
			i.i0 = 0;
			i.i1++;
			buf++;
		}
		if (*buf == '\n')
		{
			i.i0 = 0;
			i.i1 = 0;
			i.i2++;
			buf++;
		}
	}
}

static void	malloc_3d_map_array(t_map *map, t_editor_images *images)
{
	int	row;
	int	col;

	row = 0;
	map->map = (char ***)malloc(sizeof(char **) * images->row1);
	if (!map->map)
		tt_errors_exit("malloc_3d_map_array(): map[X][][]");
	while (row < images->row1)
	{
		map->map[row] = (char **)malloc(sizeof(char *) * images->column1);
		if (!map->map[row])
			tt_errors_exit("malloc_3d_map_array(): map[][X][]");
		col = 0;
		while (col < images->column1)
		{
			map->map[row][col] = (char *)malloc(sizeof(char)
					* (PARAM_COUNT + 1));
			if (!map->map[row][col])
				tt_errors_exit("malloc_3d_map_array() fail: map[][][X]");
			map->map[row][col][PARAM_COUNT] = '\0';
			col++;
		}
		row++;
	}
}

/*
	Counts rows and columns of the map file.
		Map file is standardized to be square-shaped.

	Each map element has been agreed to contain PARAM_COUNT# elements,
		thus number of columns per row is (row_bytes / PARAM_COUNT).
	Addition "+ 1" to row_bytes is only a beauty element,
		since after the last map element there is '\n' instead of ' '.
		Addition "+ 1" to PARAM_COUNT negates ' ' between the elements.
*/
static void	count_map_data(char *buf, t_editor_images *images)
{
	int	row_bytes;

	row_bytes = 0;
	while (*buf != '\n')
	{
		row_bytes++;
		buf++;
	}
	images->column1 = (row_bytes + 1) / (PARAM_COUNT + 1);
	while (*buf != 'A')
	{
		if (*buf == '\n')
			images->row1++;
		buf++;
	}
}

int	calculate_map_size(char *map_file)
{
	int		size;
	int		ret;
	int		fd;
	char	buf[1000 + 1];

	size = 0;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit (-1);
	ret = read(fd, buf, 1000);
	while (ret)
	{
		buf[ret] = '\0';
		size += ft_strlen(buf);
		ret = read(fd, buf, 1000);
	}
	if (ret == (-1))
		exit (-1);
	if (close(fd) == -1)
		exit (-1);
	return (size);
}

/*
    Reads a map file into a char *buf and converts the buf to char ***map.

	open_check and read_check functions are located
		in editor_utilities_open_read_check.
*/
int	read_map(char *map_file, t_drown *data)
{
	int		fd;
	int		ret;
	int		size;
	char	*buf;

	size = calculate_map_size(map_file);
	buf = (char *)malloc(sizeof(char) * size + 1);
	if (buf == NULL)
		exit (-1);
	open_check(&fd, map_file);
	read_check(fd, &ret, buf, size);
	buf[ret] = '\0';
	if (validate_buffer_format(buf, &data->editor.images) != 1)
		tt_errors_exit("read_map: validate_buffer_format() fail.");
	close(fd);
	if (texture_allocation(buf, &data->index, &data->gfx) == ERROR)
		return (ERROR);
	count_map_data(buf, &data->editor.images);
	malloc_3d_map_array(&data->map, &data->editor.images);
	buffer_to_3d_map_array(buf, &data->map);
	return (0);
}
