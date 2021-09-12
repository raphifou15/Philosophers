/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 02:25:05 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/12 05:00:02 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_msg(int err)
{
	if (err == 1)
		ft_putstr_err("Error\nNumber of arguments are invalid\n");
	if (err == 2)
		ft_putstr_err("Error\nAt least one argument is not a number\n");
	if (err == 3)
		ft_putstr_err("Error\nIf is start by 0 for me is invalid\n");
	return (0);
}


int	check_argv_are_number(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		if (argv[i] == NULL || argv[i][0] == '\0')
			return (1 + err_msg(2));
		j = -1;
		if (argv[i][0] != '\0' && argv[i][1] != '\0' && argv[i][0] == 48)
			return (1 + err_msg(3));
		while (argv[i][++j] != '\0')
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (1 + err_msg(2));
		}
	}
	return (0);
}


int	check_error(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
		return (1 + err_msg(1));
	if (check_argv_are_number(argc, argv) != 0)
		return (1);
	return (0);
}
