/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:23:11 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/25 22:54:02 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		ft_set_number(char *str, unsigned long n, int size)
{
	int		i;

	i = 0;

	while (n > 9)
	{
		str[size - 1 - i] = ((n % 10) + 48);
		n = n / 10;
		i++;
	}
	str[size - 1 - i] = n + 48;
	str[size] = '\0';
}

static int		ft_size(unsigned long n)
{
	int size;

	size = 0;
	while (n > 9)
	{
		n = n / 10;
		size++;
	}
	size++;
	return (size);
}

char	*ft_itoa(unsigned long n, char *str)
{
	int		size;
	int	i;

	i = -1;
	while (str[++i] != '\0')
		;
	size = ft_size(n);
	ft_set_number(str + i, n, size);
	return (str);
}

void	str_join(char *str1, char *str2)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (str1[++i] != '\0')
		;
	i--;
	while (str2[++j] != '\0')
		str1[++i] = str2[j];
	str1[++i] = str2[j];
}

void ft_bzero(char *str)
{
	int	i;

	i = -1;
	while(str[++i] != '\0')
		str[i] = '\0';
}
