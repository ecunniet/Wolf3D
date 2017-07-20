/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rainbow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 22:06:14 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/20 23:01:52 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	list->nblr = (int)(list->ymax) / 6;
//	list->modr = (int)(list->ymax) % 6;


void		ft_call_bresenham(t_env *list, int i, int color, int v)
{
	int			tmp;
	int			j;

	// v == 1 dessiner
	if (v == 1 && list->rainbow == 1)
	{
		tmp = i / list->xmax;
		if (list->nblr < 1)
			list->color = *(list->r + tmp);
		else
		{
			j = (tmp / (list->nblr + 1) >= list->modr) ?
			(tmp - list->modr) / list->nblr : tmp / (list->nblr + 1);
			j = (j == 6) ? 5 : j;
			list->color = *(list->r + j);
		}
	}
	else
		list->color = color;
}

}
