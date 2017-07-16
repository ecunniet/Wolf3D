/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 15:48:25 by ecunniet          #+#    #+#             */
/*   Updated: 2017/02/06 15:48:29 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int			ft_verif_x(int xmax_new, int xmax_old)
{
	int		x;
	int		i;

	i = 0;
	x = 0;
	if (xmax_old == -1 && xmax_new == 0)
		ft_error(-5, 0);
	else if (xmax_old == -1 && xmax_new > 0)
		return (xmax_new);
	else if (xmax_new != xmax_old)
		ft_error(-3, 0);
	return (xmax_new);
}

void		ft_error(int i, char *str)
{
	// mauvaise configuration
	if (i == -6)
		ft_putstr("Invalid map.\n");
	// map avec rien ou map trop petite w < 3 ou h < 3
	if (i == -5)
		ft_putstr("Invalid map. Too small.\n");
	// personnage n'est pas place
	if (i == -4)
		ft_putstr("Invalid map. The character isn't placed on the map.\n");
	// pas la meme longueur
	if (i == -3)
		ft_putstr("Invalid map. Lines don't have the same length.\n");
	// dans le PARSER GOGOL !!!!! que des 1 pour les lignes et colomns
	if (i == -2)
		ft_putstr("Invalid map. The first and last lines, just like the first and last colomns must only be composed of '1' or more.\n");
	// probleme de fermeture
	if (i == -1)
		ft_putstr("Fail to close file\n");
	// le fichier n'existe pas
	if (i == 0)
	{
		ft_putstr("No file");
		ft_putstr(str);
		ft_putchar('\n');
	}
	// argc = 1 donc pas de arg
	if (i == 1)
		ft_putstr("Missing file. There is no map for the game.\n");
	// le fichier n'a pas le bon nom
	if (i == 2)
	{
		ft_putstr("Invalid filename: ");
		ft_putstr(str);
		ft_putchar('\n');
	}
	// trop de fichier
	if (i > 2)
		ft_putstr("Wolf3D needs ONLY one map file to start.\n");
	ft_putstr("Usage: ./wolf3d <filename.wolf>\n");
	exit(EXIT_FAILURE);
}


static int	ft_count_x(char const *s, char c, t_env *list)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (s == NULL)
		ft_error(-5, 0);
	while (i < ft_strlen(s))
	{
		if (!(s[i] == c || s[i] == 'A' || (s[i] >= '0' && s[i] <= '9'))
		|| ((s[i] == 'A'|| (s[i] >= '0' && s[i] <= '9')) && !(s[i + 1] == c || s[i + 1] == '\0')))
			ft_error(-6, 0);
		else if ((s[i] == 'A'|| (s[i] >= '0' && s[i] <= '9'))
			&& (s[i + 1] == c || s[i + 1] == '\0'))
		{
			if (s[i] == 'A')
				list->valid++;
			j++;
		}
		i++;
	}
	return (j);
}

void		ft_verif_map(char *filename, t_env *list)
{
	list->valid = 0;
	list->xmax = -1;
	list->ymax = 0;
	if ((list->fd = open(filename, O_RDONLY)))
	{
		while (get_next_line(list->fd, &list->line))
		{
			list->xmax = ft_verif_x(ft_count_x(list->line, ' ', list), list->xmax);
			free(list->line);
			list->ymax++;
		}
		if (close(list->fd) == 0)
		{
			if (list->valid > 1)
				ft_error(-6, 0);
			if (list->valid == 0)
				ft_error(-4, 0);
			if (list->xmax < 3 || list->ymax < 3)
				ft_error(-5, 0);
			if ((list->fd = open(filename, O_RDONLY)))
			{
				ft_parser(list, 0, 0);
				if (close(list->fd) == -1)
					ft_error(-1, 0);
			}
			else
				ft_error(0, filename);
		}
		else
			ft_error(-1, 0);
	}
	else
		ft_error(0, filename);
}

void		ft_verif_name(char *str, t_env *list)
{
	int nb;
	int i;
	static char w[] = ".wolf\0";

	i = 0;
	nb = ft_strlen(str);
	if (nb >= 6)
	{
		while (i < 6)
		{
			if (str[nb - 5 + i] != w[i])
				ft_error(2, str);
			i++;
		}
		ft_verif_map(str, list);
	}
	else
		ft_error(2, str);
}

/*void		ft_free_struct(t_env *list)
{
	free(list->p);
	free(list->tmp);
	free(list->h);
	exit(EXIT_SUCCESS);
}

static void	ft_initrainbow(t_env *list)
{
	list->rainbow = 0;
	list->b_x = 0;
	list->b_y = 0;
	list->b_z = 0;
	*(list->r) = 0xf40000;
	*(list->r + 1) = 0xffa500;
	*(list->r + 2) = 0xf4f400;
	*(list->r + 3) = 0x00f400;
	*(list->r + 4) = 0x0028f4;
	*(list->r + 5) = 0xa300f4;
	list->nblr = (int)(list->ymax) / 6;
	list->modr = (int)(list->ymax) % 6;
}*/
