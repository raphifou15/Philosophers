/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 22:33:34 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/06 03:16:51 by rkhelif          ###   ########.fr       */
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

int	destroy_mutex(t_data_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->nbr_philo)
		pthread_mutex_destroy(&p->forks[i]);
	pthread_mutex_destroy(&p->mutex);
	pthread_mutex_destroy(&p->pr_data_die);
	pthread_mutex_destroy(&p->pr_data_table);
	pthread_mutex_destroy(&p->pr_print);
	pthread_mutex_destroy(&p->wait_all);
	pthread_mutex_destroy(&p->pr_time);
	pthread_mutex_destroy(&p->pr_order);
	pthread_mutex_destroy(&p->block_last_elem);
	pthread_mutex_destroy(&p->pr_temp);
	pthread_mutex_destroy(&p->wave_1);
	pthread_mutex_destroy(&p->wave_2);
	pthread_mutex_destroy(&p->wave_3);
	pthread_mutex_destroy(&p->pr_tour);
	return (0);
}
