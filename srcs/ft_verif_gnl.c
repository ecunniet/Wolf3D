/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_gnl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 21:45:03 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/24 21:47:58 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	ft_xlen(int x, char *line)
{
	if (x == 1999999999)
	{
		free(line);
		ft_error(-7, 0);
	}
}

static int	ft_read_file(char **line, char (*mem)[], int fd, int x)
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
		ft_xlen(x, *line);
	}
	return (ret == -1) ? -1 : 0;
}

int			get_next_line_first(const int fd, char **line)
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
