/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:25:00 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/10/18 11:21:47 by cdomet-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	errjoin(int error_code, char *error_message)
{
	char	*error;
	char	*tmp;

	tmp = ft_strjoin(strerror(error_code), ": ");
	if (!tmp)
		return (perr(0, "Congrats ! The error message crashed."), false);
	error = ft_strjoin(tmp, error_message);
	if (!error)
		return (perr(0, "Congrats ! The error message crashed."), false);
	free(tmp);
	ft_putstr_fd("\033[1;31m", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	free(error);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	return (true);
}

int	verror(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*error_message;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (perr(0, "Congrat ! The error message crashed"), 1);
	error_message = ft_strjoin(tmp, s3);
	if (!error_message)
		return (free(tmp), \
		perr(0, "Congrat ! The error message crashed"), 1);
	free(tmp);
	if (ft_putstr_fd("\033[1;31m", STDERR_FILENO) == -1)
		return (-1);
	if (ft_putstr_fd(error_message, STDERR_FILENO) == -1)
		return (-1);
	free(error_message);
	if (ft_putendl_fd("\033[0m", STDERR_FILENO) == -1)
		return (-1);
	return (1);
}

void	*perr(int error_code, char *error_message)
{
	if (error_code && !error_message)
	{
		ft_putstr_fd("\033[1;31m", STDERR_FILENO);
		ft_putendl_fd(strerror(error_code), STDERR_FILENO);
		ft_putstr_fd("\033[0m", STDERR_FILENO);
	}
	else if (!error_code && error_message)
	{
		ft_putstr_fd("\033[1;31m", STDERR_FILENO);
		ft_putendl_fd(error_message, STDERR_FILENO);
		ft_putstr_fd("\033[0m", STDERR_FILENO);
	}
	else if (error_code && error_message)
		errjoin(error_code, error_message);
	return (NULL);
}
