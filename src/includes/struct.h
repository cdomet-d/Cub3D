/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:41:42 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/29 10:12:47 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_queue
{
	t_co	*item;
	size_t	size;
	size_t	frt;
	size_t	end;
}	t_queue;

typedef enum e_cardinal
{
	NO,
	SO,
	WE,
	EA,
}	t_card;

typedef struct s_img
{
	// ptr to xpm
	void			*ptr;
	// path to file
	char			*pto_file;
	// texture width
	int				xpmw;
	// texture height
	int				xpmh;
	// char * containing xpm data
	char			*sxpm;
	// bits per pixel
	int				bpp;
	// lenght of the (char *) sxpm
	int				len;
	int				endian;
}	t_img;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_parser
{
	bool			found_p;
	char			**map;
	short int		ccolor[3];
	short int		fcolor[3];
	long			ceiling;
	long			floor;
	t_card			pcard;
	t_co			msize;
	t_co			p;
	t_img			ea;
	t_img			no;
	t_img			so;
	t_img			we;
	unsigned char	alle_found;
}	t_parser;

typedef struct s_moves
{
	bool			up;
	bool			down;
	bool			left;
	bool			right;
	bool			lturn;
	bool			rturn;
}	t_moves;

// values used to draw the textures in the window
typedef struct s_draw
{
	// vertical iterator
	double	line;
	// wall perceived height
	double	p_height;
	// wall half perceived height
	double	hp_height;
	// used to see if the top of the wall is visible or not
	double	wall_top;
}	t_draw;

// coordinates used to move in char * sxpm
typedef struct t_drawco
{
	// col in which to get pixel in xpmstr
	double		col;
	// line in which to get pixel in xpmstr
	double		line;
	// line incrementer
	double		line_it;
}	t_draw_co;

typedef struct s_ray
{
	void			*mlx;
	void			*win;
	t_parser		map;
	// angle between rays used to draw each pixel column
	double			rayspacing;
	// central ray angle (player)
	double			c_angle;
	// distance from player to screen
	double			d_screen;
	// current ray angle
	double			r_angle;
	// wall currently being textured
	t_img			cwall;
	t_img			img;
	t_moves			moves;
	t_point			p;
	// last horizontal hitpoint
	t_point			hhitpt;
	// last vertical hitpoint
	t_point			vhitpt;
	// coordinates of the last found intersection
	double			i;
	// half-screen width
	double			hs_width;
	// half-screen height
	double			hs_height;
}	t_ray;

#endif
