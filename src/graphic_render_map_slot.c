/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_map_slot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:06:00 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/21 12:09:54 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static int	draw_slot_outline(t_rain *r)
{
	pixel_put(&r->graph, r->graph.x - 1, r->graph.y - 1, SLOT);
	pixel_put(&r->graph, r->graph.x, r->graph.y - 1, SLOT);
	pixel_put(&r->graph, r->graph.x + 2, r->graph.y - 1, SLOT);
	pixel_put(&r->graph, r->graph.x + 3, r->graph.y - 1, SLOT);
	pixel_put(&r->graph, r->graph.x - 1, r->graph.y, SLOT);
	pixel_put(&r->graph, r->graph.x + 3, r->graph.y, SLOT);
	pixel_put(&r->graph, r->graph.x - 1, r->graph.y + 2, SLOT);
	pixel_put(&r->graph, r->graph.x + 3, r->graph.y + 2, SLOT);
	pixel_put(&r->graph, r->graph.x - 1, r->graph.y + 3, SLOT);
	pixel_put(&r->graph, r->graph.x, r->graph.y + 3, SLOT);
	pixel_put(&r->graph, r->graph.x + 2, r->graph.y + 3, SLOT);
	pixel_put(&r->graph, r->graph.x + 3, r->graph.y + 3, SLOT);
	return (0);
}

static int	draw_map_tile(t_rain *r, int color)
{
	pixel_put(&r->graph, r->graph.x, r->graph.y, color);
	pixel_put(&r->graph, r->graph.x + 1, r->graph.y, color);
	pixel_put(&r->graph, r->graph.x + 2, r->graph.y, color);
	pixel_put(&r->graph, r->graph.x, r->graph.y + 1, color);
	pixel_put(&r->graph, r->graph.x + 1, r->graph.y + 1, color);
	pixel_put(&r->graph, r->graph.x + 2, r->graph.y + 1, color);
	pixel_put(&r->graph, r->graph.x, r->graph.y + 2, color);
	pixel_put(&r->graph, r->graph.x + 1, r->graph.y + 2, color);
	pixel_put(&r->graph, r->graph.x + 2, r->graph.y + 2, color);
	return (0);
}

static int	draw_pl_tile(t_rain *r, char a[MAX + 1][MAX + 1], int x, int y)
{
	if (a[y][x] == '#' || a[y + 1][x] == '#' || a[y][x + 1] == '#'
			|| a[y +1][x + 1] == '#' || a[y][x] == '/'
			|| a[y + 1][x] == '/' || a[y][x + 1] == '/'
			|| a[y + 1][x + 1] == '/' || a[y][x] == '\\'
			|| a[y + 1][x] == '\\' || a[y][x + 1] == '\\'
			|| a[y + 1][x + 1] == '\\' || a[y][x] == '*'
			|| a[y + 1][x] == '*' || a[y][x + 1] == '*'
			|| a[y + 1][x + 1] == '*')
		draw_map_tile(r, WALL);
	else
		draw_map_tile(r, EMPTY);
	return (0);
}

static int	draw_dev_tile(t_rain *r, char a[MAX + 1][MAX + 1], int x, int y)
{
	if (a[y][x] == '#' || a[y][x] == '/' || a[y][x] == '\\'
			|| a[y][x] == '*')
		draw_map_tile(r, WALL);
	else if (a[y][x] == '0')
		draw_map_tile(r, PIT);
	else if (a[y][x] >= '1' && a[y][x] <= '9')
		draw_map_tile(r, FLOOR);
	else if (a[y][x] == 'a')
		draw_map_tile(r, SKY);
	else if (a[y][x] >= 'b' && a[y][x] <= 'j')
		draw_map_tile(r, CEILING);
	else
		draw_map_tile(r, EMPTY);
	return (0);
}

int	draw_map_slot(t_rain *r, int x, int y)
{
	if (r->graph.map == PLAYER_MAP)
		draw_pl_tile(r, (char **)r->editor.array, x, y);
	else if (r->graph.map == DEV_MAP)
		draw_dev_tile(r, (char **)r->editor.array, x, y);
	draw_slot_outline(r);
	x++;
	if (r->graph.map == PLAYER_MAP)
		x++;
	r->graph.x += 6;
	return (x);
}
