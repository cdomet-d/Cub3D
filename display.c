/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:29 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/08 17:05:10 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	get_angles(t_data *data)
{
	if (data->map[(int)data->Py][(int)data->Px] == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
	}
	else if (data->map[(int)data->Py][(int)data->Px] == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
	}
	else if (data->map[(int)data->Py][(int)data->Px] == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
	}
	else if (data->map[(int)data->Py][(int)data->Px] == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
	}
	data->camera_plane_x = -1 * data->dir_y;
	data->camera_plane_y = data->dir_x;
	data->ray_angle = 60;//data->P_angle - (FOV / 2);
	data->angle_bt_rays = 60.0 / 1049.0 * 1.0f;
}

void	init_data(t_data *data, char **map)
{
	float	half_fov_radian;

	data->left = true;
	data->map = map;
	data->Px = 3.0f;
	data->Py = 2.0f;
	data->map[(int)data->Py][(int)data->Px] = 'N';
	half_fov_radian = (FOV / 2) * (PI / 180) * 1.0f;
	data->distance_screen = (SCREEN_WIDTH / 2) / tanf(half_fov_radian)* 1.0f;
	get_angles(data);
	data->Px = data->Px + 0.5f;
	data->Py = data->Py + 0.5f;
}

int	init_display(char **map)
{
	t_data	data;

	init_data(&data, map);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	 	return (1);
	data.img.ptr = mlx_new_image(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data.img.ptr)
		return (1);
	data.img.addr = mlx_get_data_addr(data.img.ptr, &data.img.bpp, &data.img.length, &data.img.endian);
	if (!data.img.addr)
	{
		mlx_destroy_image(data.mlx_ptr, data.img.ptr);
		return (1);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!data.win_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}
	// mlx_loop_hook(data.mlx_ptr, &raycasting, &data);
	mlx_hook(data.win_ptr, 2, 1L<<0, &keys, &data);
	mlx_hook(data.win_ptr, 17, 0, &close_win, &data);
	mlx_loop(data.mlx_ptr);
	clean_display(&data);
	return (0);
}
