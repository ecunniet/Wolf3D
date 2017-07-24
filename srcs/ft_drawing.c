/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 21:57:40 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/24 23:21:15 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		ft_pixel_put_image(t_env *list, int x, int y, int color)
{
	int tmp;

	tmp = (x + y * WIDTH);
	if (x < WIDTH && y < HEIGHT && y >= 0 && x >= 0)
		*(((int*)list->adi) + tmp) = color;
}

static void		ft_draw_wall(t_env *list, int color, int x)
{
	int y;
	int j;

	list->nblr = (DRAW.drawend - DRAW.drawstart) / 6;
	list->modr = (DRAW.drawend - DRAW.drawstart) % 6;
	y = 0;
	while (y < HEIGHT)
	{
		if (list->rainbow == 1 && y >= DRAW.drawstart && y < DRAW.drawend)
		{
			if ((y - DRAW.drawstart) / (list->nblr + 1) >= list->modr)
				j = ((y - DRAW.drawstart) - list->modr) / list->nblr;
			else
				j = (y - DRAW.drawstart) / (list->nblr + 1);
			j = (j == 6) ? 5 : j;
			ft_pixel_put_image(list, x, y, *(list->r + j));
		}
		else if (y >= DRAW.drawstart && y < DRAW.drawend)
			ft_pixel_put_image(list, x, y, color);
		else
			ft_pixel_put_image(list, x, y, 0x000000);
		y++;
	}
}

static void		ft_color(t_env *list, int x)
{
	if (RAY.side == 1)
	{
		if (RAY.stepy > 0)
			ft_draw_wall(list, 0xff0000, x);
		else
			ft_draw_wall(list, 0x0000ff, x);
	}
	else
	{
		if (RAY.stepx > 0)
			ft_draw_wall(list, 0x00ff00, x);
		else
			ft_draw_wall(list, 0xffffff, x);
	}
}

void			ft_find_distance(t_env *list, int x)
{
	if (RAY.side == 0)
		RAY.perpwalldist = (RAY.mapx - RAY.rayposx + (1 - RAY.stepx) / 2) / \
		RAY.raydirx;
	else
		RAY.perpwalldist = (RAY.mapy - RAY.rayposy + (1 - RAY.stepy) / 2) / \
		RAY.raydiry;
	DRAW.lineheight = (int)(HEIGHT / RAY.perpwalldist);
	DRAW.drawstart = HEIGHT / 2 - DRAW.lineheight / 2;
	DRAW.drawend = HEIGHT / 2 + DRAW.lineheight / 2;
	ft_color(list, x);
}

void			ft_find_wall(t_env *list)
{
	while (RAY.hit == 0)
	{
		if (RAY.sidedistx < RAY.sidedisty)
		{
			RAY.sidedistx += RAY.deltadistx;
			RAY.mapx += RAY.stepx;
			RAY.side = 0;
		}
		else
		{
			RAY.sidedisty += RAY.deltadisty;
			RAY.mapy += RAY.stepy;
			RAY.side = 1;
		}
		if (list->map[RAY.mapy][RAY.mapx] > 0)
			RAY.hit = 1;
	}
}
