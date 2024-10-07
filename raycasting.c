/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:02:27 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/07 18:45:41 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

float	get_correct_distance(float horizontal, float vertical, t_data *data)
{
	float	distance;
	float	smallest;
	float 	angle;
	
	distance = 0;
	angle = (90 - data->ray_angle) * 1.0f;
	if (data->left == false)
		angle *= -1;
	if (horizontal < vertical || vertical < 0)
		smallest = horizontal;
	else
		smallest = vertical;
	distance = smallest * cosf(angle * (PI / 180.0f));
	return (distance);
}

int	check_collisions(float x, float y, char **map)
{
	int	i;
	int	j;

	i = y / CUB;
	j = x / CUB;
	if (i < 0 || j < 0 || i > 7 || j > 7 || !map[i][j])
		return (-1);
	if (map[i][j] == '1')
		return (1);
	return (0);
}

float	get_vertical_intersection(t_data *data)
{
	float	Xa;
	float	Ya;
	float	Bx;
	float	By;
	float	PB;
	int		i;

	Xa = CUB;
	if (data->left)//data->ray_angle < 90.0f)
		Xa *= -1;
	Ya = CUB * tanf(data->ray_angle * (PI / 180.0f));
	if (data->P_angle < 90 && data->P_angle > 270)
		Ya *= -1;
	Bx = (int)(data->Px / CUB) * CUB;
	if (data->left)//data->ray_angle < 90)
		Bx -= 1;
	else
		Bx += CUB;
	By = (data->Py) - (fabs((data->Px) - Bx) * tanf(data->ray_angle * (PI / 180.0f)));
	i = check_collisions(Bx, By, data->map);
	while (!i)
	{
		Bx += Xa;
		By += Ya;
		i = check_collisions(Bx, By, data->map);
	}
	if (i == -1)
		PB = -1;
	else
		PB = fabs(data->Px * CUB - Bx) / cosf(data->ray_angle * (PI / 180.0f));
	return (PB);
}

float	get_horizontal_intersection(t_data *data)
{
	float	Xa;
	float	Ya;
	float	Ax;
	float	Ay;
	float	PA;
	int		i;

	Ya = CUB;
	if (data->P_angle < 90 && data->P_angle > 270)
		Ya *= -1;
	Xa = CUB / tanf(data->ray_angle * (PI / 180.0f));
	if (data->left)//data->ray_angle < 90.0f)
		Xa *= -1;
	Ay = (int)(data->Py / CUB) * CUB - 1;
	Ax = data->Px - ((data->Py - Ay) / tanf(data->ray_angle * (PI / 180.0f)));
	i = check_collisions(Ax, Ay, data->map);
	while (!i)
	{
		Ax += Xa;
		Ay += Ya;
		i = check_collisions(Ax, Ay, data->map);
	}
	if (i == -1)
		PA = -1;
	else
		PA = fabs(data->Px - Ax) / cosf(data->ray_angle * (PI / 180.0f));
	return (PA);
}

void	change_side(t_data *data)
{
	data->left = false;
	data->angle_bt_rays *= -1;
}

int	raycasting(t_data *data)
{
	int	i;
	float	horizontal;
	float	vertical;
	float	distance;

	i = 0;
	data->ray_angle = 60;
	while (i < SCREEN_WIDTH)
	{
		if (data->ray_angle >= 90.0f)
			if (data->left)
				change_side(data);
		horizontal = get_horizontal_intersection(data);
		// printf("PA : %f\n", horizontal);
		vertical = get_vertical_intersection(data);
		// printf("PB : %f\n", vertical);
		distance = get_correct_distance(horizontal, vertical, data);
		// printf("i : %d : distance : %f\n", i, distance);
		draw_column(data, distance, i);
		i++;
		data->ray_angle += data->angle_bt_rays;
		// printf("ray angle : %f\n", data->ray_angle);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.ptr, 0, 0);
	return (0);
}

// float angle_radians = data->ray_angle * (PI / 180.0f);

	//  if (fabsf(sinf(angle_radians)) < EPSILON)
    //     return -1;
