/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 22:06:31 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/24 22:15:16 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		ft_error2(int i)
{
	if (i == -8)
		ft_putstr("Invalid map. Too large. 1 000 000 000 lines is the maximum \
height.");
	if (i == -7)
		ft_putstr("Invalid map. Too large. 2 000 000 000 caracters (including \
spaces and line breaks) is the maximum width.");
	if (i == -6)
		ft_putstr("Invalid map.\n");
	if (i == -5)
		ft_putstr("Invalid map. Too small.\n");
	if (i == -4)
		ft_putstr("Invalid map. The character isn't placed on the map.\n");
	if (i == -3)
		ft_putstr("Invalid map. Lines don't have the same length.\n");
	if (i == -2)
		ft_putstr("Invalid map. The first and last lines, just like the first \
and last colomns must be composed of '1'.\n");
}

void			ft_error(int i, char *str)
{
	if (i < -1)
		ft_error2(i);
	if (i == -1)
		ft_putstr("Fail to close file\n");
	if (i == 0)
	{
		ft_putstr("No file");
		ft_putstr(str);
		ft_putchar('\n');
	}
	if (i == 2)
	{
		ft_putstr("Invalid filename: ");
		ft_putstr(str);
		ft_putchar('\n');
	}
	if (i > 2)
		ft_putstr("Wolf3D needs ONLY one map file to start.\n");
	ft_putstr("Usage:\n./wolf3d\n./wolf3d <filename.wolf>\n");
	exit(EXIT_FAILURE);
}
