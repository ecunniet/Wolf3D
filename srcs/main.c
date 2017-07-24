/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <ecunniet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:27:38 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/24 23:39:33 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int		ft_draw_pix(t_env *list)
{
	list->mlx = mlx_init();
	list->win = mlx_new_window(list->mlx, WIDTH, HEIGHT, "Wolf3D");
	list->img_ptr = mlx_new_image(list->mlx, WIDTH, HEIGHT);
	list->adi = mlx_get_data_addr(list->img_ptr, &list->bpp,
	&list->size_line, &list->endian);
	list->music.music_on = 0;
	ft_music(list);
	ft_ray(0, list);
	mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	mlx_hook(list->win, KEYPRESSEVENT, KEYPRESSMASK, &ft_key_press, list);
	mlx_hook(list->win, KEYRELEASEEVENT, KEYRELEASEMASK,
	&ft_key_release, list);
	mlx_hook(list->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, &ft_exit, list);
	mlx_loop_hook(list->mlx, &ft_loop, list);
	mlx_loop(list->mlx);
	return (0);
}

void			ft_init(t_env *list)
{
	list->move.up = 0;
	list->move.down = 0;
	list->move.right = 0;
	list->move.left = 0;
	MO = 0.2;
	ROT = 0.05;
	list->rainbow = 0;
	*(list->r) = 0xf40000;
	*(list->r + 1) = 0xffa500;
	*(list->r + 2) = 0xf4f400;
	*(list->r + 3) = 0x00f400;
	*(list->r + 4) = 0x0028f4;
	*(list->r + 5) = 0xa300f4;
}

void			ft_define(t_env *list)
{
	list->xmax = 8;
	list->ymax = 8;
	PLAY.x = 4;
	PLAY.y = 4;
	PLAY.dirx = -1;
	PLAY.diry = 0;
	PLAY.planex = 0;
	PLAY.planey = 0.66;
}

void			ft_default_map(t_env *list, int i, int x)
{
	ft_define(list);
	if (!(list->map = (int **)malloc(sizeof(int *)
	* list->ymax)))
		exit(EXIT_FAILURE);
	while (i < list->ymax)
	{
		if (!(list->map[i] = (int *)malloc(sizeof(int) * list->xmax)))
		{
			ft_free(i - 1, list);
			exit(EXIT_FAILURE);
		}
		x = 0;
		while (x < list->xmax)
		{
			if (i == 0 || i == list->ymax - 1 || x == 0 || x == list->xmax - 1)
				list->map[i][x] = 1;
			else
				list->map[i][x] = 0;
			x++;
		}
		i++;
	}
}

int				main(int argc, char **argv)
{
	t_env	list;

	if (argc == 1)
	{
		ft_default_map(&list, 0, 0);
		ft_init(&list);
		ft_draw_pix(&list);
	}
	else if (argc == 2)
	{
		ft_init(&list);
		ft_verif_name(argv[1], &list);
		ft_draw_pix(&list);
	}
	else
		ft_error(argc, 0);
	return (0);
}
