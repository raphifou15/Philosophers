/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_odd_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:24:09 by rkhelif           #+#    #+#             */
/*   Updated: 2021/10/05 00:21:19 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork_and_display(t_philo *p)
{
	pthread_mutex_lock(p->left);
	display_fork_left_odd(p);
	pthread_mutex_lock(p->right);
	display_fork_right_odd(p);
}

void	take_fork_and_display2(t_philo *p)
{
	pthread_mutex_lock(p->right);
	display_fork_right_odd(p);
	pthread_mutex_lock(p->left);
	display_fork_left_odd(p);
}
