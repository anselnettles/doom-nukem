/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_minimap.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:06:00 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/18 15:56:41 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitter_cold_droplets_in_autumn_rain.h"

static void	draw_slot_outline(t_rain *r)
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
}

static void	draw_map_tile(t_rain *r, uint32_t color)
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
}

static void	draw_player_tile(t_rain *r, char a[MAX + 1][MAX + 1][MAX + 1])
{
	if (a[r->index.y][r->index.x][0] == '#')
		draw_map_tile(r, WALL);
	else
		draw_map_tile(r, EMPTY);
}

static void	draw_developer_tile(t_rain *r, char a[MAX + 1][MAX + 1][MAX + 1])
{
	if (a[r->index.y][r->index.x][0] == '#')
		draw_map_tile(r, WALL);
	else if (a[r->index.y][r->index.x][2] == '0')
		draw_map_tile(r, PIT);
	else if (a[r->index.y][r->index.x][2] >= '1'
			&& a[r->index.y][r->index.x][2] <= '9')
		draw_map_tile(r, FLOOR);
	else if (a[r->index.y][r->index.x][3] == 'a')
		draw_map_tile(r, SKY);
	else if (a[r->index.y][r->index.x][3] >= 'b'
			&& a[r->index.y][r->index.x][3] <= 'j')
		draw_map_tile(r, CEILING);
	else if (a[r->index.y][r->index.x][1] == 'S')
		draw_map_tile(r, START_POINT);
	else
		draw_map_tile(r, EMPTY);
}

void	draw_minimap_slot(t_rain *r)
{
	if (r->graph.map == PLAYER_MAP)
		draw_player_tile(r, r->editor.map);
	else
		draw_developer_tile(r, r->editor.map);
	draw_slot_outline(r);
}
