/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <ecunniet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:27:38 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/07 12:59:15 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			ft_find_distance(t_env *list)
{
	if (list->ray.side == 0)
		list->ray.perpwalldist = (list->ray.mapx - list->ray.rayposx + (1 - list->ray.stepx) / 2) / list->ray.raydistx;
	}
	else
		list->ray.perpwalldist = (list->ray.mapy - list->ray.rayposy + (1 - list->ray.stepy) / 2) / list->ray.raydisty;	
}

void			ft_find_wall(t_env *list)
{
	while (list->ray.hit == 0)
	{
		if (list->ray.sidedistx < list->ray.sidedisty)
		{
			list->ray.sidedistx += list->ray.deltadistx;
			list->ray.mapx += list->ray.stepx;
			list->ray.side = 0;
		}
		else
		{
			list->ray.sidedisty += list->ray.deltadisty;
			list->ray.mapy += list->ray.stepy;
			list->ray.side = 1;
		}
		if (list->map[list->ray.mapy][list->ray.mapx] > 0)
			list->ray.hit = 1;
	}
}

void			ft_ray(int x, t_env *list)
{
	while (x < WIDTH)
	{
		list->ray.camerax = 2 * x / (double)(WIDTH) - 1;
		list->ray.rayposx = list->player.x;
		list->ray.rayposy = list->player.y;
		list->ray.raydirx = list->player.dirx + list->player.planex * list->ray.camerax;
		list->ray.raydiry = list->player.diry + list->player.planey * list->ray.camerax;
		list->ray.mapx = (int)(list->ray.rayposx);
		list->ray.mapy = (int)(list->ray.rayposy);
		list->ray.deltadistx = sqrt(1 + (list->ray.raydiry * list->ray.raydiry) \
		/ (list->ray.raydirx * list->ray.raydirx));
		list->ray.deltadisty = sqrt(1 + (list->ray.raydirx * list->ray.raydirx) \
		/ (list->ray.raydiry * list->ray.raydiry));
		list->ray.hit = 0;
		if (list->ray.raydirx < 0)
		{
			list->ray.stepx = -1;
			list->ray.sidedistx = (list->ray.rayposx - list->ray.mapx) * list->ray.deltadistx;
		}
		else
		{
			list->ray.stepx = 1;
			list->ray.sidedistx = (list->ray.mapx + 1 - list->ray.rayposx) * list->ray.deltadistx;
		}
		if (list->ray.raydiry < 0)
		{
			list->ray.stepy = -1;
			list->ray.sidedisty = (list->ray.rayposy - list->ray.mapy) * list->ray.deltadisty;
		}
		else
		{
			list->ray.stepy = 1;
			list->ray.sidedisty = (list->ray.mapy + 1 - list->ray.rayposy) * list->ray.deltadisty;
		}
		ft_find_wall(list);
		ft_find_distance(list);
		x++;
	}
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
	ft_ray(0, list);
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
