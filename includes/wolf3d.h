/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <ecunniet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:55:12 by ecunniet          #+#    #+#             */
/*   Updated: 2017/07/20 23:01:54 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdlib.h>
# define WIDTH 960
# define HEIGHT 600
# define A 0
# define D 2
# define RB 15
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define ESC 53
# define MUSIC 46
# define BUFF_SIZEF 1
# define KEYPRESSEVENT 2
# define KEYPRESSMASK (1L << 0)
# define KEYRELEASEEVENT 3
# define KEYRELEASEMASK (1L << 1)
# define DESTROYNOTIFY 17
# define STRUCTURENOTIFYMASK (1L << 17)


typedef	struct		s_pos
{
	double		x;
	double		y;
	double		z;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
}			t_pos;

typedef struct		s_ray
{
	double		rayposx;
	double		rayposy;
	double		raydirx;
	double		raydiry;
	double		camerax;
	int		mapx;
	int		mapy;
	double		sidedistx;
	double		sidedisty;
	int		stepx;
	int		stepy;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int		hit;
	int		side;
}			t_ray;

typedef struct			s_wall
{
	int		lineheight;
	int		drawstart;
	int		drawend;
}				t_wall;

typedef struct			s_music
{
	int		music_on;
	int		pause_on;
}				t_music;

typedef struct			s_cmd
{
	int		viewl;
	int		viewr;
	int		up;
	int		down;
	int		right;
	int		left;
}				t_cmd;

typedef struct			s_env
{
	// pour la fenetre
	int		fd;
	char		*line;
	double		xmax;
	double		ymax;
	int		valid;
	// pour la mlx 
	void		*mlx;
	void		*win;
	void		*img_ptr;
	int		bpp;
	int		size_line;
	int		endian;
	char		*adi;
	int		**map;
	double		movespeed;
	double		rotspeed;
	int				rainbow;
	int				nblr;
	int				modr;
	int				r[6];
	t_ray		ray;
	t_wall		draw;
	t_pos		player;
	t_music		music;
	t_cmd		move;
}				t_env;

void				ft_free(int y, t_env *list);
void				ft_music(t_env *list);
int				ft_exit(t_env *list);
int				ft_key_press(int keycode, t_env *list);
int				ft_key_release(int keycode, t_env *list);
int				ft_loop(t_env *list);
void				ft_error(int i, char *str);
void				ft_ray(int x, t_env *list);
void				ft_verif_name(char *str, t_env *list);
void				ft_verif_map(char *filename, t_env *list);
void				ft_parser(t_env *list, int x, int y);
int				get_next_line_first(const int fd, char **line);

#endif
