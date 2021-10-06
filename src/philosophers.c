/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 20:57:24 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/05 23:57:19 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philosophers(t_data_philo *p)
{
	p->time_begin = time_now();
	if (p->nbr_philo <= 1)
		return (one_philo_or_less_eat(p));
	if ((p->nbr_philo % 2) == 0)
		return (philo_pair(p, -1));
	if (p->nbr_philo % 2 != 0)
		return (philo_odd(p));
	return (0);
}
