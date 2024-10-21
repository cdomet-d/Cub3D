/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:29:50 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/18 21:46:22 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	vertical_intersection(t_ray *r)
{
	t_point	step;

	step.x = 1;
	step.y = tan(radian(r->r_angle)) * 1;
	r->vhitpt.x = (int)(r->p.x);
	if (cos(radian(r->r_angle)) == 0)
		return (-1);
	if (r->r_angle > 90.0 && r->r_angle < 270.0)
	{
		step.x *= -1;
		r->vhitpt.x -= EP;
	}
	else
	{
		step.y *= -1;
		r->vhitpt.x += 1;
	}
	r->vhitpt.y = r->p.y + tan(radian(r->r_angle)) * (r->p.x - r->vhitpt.x);
	if (find_wall(r, &r->vhitpt, &step) == -1)
		return (-1);
	return (get_distance(&r->vhitpt, r));
}

static double	horizontal_intersection(t_ray *r)
{
	t_point	step;

	step.y = 1;
	step.x = 0;
	if (cos(radian(r->r_angle)) != 0)
		step.x = 1 / tan(radian(r->r_angle));
	r->hhitpt.y = (int)(r->p.y);
	if (sin(radian(r->r_angle)) == 0)
		return (-1);
	if (r->r_angle > 0.0 && r->r_angle < 180.0)
	{
		step.y *= -1;
		r->hhitpt.y -= EP;
	}
	else
	{
		step.x *= -1;
		r->hhitpt.y += 1;
	}
	r->hhitpt.x = r->p.x;
	if (cos(radian(r->r_angle)) != 0)
		r->hhitpt.x = r->p.x + (r->p.y - r->hhitpt.y) / tan(radian(r->r_angle));
	if (find_wall(r, &r->hhitpt, &step) == -1)
		return (-1);
	return (get_distance(&r->hhitpt, r));
}

static double	smallest_distance(double hor, double ver, t_ray *r)
{
	double	smallest;

	smallest = 0.0;
	if (ver == -1 || (hor < ver && hor > 0))
	{
		smallest = hor;
		r->i = r->hhitpt.x;
		if (r->r_angle > 0.0 && r->r_angle < 180.0)
			r->cwall = r->map.no;
		else
			r->cwall = r->map.so;
		return (smallest);
	}
	else if (ver > 0)
	{
		smallest = ver;
		r->i = r->vhitpt.y;
		if (r->r_angle > 90.0 && r->r_angle < 270.0)
			r->cwall = r->map.we;
		else
			r->cwall = r->map.ea;
	}
	return (smallest);
}

static void	fish_eye(double *distance, int i, t_ray *r)
{
	double	angle;

	angle = (i - r->hs_width) * r->rayspacing;
	*distance *= cos(radian(angle));
}

int	raycasting(t_ray *r)
{
	int		i;
	double	horizontal;
	double	vertical;
	double	distance;

	i = 0;
	move(r);
	r->r_angle = r->c_angle + 30.0f;
	normalise_angle(&r->r_angle);
	while (i < S_WIDTH)
	{
		horizontal = horizontal_intersection(r);
		vertical = vertical_intersection(r);
		distance = smallest_distance(horizontal, vertical, r);
		fish_eye(&distance, i, r);
		draw_column(r, distance, i);
		r->r_angle -= r->rayspacing;
		normalise_angle(&r->r_angle);
		i++;
	}
	mlx_put_image_to_window(r->mlx, r->win, \
		r->img.ptr, 0, 0);
	return (0);
}
