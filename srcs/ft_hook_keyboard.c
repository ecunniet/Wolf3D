/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_keyboard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 12:02:04 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/24 23:29:34 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			ft_music(t_env *list)
{
	if (list->music.music_on == 1)
	{
		system("killall -c sh");
		system("killall afplay");
	}
	if (list->rainbow == 1)
		system("while(true); do afplay music/Rainbow.mp3; done &");
	else
		system("while(true); do afplay music/YuriOnIce.mp3; done &");
	list->music.pause_on = 0;
	list->music.music_on = 1;
}

static int		ft_key_funct(int keycode, t_env *list)
{
	if (keycode == RB && list->rainbow == 0)
	{
		list->rainbow = 1;
		ft_music(list);
	}
	else if (keycode == RB && list->rainbow == 1)
	{
		list->rainbow = 0;
		ft_music(list);
	}
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
	if (keycode == ESC)
		ft_exit(list);
	return (0);
}

int				ft_exit(t_env *list)
{
	ft_free(list->ymax, list);
	system("killall -c sh");
	system("killall afplay");
	exit(EXIT_SUCCESS);
}

int				ft_key_press(int keycode, t_env *list)
{
	if (keycode == UP)
		list->move.up = 1;
	if (keycode == DOWN)
		list->move.down = 1;
	if (keycode == A)
		list->move.viewl = 1;
	if (keycode == D)
		list->move.viewr = 1;
	if (keycode == RIGHT)
		list->move.right = 1;
	if (keycode == LEFT)
		list->move.left = 1;
	ft_key_funct(keycode, list);
	return (0);
}

int				ft_key_release(int keycode, t_env *list)
{
	keycode = 0;
	list->move.up = 0;
	list->move.down = 0;
	list->move.viewr = 0;
	list->move.viewl = 0;
	list->move.right = 0;
	list->move.left = 0;
	return (0);
}
