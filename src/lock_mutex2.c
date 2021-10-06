/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_mutex2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 04:59:34 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/06 05:02:25 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_mutex_wave_1_pair2(t_philo *p)
{
	pthread_mutex_lock(&p->data->pr_order);
	if (p->num_philo == p->data->order)
	{
		pthread_mutex_unlock(&p->data->pr_order);
		pthread_mutex_lock(&p->data->wave_1);
	}
	else
		pthread_mutex_unlock(&p->data->pr_order);
}
