#include "drowning.h"

void		collect_airbottle(t_drown *d)
{
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	Mix_PlayChannel(-1, d->audio.inhale, 0);
	d->gfx.frame.right_arm = 3;
}

int		player_object_collision(t_drown *d, int s)
{
	if (d->map.map[(int)roundf(d->player.y / 64)]
		[(int)roundf(d->player.x / 64)][3] == 'Z')
		d->system.ending_state = REGULAR_ENDING;
	if (d->map.map[(int)roundf(d->player.y / 64)]
		[(int)roundf(d->player.x / 64)][3] == '$')
	{
		if (d->system.keyboard_state[SDL_SCANCODE_E])
		{
			d->map.map[(int)roundf(d->player.y / 64)]
			[(int)roundf(d->player.x / 64)][3] = '.';
			collect_airbottle(d);
		}
	}
		return (0);
}
