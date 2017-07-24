/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 22:37:13 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/24 23:27:47 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_v_or_h(t_env *list)
{
	if (RAY.raydirx < 0)
	{
		RAY.stepx = -1;
		RAY.sidedistx = (RAY.rayposx - RAY.mapx) * RAY.deltadistx;
	}
	else
	{
		RAY.stepx = 1;
		RAY.sidedistx = (RAY.mapx + 1 - RAY.rayposx) * RAY.deltadistx;
	}
	if (RAY.raydiry < 0)
	{
		RAY.stepy = -1;
		RAY.sidedisty = (RAY.rayposy - RAY.mapy) * RAY.deltadisty;
	}
	else
	{
		RAY.stepy = 1;
		RAY.sidedisty = (RAY.mapy + 1 - RAY.rayposy) * RAY.deltadisty;
	}
}

void	ft_ray(int x, t_env *list)
{
	while (x < WIDTH)
	{
		RAY.camerax = 2 * x / (double)(WIDTH) - 1;
		RAY.rayposx = PLAY.x;
		RAY.rayposy = PLAY.y;
		RAY.raydirx = PLAY.dirx + PLAY.planex * RAY.camerax;
		RAY.raydiry = PLAY.diry + PLAY.planey * RAY.camerax;
		RAY.mapx = (int)(RAY.rayposx);
		RAY.mapy = (int)(RAY.rayposy);
		RAY.deltadistx = sqrt(1 + (RAY.raydiry * RAY.raydiry) \
		/ (RAY.raydirx * RAY.raydirx));
		RAY.deltadisty = sqrt(1 + (RAY.raydirx * RAY.raydirx) \
		/ (RAY.raydiry * RAY.raydiry));
		RAY.hit = 0;
		ft_v_or_h(list);
		ft_find_wall(list);
		ft_find_distance(list, x);
		x++;
	}
	mlx_put_image_to_window(list->mlx, list->win, list->img_ptr, 0, 0);
}

void	ft_rotation(t_env *list, double rot, double olddirx, double oldplanex)
{
	PLAY.dirx = olddirx * cos(rot * ROT) - PLAY.diry * sin(rot * ROT);
	PLAY.diry = olddirx * sin(rot * ROT) + PLAY.diry * cos(rot * ROT);
	PLAY.planex = oldplanex * cos(rot * ROT) - PLAY.planey * sin(rot * ROT);
	PLAY.planey = oldplanex * sin(rot * ROT) + PLAY.planey * cos(rot * ROT);
}

void	ft_move(t_env *list, int i, double x, double y)
{
	if (list->map[(int)(PLAY.y + i * (y * MO))][(int)(PLAY.x)] == 0)
		PLAY.y += i * (y * MO);
	if (list->map[(int)(PLAY.y)][(int)(PLAY.x + i * (x * MO))] == 0)
		PLAY.x += i * (x * MO);
}

int		ft_loop(t_env *list)
{
	if (list->move.up > 0)
		ft_move(list, 1, PLAY.dirx, PLAY.diry);
	if (list->move.down > 0)
		ft_move(list, -1, PLAY.dirx, PLAY.diry);
	if (list->move.right > 0)
		ft_move(list, 1, PLAY.planex, PLAY.planey);
	if (list->move.left > 0)
		ft_move(list, -1, PLAY.planex, PLAY.planey);
	if (list->move.viewl > 0)
		ft_rotation(list, 1, PLAY.dirx, PLAY.planex);
	if (list->move.viewr > 0)
		ft_rotation(list, -1, PLAY.dirx, PLAY.planex);
	ft_ray(0, list);
	return (0);
}
