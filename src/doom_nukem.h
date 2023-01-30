/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:56:34 by tpaaso            #+#    #+#             */
/*   Updated: 2023/01/30 14:36:30 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# include <SDL2/SDL.h>

# ifdef __APPLE__
#  include "SDL_image.h"
# elif __linux__
#  include <SDL2/SDL_image.h>

# endif

# include "../libft/libft.h"
# define PI 3.1415927
# define DEGREES 0.0174532
# define SPEED 10			//players step size
# define BITS 64			//elements size
# define WIDTH 1280			//window width
# define HEIGHT 800			//window height
# define MMWIDTH 420		//minimap width
# define MMHEIGHT 200		//minimap height
# define LIMIT 100			//map size limit
# define THREAD 6			//amount of threads
# define THREADRAY 213		//amount of rays per thread

typedef struct s_map
{
	char	**map;
	int		y_max;
	int		x_max;
}			t_map;

typedef struct s_texture
{
	Uint32	texture[64][64];
}			t_texture;

typedef struct s_player
{
	float		x;
	float		y;
	float		dir;
	float		dx;
	float		dy;
	int		height;
	int		flag;
}				t_player;

typedef struct s_wall
{
	float		x;
	float		y;
	float		dir;
	float		dx;
	float		dy;
	struct s_player *next;
}				t_wall;

typedef struct s_ray
{
	SDL_Window	*window;
	t_player	player;
	t_map		map;
	float		distance;
	float		dir;
	int			x;
	int			count;
	int			height;
}				t_ray;

typedef struct s_main
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	SDL_Surface	*image;
	SDL_Event	event;
	SDL_Rect	rect;
	SDL_bool	cursor;
	int			option;
	t_player	player;
	t_map		map;
	int			height;
	int			thread;
}				t_main;

enum e_option
{
	EXIT = 0,
	PLAY = 1,
};

void	map_len(char *file, t_map *data);
char	*copy_line(char *line, t_map *data);
void	fill_gaps(char *line);
void	read_map(char *file, t_map *data);
int		init_sdl(SDL_Window *window, SDL_Surface *screen);
void	draw_map(t_main *data);
void	init_player(t_player *player);
void	move_player(int key, t_player *player, t_map map);
void	rotate_player(int key, t_player *player);
void	clear_screen(t_main *data);
void	deal_key(int key, t_main *data);
void	deal_mouse(t_main *data);
void    render_thread(t_main *data);
void	*ft_raycast_thread(void  *args);
void	strife(int key, t_player *player, t_map map);
void	draw_thread(t_ray *ray, float distance, t_wall wall);
void	pixel_put(SDL_Surface *screen, int x, int y, Uint32 color);
void	init_values(t_main *data);
void	init_data(t_main *data);

#endif
