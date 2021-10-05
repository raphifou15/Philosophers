/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_first_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 05:29:12 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/05 05:34:43 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	find_first_elem(t_philo *p)
{
	int	tmp;

	pthread_mutex_lock(&p->data->pr_tour);
	tmp = p->data->tour;
	if (tmp == 0)
	{
		pthread_mutex_lock(&p->data->pr_order);
		p->data->order2 = p->num_philo;
		pthread_mutex_unlock(&p->data->pr_order);
	}
	p->data->tour = 1;
	pthread_mutex_unlock(&p->data->pr_tour);
}

void	find_first_elem2(t_philo *p)
{
	int	tmp;

	pthread_mutex_lock(&p->data->pr_tour);
	tmp = p->data->tour;
	pthread_mutex_unlock(&p->data->pr_tour);
	if (tmp == 0)
	{
		pthread_mutex_lock(&p->data->pr_order);
		p->data->order = p->num_philo;
		pthread_mutex_unlock(&p->data->pr_order);
	}
	pthread_mutex_lock(&p->data->pr_tour);
	p->data->tour = 1;
	pthread_mutex_unlock(&p->data->pr_tour);
}
