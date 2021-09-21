/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 03:44:24 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/21 22:22:43 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_m(char *str)
{
	long	nbr;
	int		nb;
	int		i;

	i = -1;
	nbr = 0;
	while (str[++i] != '\0' && nbr <= 2147483647)
	{
		nbr *= 10;
		nbr += str[i] - 48;
	}
	if (nbr > 2147483647)
		return (-1 + err_msg(4));
	nb = (int)nbr;
	return (nb);
}

void	ft_putstr_err(char *str)
{
	int	i;

	i = -1;
	if (str == NULL)
		return ;
	while (str[++i] != '\0')
		write(2, &str[i], 1);
}

unsigned long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}
