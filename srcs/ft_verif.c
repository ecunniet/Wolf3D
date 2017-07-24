/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 21:42:11 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/24 21:57:08 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

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
		if (!(s[i] == c || s[i] == 'A' || s[i] == '0' || s[i] <= '1') ||
		((s[i] == 'A' || s[i] == '0' || s[i] == '1') && !(s[i + 1] == c ||
		s[i + 1] == '\0')) || ((s[i + 1] == c || s[i + 1] == '\0') &&
		!(s[i] == 'A' || s[i] == '0' || s[i] == '1')))
			ft_error(-6, 0);
		else if ((s[i] == 'A' || (s[i] >= '0' && s[i] <= '9'))
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

static int	ft_verif_x(int xmax_new, int xmax_old)
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

static void	ft_next(t_env *list, char *filename)
{
	if (list->valid > 1)
		ft_error(-6, 0);
	else if (list->valid == 0)
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

static void	ft_verif_map(char *filename, t_env *list)
{
	list->valid = 0;
	list->xmax = -1;
	list->ymax = 0;
	if ((list->fd = open(filename, O_RDONLY)))
	{
		while (get_next_line_first(list->fd, &list->line))
		{
			list->xmax = ft_verif_x(ft_count_x(list->line, ' ', list), \
			list->xmax);
			free(list->line);
			list->ymax++;
			if (list->ymax == 1000000000)
				ft_error(-8, 0);
		}
		if (close(list->fd) == 0)
			ft_next(list, filename);
		else
			ft_error(-1, 0);
	}
	else
		ft_error(0, filename);
}

void		ft_verif_name(char *str, t_env *list)
{
	int			nb;
	int			i;
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
