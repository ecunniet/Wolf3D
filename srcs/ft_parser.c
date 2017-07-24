/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <ecunniet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:48:49 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/24 22:33:36 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_free(int y, t_env *list)
{
	int i;

	i = 0;
	while (i < y)
	{
		free(list->map[i]);
		i++;
	}
	free(list->map);
}

void	ft_parser2(char *ptr, int x, int y, t_env *list)
{
	while (x < list->xmax)
	{
		if ((y == 0 || y == list->ymax - 1 \
					|| x == 0 || x == list->xmax - 1) \
				&& *ptr != '1')
		{
			ft_free(y + 1, list);
			ft_error(-2, 0);
		}
		list->map[y][x] = ft_atoi(ptr);
		if (*ptr == 'A')
		{
			PLAY.x = x;
			PLAY.y = y;
			PLAY.dirx = -1;
			PLAY.diry = 0;
			PLAY.planex = 0;
			PLAY.planey = 0.66;
		}
		ptr++;
		while (*ptr == ' ')
			ptr++;
		x++;
	}
}

void	ft_parser(t_env *list, int x, int y)
{
	char	*ptr;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!(list->map = (int **)malloc(sizeof(int *)
					* list->ymax)))
		exit(EXIT_FAILURE);
	while (get_next_line(list->fd, &list->line))
	{
		if (!(list->map[y] = (int *)malloc(sizeof(int) * list->xmax)))
		{
			ft_free(y - 1, list);
			exit(EXIT_FAILURE);
		}
		x = 0;
		ptr = list->line;
		ft_parser2(ptr, x, y, list);
		free(list->line);
		y++;
	}
}
