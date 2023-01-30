/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_minimap.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:06:00 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/27 17:39:48 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"
/*
static void	draw_slot_outline(t_drown *d)
{
	pixel_put(&d->graph, d->graph.x - 1, d->graph.y - 1, SLOT);
	pixel_put(&d->graph, d->graph.x, d->graph.y - 1, SLOT);
	pixel_put(&d->graph, d->graph.x + 2, d->graph.y - 1, SLOT);
	pixel_put(&d->graph, d->graph.x + 3, d->graph.y - 1, SLOT);
	pixel_put(&d->graph, d->graph.x - 1, d->graph.y, SLOT);
	pixel_put(&d->graph, d->graph.x + 3, d->graph.y, SLOT);
	pixel_put(&d->graph, d->graph.x - 1, d->graph.y + 2, SLOT);
	pixel_put(&d->graph, d->graph.x + 3, d->graph.y + 2, SLOT);
	pixel_put(&d->graph, d->graph.x - 1, d->graph.y + 3, SLOT);
	pixel_put(&d->graph, d->graph.x, d->graph.y + 3, SLOT);
	pixel_put(&d->graph, d->graph.x + 2, d->graph.y + 3, SLOT);
	pixel_put(&d->graph, d->graph.x + 3, d->graph.y + 3, SLOT);
}

static void	draw_map_tile(t_drown *d, uint32_t color)
{
	pixel_put(&d->graph, d->graph.x, d->graph.y, color);
	pixel_put(&d->graph, d->graph.x + 1, d->graph.y, color);
	pixel_put(&d->graph, d->graph.x + 2, d->graph.y, color);
	pixel_put(&d->graph, d->graph.x, d->graph.y + 1, color);
	pixel_put(&d->graph, d->graph.x + 1, d->graph.y + 1, color);
	pixel_put(&d->graph, d->graph.x + 2, d->graph.y + 1, color);
	pixel_put(&d->graph, d->graph.x, d->graph.y + 2, color);
	pixel_put(&d->graph, d->graph.x + 1, d->graph.y + 2, color);
	pixel_put(&d->graph, d->graph.x + 2, d->graph.y + 2, color);
}

static void	draw_player_tile(t_drown *d, char a[MAX + 1][MAX + 1][PARAMS + 1])
{
	if (a[d->index.y][d->index.x][0] == '#')
		//draw_map_tile(r, WALL);
	else
		//draw_map_tile(r, EMPTY);
}

static void	draw_developer_tile(t_drown *d, char a[MAX + 1][MAX + 1][PARAMS + 1])
{
	if (a[d->index.y][d->index.x][0] == '#')
		draw_map_tile(r, WALL);
	else if (a[d->index.y][d->index.x][2] == '0')
		draw_map_tile(r, PIT);
	else if (a[d->index.y][d->index.x][2] >= '1'
			&& a[d->index.y][d->index.x][2] <= '9')
		draw_map_tile(r, FLOOR);
	else if (a[d->index.y][d->index.x][3] == 'a')
		draw_map_tile(r, SKY);
	else if (a[d->index.y][d->index.x][3] >= 'b'
			&& a[d->index.y][d->index.x][3] <= 'j')
		draw_map_tile(r, CEILING);
	else if (a[d->index.y][d->index.x][1] == 'S')
		draw_map_tile(r, START_POINT);
	else
		draw_map_tile(r, EMPTY);
}

void	draw_minimap_slot(t_drown *d)
{
	//if (d->graph.map == PLAYER_MAP)
	//	draw_player_tile(r, d->editor.map);
	//else
	//	draw_developer_tile(r, d->editor.map);
	//draw_slot_outline(r);
}*/
