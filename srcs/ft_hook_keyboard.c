/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_keyboard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 12:02:04 by ecunniet          #+#    #+#             */
/*   Updated: 2017/04/25 12:02:14 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_music(t_env *list)
{
	if (list->music.music_on == 1)
	{
		system("killall -c sh");
		system("killall afplay");
	}
	if (list->i == 1)
		system("while(true); do afplay Julia.mp3; done &");
	if (list->i == 2)
		system("while(true); do afplay Mandelbrot.mp3; done &");
	if (list->i == 3)
		system("while(true); do afplay Burning_Ship.mp3; done &");
	list->music.music_on = 1;
}

static int	ft_key_funct(int keycode, t_env *list)
{
	int		tmp;

	tmp = list->i;
	list->i = (keycode == ONE) ? 1 : list->i;
	list->i = (keycode == TWO) ? 2 : list->i;
	list->i = (keycode == THREE) ? 3 : list->i;
	if (list->i != tmp)
		ft_init(list);
	if (keycode == MUSIC && list->music.pause_on == 0)
	{
		system("killall -STOP afplay");
		list->music.pause_on = 1;
	}
	else if (keycode == MUSIC && list->music.pause_on == 1)
	{
		system("killall -CONT afplay");
		list->music.pause_on = 0;
	}
	if (keycode == PAUSE)
		list->move.pause = (list->move.pause == 0) ? 1 : 0;
	(keycode == ESC) ? ft_exit(list) : 0;
	return (0);
}

int			ft_key_press(int keycode, t_env *list)
{
	list->move.i_more = (keycode == I) ? 1 : 0;
	list->move.i_less = (keycode == O) ? 1 : 0;
	list->move.z_more = (keycode == MORE) ? 1 : 0;
	list->move.z_less = (keycode == LESS) ? 1 : 0;
	list->move.up = (keycode == UP) ? 1 : 0;
	list->move.down = (keycode == DOWN) ? 1 : 0;
	list->move.right = (keycode == RIGHT) ? 1 : 0;
	list->move.left = (keycode == LEFT) ? 1 : 0;
	ft_key_funct(keycode, list);
	return (0);
}

int			ft_key_release(int keycode, t_env *list)
{
	list->move.i_more = 0;
	list->move.i_less = 0;
	list->move.z_more = 0;
	list->move.z_less = 0;
	list->move.up = 0;
	list->move.down = 0;
	list->move.right = 0;
	list->move.left = 0;
	return (0);
}

int			ft_loop_ok(t_env *list)
{
	if (list->frac.i_max > 0)
		list->frac.i_max += (list->move.i_more - list->move.i_less);
	if (list->frac.i_max == 0)
		list->frac.i_max += list->move.i_more;
	if (list->move.z_more != 0 || list->move.z_less != 0)
		list->frac.zoom *= ((list->move.z_more * pow(1.001, FPS))
		+ (list->move.z_less / pow(1.001, FPS)));
	list->frac.movey += (list->move.down - list->move.up) *
	(0.0013 * FPS / list->frac.zoom);
	list->frac.movex += (list->move.right - list->move.left) *
	(0.0013 * FPS / list->frac.zoom);
	ft_fractal(list);
	return (0);
}
