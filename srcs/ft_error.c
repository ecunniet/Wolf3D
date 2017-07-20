/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 22:06:31 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/20 22:46:38 by ecunniet         ###   ########.fr       */
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
	if (i == -8)
		ft_putstr("Invalid map. Too large. 1 000 000 000 lines is the maximum height.");
	if (i == -7)
		ft_putstr("Invalid map. Too large. 2 000 000 000 caracters (including spaces and line breaks) is the maximum width.");
	if (i == -6)
		ft_putstr("Invalid map.\n");
	if (i == -5)
		ft_putstr("Invalid map. Too small.\n");
	if (i == -4)
		ft_putstr("Invalid map. The character isn't placed on the map.\n");
	if (i == -3)
		ft_putstr("Invalid map. Lines don't have the same length.\n");
	if (i == -2)
		ft_putstr("Invalid map. The first and last lines, just like the first and last colomns must be composed of numbers from 1 to 9.\n");
	if (i == -1)
		ft_putstr("Fail to close file\n");
	if (i == 0)
	{
		ft_putstr("No file");
		ft_putstr(str);
		ft_putchar('\n');
	}
	if (i == 1)
		ft_putstr("Missing file. There is no map for the game.\n");
	if (i == 2)
	{
		ft_putstr("Invalid filename: ");
		ft_putstr(str);
		ft_putchar('\n');
	}
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
		|| ((s[i] == 'A'|| (s[i] >= '0' && s[i] <= '9')) && !(s[i + 1] == c || s[i + 1] == '\0')) || ((s[i + 1] == c || s[i + 1] == '\0') && !(s[i] == 'A' || (s[i] >= '0' && s[i] <= '9'))))
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

static	int		ft_read_file(char **line, char (*mem)[], int fd, int x)
{
	char	tmp[BUFF_SIZEF + 1];
	char	*ptr;
	int		ret;

	while ((ret = read(fd, tmp, BUFF_SIZEF)) > 0)
	{
		tmp[ret] = 0;
		if ((ptr = ft_strchr(tmp, '\n')))
		{
			*ptr = 0;
			ptr++;
			ft_strcpy((char*)mem, ptr);
			*line = (*line == NULL) ? ft_strdup(tmp)
				: ft_strjoin_free(*line, tmp, 1);
			return (1);
		}
		else
		{
			*line = (*line == NULL) ? ft_strdup(tmp)
				: ft_strjoin_free(*line, tmp, 1);
			x++;
		}
		if (x == 1999999999)
		{
			free(line);
			ft_error(-7, 0);
		}
	}
	if (ret == -1)
		return (-1);
	return (0);
}

int				get_next_line_first(const int fd, char **line)
{
	static char		mem[BUFF_SIZEF + 1] = "";
	int				i;
	char			*ptr;

	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	if (ft_strlen(mem) > 0)
	{
		if ((ptr = ft_strchr(mem, '\n')))
		{
			*ptr = 0;
			ptr++;
			*line = ft_strdup(mem);
			ft_strcpy(mem, ptr);
			return (1);
		}
		else
		{
			*line = ft_strdup(mem);
			*mem = 0;
		}
	}
	i = ft_read_file(&(*line), &mem, fd, 0);
	return (i == 0 && *line != NULL) ? 1 : i;
}

void		ft_verif_map(char *filename, t_env *list)
{
	list->valid = 0;
	list->xmax = -1;
	list->ymax = 0;
	if ((list->fd = open(filename, O_RDONLY)))
	{
		while (get_next_line_first(list->fd, &list->line))
		{
			list->xmax = ft_verif_x(ft_count_x(list->line, ' ', list), list->xmax);
			free(list->line);
			list->ymax++;
			if (list->ymax == 1000000000)
				ft_error(-8, 0);
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
