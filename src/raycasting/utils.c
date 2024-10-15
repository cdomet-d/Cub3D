/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:23:41 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/14 18:17:14 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	clean_display(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
}

double	to_radian(double angle)
{
	return (angle * (PI / 180.0f));
}

double	get_opposite(double adj, double angle)
{
	double	op;
	
	op = tanf(to_radian(angle)) * adj;
	return (op);
}

double	get_adjacent(double opposite, double angle)
{
	double	adj;
	
	adj = opposite / tanf(to_radian(angle));
	return (adj);
}

int	get_quarter(t_data *data)
{
	int	quarter;

	quarter = ((int)data->P_angle / 90) % 4;
	return (quarter);
}

void	leftmost_angle(t_data *data)
{
	int		index_axis;
	double	angle_ref;
	
	index_axis = get_quarter(data);
	angle_ref = 90 * index_axis;
	data->ray_angle = data->P_angle - angle_ref;
	// printf("ray angle : %f\n", data->ray_angle);
}

double	get_distance(t_point *pt, t_data *data)
{
	double	distance;

	// distance = fabs(data->Px /** CUB*/ - pt->distX) / cosf(to_radian(data->ray_angle - 90 * quarter));
	distance = sqrtf(powf((data->Px - pt->distX), 2) + powf((data->Py - pt->distY), 2));
	return (distance);
}

int	on_axis(float angle)
{
	if (angle == 0.0f || angle == 90.0f || angle == 180.0f \
		|| angle == 270.0f || angle == 360.0f)
		return (1);
	return (0);
}

void	normalise_angle(double *angle)
{
	*angle = remainder((*angle + 360), 360);
}