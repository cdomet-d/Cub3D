/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:09:25 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/29 13:27:28 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	str_is_num(char	*str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_strlen(str) == 1)
			if (str[i] < '0' || str[i] > '9')
				return (false);
		if ((str[i] != '\n' && (str[i] < '0' || str[i] > '9')))
			return (false);
		i++;
	}
	return (true);
}

static bool	rgb_is_valid(char **rgb)
{
	size_t	i;

	i = 0;
	if (ft_arrlen(rgb) != 3)
		return (perr(EINVAL, "missing RGB value"), false);
	while (rgb[i])
	{
		if (ft_strlen(rgb[i]) > 4 || !str_is_num(rgb[i]))
			return (verror(strerror(EINVAL), ": invalid RGB value: ", \
			rgb[i]), false);
		i++;
	}
	return (true);
}

bool	rgb_to_int(t_parser *map, char **rgb, bool floor)
{
	size_t	i;

	i = 0;
	if (!rgb_is_valid(rgb))
		return (false);
	while (rgb[i])
	{
		if (floor)
		{
			map->fcolor[i] = ft_atoi(rgb[i]);
			if (map->fcolor[i] < 0 || map->fcolor[i] > 255)
				return (verror(strerror(EINVAL), ": flo: invalid RGB value: ", \
				rgb[i]), false);
		}
		else
		{
			map->ccolor[i] = ft_atoi(rgb[i]);
			if (map->ccolor[i] < 0 || map->ccolor[i] > 255)
				return (verror(strerror(EINVAL), ": sky: invalid RGB value: ", \
				rgb[i]), false);
		}
		i++;
	}
	return (true);
}

size_t	int_to_hex(short int color[3])
{
	return (((color[0] & EBYTES) << 16) + ((color[1] & EBYTES) << 8) \
	+ ((color[2]) & EBYTES));
}
