/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecunniet <ecunniet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:55:12 by ecunniet          #+#    #+#             */
/*   Updated: 2017/04/25 12:01:54 by ecunniet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <unistd.h>
# define WIDTH 320
# define HEIGHT 200
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define MORE 24
# define LESS 27
# define I 34
# define O 31
# define ESC 53
# define FPS 60
# define ONE 18
# define TWO 19
# define THREE 20
# define PAUSE 36
# define MUSIC 46
# define KEYPRESSEVENT 2
# define KEYPRESSMASK (1L << 0)
# define KEYRELEASEEVENT 3
# define KEYRELEASEMASK (1L << 1)
# define BUTTONPRESS 4
# define BUTTONPRESSMASK (1L << 2)
# define BUTTONRELEASE 5
# define BUTTONRELEASEMASK (1L << 3)
# define MOTIONNOTIFY 6
# define POINTERMOTIONMASK (1L << 6)
# define DESTROYNOTIFY 17
# define STRUCTURENOTIFYMASK (1L << 17)


typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
}					t_point;

typedef	struct		s_pixel
{
	double			x;
	double			y;
	double			z;
}					t_pixel;
/*
typedef struct		s_env
{
	int				color;
	double			zoom;
	int				center_x;
	int				center_y;
	double			angle_y;
	double			angle_x;
	double			angle_z;
	int				b_x;
	int				b_y;
	int				b_z;
	char			*str;
	int				rainbow;
	int				nblr;
	int				modr;
	int				r[6];
}					t_env;

typedef	struct		s_line
{
	int				dx;
	int				dy;
	int				err;
	int				xi;
	int				yi;
	int				xf;
	int				yf;
	int				xinc;
	int				yinc;
	int				i;
}					t_line;
*/

typedef	struct		s_pos
{
	double		x;
	double		y;
	double		z;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
//	double		angle;
//	double		vue;
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

typedef struct		s_music
{
	int				music_on;
	int				pause_on;
}					t_music;

/*
typedef	struct				s_wall
{
	int				h_x;
	int				h_y;
	int				v_x;
	int				v_y;
	int				yb;
	int				xb;
	int				ya;
	int				xa;
	
}					t_wall;
*/
typedef struct				s_cmd
{
	int				pause;
	int				x0;
	int				y0;
	int				on;
	int				up;
	int				down;
	int				right;
	int				left;
	int				z_more;
	int				z_less;
	int				i_more;
	int				i_less;
}					t_cmd;

typedef struct				s_env
{
	// pour la fenetre
	int			fd;
	char			*line;
	double			xmax;
	double			ymax;
	int			valid;
	// pour la mlx 
	void			*mlx;
	void			*win;
	void			*img_ptr;
	int			bpp;
	int			size_line;
	int			endian;
	char			*adi;
	double			zoom;
	int			i;
	int			**map;
	t_ray			ray;
	//t_wall			wall;
	t_pos			player;
	t_music			music;
	t_cmd			move;
}					t_env;

void				ft_error(int i, char *str);
void				ft_verif_name(char *str, t_env *list);
void				ft_verif_map(char *filename, t_env *list);
void				ft_parser(t_env *list, int x, int y);
//void				ft_init(t_env *list);
//int				ft_wolf(t_env *list);
//int				ft_loop_ok(t_env *list);
//int				ft_key_release(int keycode, t_env *list);
//int				ft_key_press(int keycode, t_env *list);
//void				ft_music(t_env *list);
//int				ft_button_release(int button, int x, int y, t_env *list);
//int				ft_button_press(int button, int x, int y, t_env *list);
//int				ft_mouse_motion(int x, int y, t_env *list);
//int				ft_exit(t_env *list);
//void				ft_error(int i, char *str);

#endif
