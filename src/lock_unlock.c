/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_unlock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 04:58:08 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/05 04:59:55 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_unlock_mutex_wave_1(t_philo *p)
{
	 pthread_mutex_lock(&p->data->wave_1);
	 pthread_mutex_unlock(&p->data->wave_1);
}

void	lock_unlock_mutex_wave_2(t_philo *p)
{
	 pthread_mutex_lock(&p->data->wave_2);
	 pthread_mutex_unlock(&p->data->wave_2);
}

void	lock_unlock_mutex_wave_3(t_philo *p)
{
	 pthread_mutex_lock(&p->data->wave_3);
	 pthread_mutex_unlock(&p->data->wave_3);
}
