/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 03:44:24 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/19 22:33:27 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_atoi_m(char *str)
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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	if (str == NULL)
		return ;
	while (str[++i] != '\0')
		write(1, &str[i], 1);
}

void	ft_putnbr(int nbr)
{
	long	n;

	n = nbr;
	if (n < 0)
		ft_putchar('-');
	if (n < 0)
		n *= -1;
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putchar((n % 10) + 48);
	}
	else
		ft_putchar(n + 48);
}

unsigned long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	
	return ((unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}


