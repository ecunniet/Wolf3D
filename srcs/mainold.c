/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debutwolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <ecunniet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:27:38 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/07 12:59:15 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
void			ft_check_wall_v(t_env *list)
{
	if (list->player.angle >= 90 && list->player.angle < 270)
	{
		list->wall.xb = -64;
		list->wall.v_x = (int)((list->player.x - 32) / 64) * 64 - 1;
	}
	else
	{
		list->wall.xb = 64;
		list->wall.v_x = (int)((list->player.x - 32) / 64) * 64 + 64;
	}
	list->wall.v_y = list->player.y;
	list->wall.yb = 0;
	if (list->player.angle - 30  != 180 && list->player.angle - 30 != 0)
	{
		ft_putendl("hello2");
		list->wall.v_y += (list->player.x - list->wall.v_x) * tan((list->player.angle - 30) * M_PI / 180);
		list->wall.yb = 64 * tan((list->player.angle - 30) * M_PI / 180);
	}
	ft_putnbr(list->wall.v_y);
	ft_putchar('\n');
	ft_putnbr(list->wall.v_x);
	ft_putendl("hello3");
	ft_putnbr(list->map[(int)(list->wall.v_y / 64)][(int)(list->wall.v_x / 64)]);
	ft_putchar('\n');
	while (list->map[(int)(list->wall.v_y / 64)][(int)(list->wall.v_x / 64)] == 0)
	{
		ft_putchar('\n');
		ft_putnbr(list->wall.v_y);
		ft_putchar('\n');
		ft_putnbr(list->wall.v_x);
		list->wall.v_y += list->wall.yb;
		list->wall.v_x += list->wall.xb;
	}
	ft_putendl("hey");
	ft_putnbr(list->wall.v_y);
	ft_putchar('\n');
	ft_putnbr(list->wall.v_x);
	ft_putendl("hello3");
}

void			ft_check_wall_h(t_env *list)
{
	if (list->player.angle >= 0 &&	list->player.angle < 180)
	{
		list->wall.ya = -64;
		list->wall.h_y = (int)((list->player.y - 32) / 64) * 64 - 1;
	}
	else
	{
		list->wall.ya = 64;
		list->wall.h_y = (int)((list->player.y - 32) / 64) * 64 + 64;
	}
	list->wall.h_x = list->player.x;
	list->wall.xa = 0;
	if (list->player.angle - 30 != 90 && list->player.angle - 30 != 270)
	{
		ft_putendl("hello");
		list->wall.h_x += (list->player.y - list->wall.h_y) / tan((list->player.angle - 30) * M_PI / 180);
		list->wall.xa = 64 / tan((list->player.angle - 30) * M_PI / 180);
	}
	ft_putnbr(list->wall.h_y);
	ft_putchar('\n');
	ft_putnbr(list->wall.h_x);
	ft_putchar('\n');
	ft_putnbr(list->map[(int)(list->wall.h_y / 64)][(int)(list->wall.h_x / 64)]);
	while (list->map[(int)(list->wall.h_y / 64)][(int)(list->wall.h_x / 64)] == 0)
	{
		ft_putchar('\n');
		ft_putnbr(list->wall.h_y);
		ft_putchar('\n');
		ft_putnbr(list->wall.h_x);
		ft_putchar('\n');
		list->wall.h_y += list->wall.ya;
		list->wall.h_x += list->wall.xa;
	}
	ft_putendl("hey");
	ft_putnbr(list->wall.h_y);
	ft_putchar('\n');
	ft_putnbr(list->wall.h_x);
	ft_putendl("hello3");
}

void			ft_find_wall(t_env *list)
{
	if (list->player.angle - 30 != 180 && list->player.angle - 30 != 0)
		ft_check_wall_h(list);
	if (list->player.angle - 30 != 90 && list->player.angle - 30 != 270)
		ft_check_wall_v(list);
}
*/

void			ft_find_wall(t_env *list)
{
	//hello
}

static int		ft_draw_pix(t_env *list)
{
	list->mlx = mlx_init();
	list->win = mlx_new_window(list->mlx, WIDTH, HEIGHT, "Wolf3D");
	list->img_ptr = mlx_new_image(list->mlx, WIDTH, HEIGHT);
	list->adi = mlx_get_data_addr(list->img_ptr, &list->bpp,
	&list->size_line, &list->endian);
//	list->music.music_on = 0;
//	ft_init(list);
	ft_find_wall(list);
	mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
//	mlx_hook(list->win, KEYPRESSEVENT, KEYPRESSMASK, &ft_key_press, list);
//	mlx_hook(list->win, KEYRELEASEEVENT, KEYRELEASEMASK,
//	&ft_key_release, list);
//	mlx_hook(list->win, MOTIONNOTIFY, POINTERMOTIONMASK,
//	&ft_mouse_motion, list);
//	mlx_hook(list->win, BUTTONPRESS, BUTTONPRESSMASK, &ft_button_press, list);
//	mlx_hook(list->win, BUTTONRELEASE, BUTTONRELEASEMASK,
//	&ft_button_release, list);
//	mlx_hook(list->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, &ft_exit, list);
//	mlx_loop_hook(list->mlx, &ft_loop_ok, list);
	mlx_loop(list->mlx);
	return (0);
}

int				main(int argc, char **argv)
{
	t_env	list;

	if (argc == 2)
	{
		ft_verif_name(argv[1], &list);
		ft_draw_pix(&list);
	}
	else
		ft_error(argc,  0);
	return (0);
}
