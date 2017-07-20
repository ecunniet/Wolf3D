/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <ecunniet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:27:38 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/20 23:58:39 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			ft_pixel_put_image(t_env *list, int x, int y, int color)
{
	int tmp;

	tmp = (x + y * WIDTH);
	if (x < WIDTH && y < HEIGHT && y >= 0 && x >= 0)
		*(((int*)list->adi) + tmp) = color;
}

void			ft_draw_wall(t_env *list, int color, int x)
{
	int y;
	int j;

	list->nblr = (list->draw.drawend - list->draw.drawstart) / 6;
	list->modr = (list->draw.drawend - list->draw.drawstart) % 6;
	y = 0;
	while (y < HEIGHT)
	{
		if (list->rainbow == 1)
		{
		/*if (y < list->draw.drawstart)
				ft_pixel_put_image(list, x, y, *(list->r));
			else */
			if (y >= list->draw.drawstart && y < list->draw.drawend)
			{
				if ((y - list->draw.drawstart) / (list->nblr + 1) >= list->modr)
					j = ((y - list->draw.drawstart) - list->modr) / list->nblr;
				else
					j = (y - list->draw.drawstart) / (list->nblr + 1);
				j = (j == 6) ? 5 : j;
				ft_pixel_put_image(list, x, y, *(list->r + j));
			}
			else
				ft_pixel_put_image(list, x, y, 0x000000);
		//	else
			//ft_pixel_put_image(list, x, y, *(list->r + 5));
		}
		else if (y >= list->draw.drawstart && y < list->draw.drawend)
			ft_pixel_put_image(list, x, y, color);
		else
			ft_pixel_put_image(list, x, y, 0x000000);
		y++;
	}
}

void			ft_color(t_env *list, int x)
{
	if (list->ray.side == 1)
	{
		if (list->ray.stepy > 0)
			ft_draw_wall(list, 0xff0000, x);
		else
			ft_draw_wall(list, 0x0000ff, x);
	}
	else
	{
		if (list->ray.stepx > 0)
			ft_draw_wall(list, 0x00ff00, x);
		else
			ft_draw_wall(list, 0xffffff, x);
	}
}


void			ft_find_distance(t_env *list, int x)
{
	if (list->ray.side == 0)
		list->ray.perpwalldist = (list->ray.mapx - list->ray.rayposx + (1 - list->ray.stepx) / 2) / list->ray.raydirx;
	else
		list->ray.perpwalldist = (list->ray.mapy - list->ray.rayposy + (1 - list->ray.stepy) / 2) / list->ray.raydiry;
	list->draw.lineheight = (int)(HEIGHT / list->ray.perpwalldist);
	list->draw.drawstart = HEIGHT / 2 - list->draw.lineheight / 2;
	if (list->draw.drawstart < 0)
		list->draw.drawstart = 0;
	list->draw.drawend = HEIGHT / 2 + list->draw.lineheight / 2;
	if (list->draw.drawend >= HEIGHT)
		list->draw.drawend = HEIGHT - 1;
	ft_color(list, x);
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
		ft_find_distance(list, x);
		x++;
	}
	mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
}

static int		ft_draw_pix(t_env *list)
{
	list->mlx = mlx_init();
	list->win = mlx_new_window(list->mlx, WIDTH, HEIGHT, "Wolf3D");
	list->img_ptr = mlx_new_image(list->mlx, WIDTH, HEIGHT);
	list->adi = mlx_get_data_addr(list->img_ptr, &list->bpp,
	&list->size_line, &list->endian);
	ft_music(list);
	ft_ray(0, list);
	mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
	mlx_hook(list->win, KEYPRESSEVENT, KEYPRESSMASK, &ft_key_press, list);
	mlx_hook(list->win, KEYRELEASEEVENT, KEYRELEASEMASK,
	&ft_key_release, list);
	mlx_hook(list->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, &ft_exit, list);
	mlx_loop_hook(list->mlx, &ft_loop_ok, list);
	mlx_loop(list->mlx);
	return (0);
}

int				main(int argc, char **argv)
{
	t_env	list;

	if (argc == 2)
	{
		list.move.up = 0;
		list.move.down = 0;
		list.move.right = 0;
		list.move.left = 0;
		list.movespeed = 0.1;
		list.rotspeed = 0.05;
		list.rainbow = 0;
		*(list.r) = 0xf40000;
		*(list.r + 1) = 0xffa500;
		*(list.r + 2) = 0xf4f400;
		*(list.r + 3) = 0x00f400;
		*(list.r + 4) = 0x0028f4;
		*(list.r + 5) = 0xa300f4;
		ft_verif_name(argv[1], &list);
		ft_draw_pix(&list);
	}
	else
		ft_error(argc,  0);
	return (0);
}
