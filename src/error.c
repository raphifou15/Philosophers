/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 02:25:05 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/21 23:46:07 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_msg(int err)
{
	if (err == 1)
		ft_putstr_err("Error\nNumber of arguments are invalid\n");
	if (err == 2)
		ft_putstr_err("Error\nAt least one argument is not a number\n");
	if (err == 2)
		ft_putstr_err("Or the number is a negatif.\n");
	if (err == 3)
		ft_putstr_err("Error\nIf is start by 0 for me the number is invalid\n");
	if (err == 4)
		ft_putstr_err("Error\nMax value that i autorize: 2147483647\n");
	if (err == 5)
		ft_putstr_err("Error\nMalloc failled\n");
	if (err == 6)
		ft_putstr_err("Error\npthread_create fail function ft_philosophers\n");
	if (err == 7)
		ft_putstr_err("Error\npthread_join fail function ft_philosophers\n");
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
