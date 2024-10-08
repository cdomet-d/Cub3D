/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:13:08 by csweetin          #+#    #+#             */
/*   Updated: 2024/10/08 15:23:21 by csweetin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	ft_put_pixel(t_img *img, int colomn, int line, int color)
{
	if (colomn < 0 || colomn >= SCREEN_WIDTH || line < 0 || line >= SCREEN_HEIGHT)
		return ;
	*(int *)(img->addr + (line * img->length + colomn * (img->bpp / 8))) = color;
}
 
void	draw_column(t_data *data, float distance, int colomn)
{
	int	hp;
	int	i;
	int	hr;
	int	half_hp;

	i = 0;
	distance *= 64;
	// printf("distance : %f\n", distance);
	hr = 64 / 2;
	hp = 64.0 * data->distance_screen / distance;
	// printf("hp : %f\n", hp);
	half_hp = hp / 2;
	if ((hr - half_hp) > 0)
		i = hr - half_hp;
	// while (i < (hr - half_hp))
	// {
	// 	ft_put_pixel(&data->img, colomn, i, SKY);
	// 	i++;
	// }
	while (i <= (hr + half_hp))
	{
		ft_put_pixel(&data->img, colomn, i, data->color);
		i++;
	}
	// while (i < SCREEN_HEIGHT)
	// {
	// 	ft_put_pixel(&data->img, colomn, i, GROUND);
	// 	i++;
	// }
}