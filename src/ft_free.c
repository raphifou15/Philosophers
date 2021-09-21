/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 22:33:34 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/19 01:12:03 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free(t_data_philo *p)
{
	if (p->philo != NULL)
	{
		free(p->philo);
		p->philo = NULL;
	}
	if (p->forks != NULL)
	{
		free(p->forks);
		p->forks = NULL;
	}
	return (0);
}

void	destroy_mutex(t_data_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->nbr_philo)
		pthread_mutex_destroy(&p->forks[i]);
	pthread_mutex_destroy(&p->mutex);
}
