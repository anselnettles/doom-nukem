/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/11 18:23:17 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

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
/*
static void	draw_slot_filling(t_rain *r)
{

}*/

/*static void	draw_slot(t_rain *r)
{
	int i;
	i = 0;
	while (i != 3)
	{
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		i++;
		r->graph.y++;
		r->graph.x -= 2;
	}
	r->graph.y -= 3;
	i = 0;
	r->graph.color = SLOT;
		r->graph.x--;
		r->graph.y--;
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		r->graph.x += 2;
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		r->graph.y++;
		pixel_put(&r->graph);
		r->graph.x -= 4;
		pixel_put(&r->graph);
		r->graph.y += 2;
		pixel_put(&r->graph);
		r->graph.x += 4;
		pixel_put(&r->graph);
		r->graph.x -= 4;
		r->graph.y++;
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		r->graph.x += 2;
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		r->graph.x -= 3;
		r->graph.y -= 3;
}*/

static int	draw_playermap_tile(t_rain *r, char a[MAX_READ + 1][MAX_READ + 1], int x, int y)
{
	if (a[y][x] == '#' || a[y + 1][x] == '#' || a[y][x + 1] == '#'
			|| a[y +1][x + 1] == '#' || a[y][x] == '/'
			|| a[y + 1][x] == '/' || a[y][x + 1] == '/'
			|| a[y + 1][x + 1] == '/' || a[y][x] == '\\'
			|| a[y + 1][x] == '\\' || a[y][x + 1] == '\\'
			|| a[y + 1][x + 1] == '\\' || a[y][x] == '*'
			|| a[y + 1][x] == '*' || a[y][x + 1] == '*'
			|| a[y + 1][x + 1] == '*')
		pixel_put(&r->graph, r->graph.x, r->graph.y, WALL);
	else
		pixel_put(&r->graph, r->graph.x, r->graph.y, EMPTY);
	return (0);
}

static int	draw_devmap_tile(t_rain *r, char a[MAX_READ + 1][MAX_READ + 1], int x, int y)
{
	if (a[y][x] == '#' || a[y][x] == '/' || a[y][x] == '\\'
			|| a[y][x] == '*')
		pixel_put(&r->graph, r->graph.x, r->graph.y, WALL);
	else
		pixel_put(&r->graph, r->graph.x, r->graph.y, EMPTY);
	return (0);
}


/*
static uint32_t check_blockmap_tiles(t_editor *e, int x, int y)
{
	if (e->array[y][x] == '#' || e->array[y][x] == '/'
			|| e->array[y][x] == '\\' || e->array[y][x] == '*'
			|| e->array[y + 1][x] == '#' || e->array[y + 1][x] == '/
			|| e->array[y + 1][x] == '\\' || e->array[y + 1][x] == '*'
			|| e->array[y][x + 1] == '#' || e->array[y][x + 1] == '/'
			|| e->array[y][x + 1] == '\\' || e->array[y][x + 1] == '*'
			|| e->array[y + 1][x + 1] == '#' || e->array[y + 1][x + 1] == '/'
			|| e->array[y + 1][x + 1] == '\\' || e->array[y + 1][x + 1] == '*')
		return (WALL);
	else
		return (EMPTY);
}*/

/*static uint32_t	dev_map_tiles(t_editor *e, int x, int y)
{
	if (e->array[y][x] == '#' || e->array[y][x] == '/'
			|| e->array[y][x] == '\\' || e->array[y][x] == '*')
		return (WALL);
	else if (e->array[y][x] == '0')
		return (PIT);
	else if (e->array[y][x] >= '1' && e->array[y][x] <= '9')
		return (FLOOR);
	else if (e->array[y][x] == 'a')
		return (SKY);
	else if (e->array[y][x] >= 'b' && e->array[y][x] <= 'j')
		return (CEILING);
	else
		return (EMPTY);
}*/

static int	draw_arraymap(t_rain *r)
{
	int	x;
	int	y;

	write(1, "i wanna draw. ", 14);
	if (r->editor.array[0] != NULL) //how to make this check more useful?
	{
		r->graph.y = 10;
		r->graph.x = 460;			// default location for the map?
		x = 0;
		y = 0;
		while (y <= r->index.y)
		{
			while (x <= r->index.width)
			{
				write(1, "drawing. ", 9);
				if (r->graph.map == PLAYER_MAP)
				{
					write(1, "player map. ", 12);
					draw_playermap_tile(r, (char **)r->editor.array, x, y);
				}
				else if (r->graph.map == DEV_MAP)
					draw_devmap_tile(r, (char **)r->editor.array, x, y);
				write(1, " fun.", 5);
				draw_slot_outline(r);
				write(1, " outline managed.", 17);
				x++;
				if (r->graph.map == PLAYER_MAP)
					x++;
				r->graph.x += 6;
			}
			x = 0;
			r->graph.x = 460;
			y++;
			if (r->graph.map == PLAYER_MAP)
				y++;
			r->graph.y += 6;
		}
	}
	return (0);
}

int	render(t_rain *r)
{
	SDL_FillRect(r->graph.surf, NULL, 0);
	if (draw_arraymap(r) == ERROR)
		return (ERROR);
	//draw_space(r);
	SDL_UpdateWindowSurface(r->graph.win);
	write(1, "[Ren'd]", 7);
	return (0);
}

int	initialize(t_graph *g)
{
	if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_EVENTS) <= SDL_ERROR)
	{
		g->SDL_error_string = SDL_GetError();
		write(1, g->SDL_error_string, ft_strlen(g->SDL_error_string));
		return (ERROR);
	}
	g->scale = SCALE;
	g->width = WIDTH * g->scale;
	g->height = HEIGHT * g->scale;
	g->win = SDL_CreateWindow(TITLE, 0, 0, g->width, g->height, 0);
	g->surf = SDL_GetWindowSurface(g->win);
	if (g->win == NULL || g->surf == NULL)
	{
		g->SDL_error_string = SDL_GetError();
		write(1, g->SDL_error_string, ft_strlen(g->SDL_error_string));
		return (ERROR);
	}
	g->map = PLAYER_MAP;
	return (0);
}

int	graphic_interface(t_rain *rain)
{
	if (initialize(&rain->graph) == ERROR)
		return (error(SDL_FAIL));
	if (render(rain) == ERROR)
		return (error(RENDER_FAIL));
	sdl_loop(rain);
	return (0);
}
