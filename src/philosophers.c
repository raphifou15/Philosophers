/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 02:11:15 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/21 05:22:55 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data_philo *p, char **argv)
{
	if ((p->nbr_philo = ft_atoi_m(argv[1])) == -1)
		return (1);
	if ((p->t_die = ft_atoi_m(argv[2])) == -1)
		return (1);
	if ((p->t_eat = ft_atoi_m(argv[3])) == -1)
		return (1);
	if ((p->t_sleep = ft_atoi_m(argv[4])) == -1)
		return (1);
	if (argv[5] == NULL)
		p->t_philo_must_eat = -2;
	else
	{
		if ((p->t_philo_must_eat = ft_atoi_m(argv[5])) == -1)
			return (1 + err_msg(5));
	}
	p->die = 0;
	return (0);
}


int	init_philo_part2(t_data_philo *p)
{
	int	i;

	i = -1;
	p->philo = malloc(sizeof(t_philo) * p->nbr_philo);
	if (p->philo == NULL)
		return (1 + err_msg(5) + ft_free(p));
	p->forks = malloc(sizeof(pthread_mutex_t) * p->nbr_philo);
	if (p->forks == NULL)
		return (1 + err_msg(5) + ft_free(p));
	while (++i < p->nbr_philo)
		pthread_mutex_init(&p->forks[i], NULL);
	pthread_mutex_init(&p->mutex, NULL);
	i = -1;
	while (++i < p->nbr_philo)
	{
		p->philo[i].data = p;
		p->philo[i].die = 0;
		p->philo[i].mutex = &p->mutex;
		p->philo[i].eating = (unsigned long)p->t_eat;
		p->philo[i].sleeping = (unsigned long)p->t_sleep;
		p->philo[i].num_philo = i + 1;
		p->philo[i].die = p->t_die;
		p->philo[i].nbr_eat = 0;
		p->philo[i].right = &p->forks[i];
		if (i + 1 == p->nbr_philo)
			p->philo[i].left = &p->forks[0];
		else
			p->philo[i].left = &p->forks[i + 1];
	}
	return (0);
}

int		check_if_alive(t_philo *p)
{
	unsigned long	die;

	die = (unsigned long)p->die;

	if (p->data->die == 1)
	{
		pthread_mutex_unlock(p->right);
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(&p->data->mutex);
		return (1);
	}
	if ((time_now() - p->last_meal) >= die)
	{
		printf("\e[15;31mtimestamp: %ld   ",time_now() - p->data->time_begin);
		printf("%d died\e[0m\n", p->num_philo);
		p->data->die = 1;
		pthread_mutex_unlock(p->right);
		pthread_mutex_unlock(p->left);
		pthread_mutex_unlock(&p->data->mutex);
		return (1);
	}
	return (0);
}

void	ft_check_if_die_during_eating(t_philo *p)
{
	unsigned long	time;
	unsigned long	die;

	die = (unsigned long)p->die;

	time = (time_now() - p->last_meal);
	if (time + p->eating >= die)
		p->eating = die - time + 1;
}


void	ft_check_if_die_during_sleeping(t_philo *p)
{
	unsigned long	time;
	unsigned long	die;

	die = (unsigned long)p->die;

	time = (time_now() - p->last_meal);

	if (time + p->sleeping >= die)
	{
		p->sleeping = die - time + 1;
	}
}

void	*routine(void  *pa)
{
	t_philo		*p;
	t_data_philo *pr;

	p = (t_philo *)pa;
	pr = p->data;
	while (p->die > 0)
	{
		if (p->num_philo % 2 == 0)
		{
			pthread_mutex_lock(p->right);
			
			pthread_mutex_lock(&p->data->mutex);
			if (check_if_alive(p) == 1)
				return (NULL);
			printf("\e[11;32mtimestamp: %ld   ",time_now() - pr->time_begin);
			printf("%d has taken a fork right\e[0m\n", p->num_philo);
			pthread_mutex_unlock(&p->data->mutex);
			pthread_mutex_lock(p->left);

			pthread_mutex_lock(&p->data->mutex);
			if (check_if_alive(p) == 1)
				return (NULL);
			printf("\e[1;32mtimestamp: %ld   ",time_now() - pr->time_begin);
			printf("%d has taken a fork left\e[0m\n", p->num_philo);
			pthread_mutex_unlock(&p->data->mutex);
		}
		else
		{

			pthread_mutex_lock(p->left);

			pthread_mutex_lock(&p->data->mutex);
			if (check_if_alive(p) == 1)
				return (NULL);
			printf("\e[1;32mtimestamp: %ld   ",time_now() - pr->time_begin);
			printf("%d has taken a fork left\e[0m\n", p->num_philo);
			pthread_mutex_unlock(&p->data->mutex);

			pthread_mutex_lock(p->right);
			pthread_mutex_lock(&p->data->mutex);
			if (check_if_alive(p) == 1)
				return (NULL);
			printf("\e[11;32mtimestamp: %ld   ",time_now() - pr->time_begin);
			printf("%d has taken a fork right\e[0m\n", p->num_philo);
			pthread_mutex_unlock(&p->data->mutex);
		}

		pthread_mutex_lock(&p->data->mutex);
		if (check_if_alive(p) == 1)
			return (NULL);
		ft_check_if_die_during_eating(p);
		p->last_meal = time_now();
		printf("\e[15;33mtimestamp: %ld   ",time_now() - pr->time_begin);
		printf("%d is eating\e[0m\n", p->num_philo);
		pthread_mutex_unlock(&p->data->mutex);
		usleep(p->eating * 1000);
		//p->die -= 50;
		if (p->num_philo  % 2 == 0)
		{
			pthread_mutex_unlock(p->right);
			pthread_mutex_unlock(p->left);
		}
		else
		{
			pthread_mutex_unlock(p->left);
			pthread_mutex_unlock(p->right);
		}

		pthread_mutex_lock(&p->data->mutex);
		if (check_if_alive(p) == 1)
			return (NULL);
		ft_check_if_die_during_sleeping(p);
		printf("\e[1;36mtimestamp: %ld   ",time_now() - pr->time_begin);
		printf("%d is sleeping\e[0m\n", p->num_philo);
		pthread_mutex_unlock(&p->data->mutex);
		usleep(p->sleeping * 1000);


		pthread_mutex_lock(&p->data->mutex);
		if (check_if_alive(p) == 1)
			return (NULL);
		printf("\e[1;37mtimestamp: %ld   ",time_now() - pr->time_begin);
		printf("%d is thinking\e[0m\n", p->num_philo);
		pthread_mutex_unlock(&p->data->mutex);
	}
	return (NULL);
}

int	ft_philosophers(t_data_philo *p)
{
	int	i;

	i = -1;
	p->time_begin = time_now();
	while (++i < p->nbr_philo)
		p->philo[i].last_meal = time_now();
	i = -1;
	while (++i < p->nbr_philo)
	{
		if (pthread_create(&p->philo[i].th, NULL, routine, (void *)&p->philo[i]) != 0)
			return (1);
	}

	i = -1;
	while (++i < p->nbr_philo)
	{
		if (pthread_join(p->philo[i].th, NULL) != 0)
			return (1);
	}
	return (0);
}



int	main(int argc, char *argv[])
{
	t_data_philo p;
	if (check_error(argc, argv) != 0)
		return (1);
	//philo_data();
	if (init_philo(&p, argv) != 0)
		return (1);
	if (init_philo_part2(&p) != 0)
		return (1);
	if (ft_philosophers(&p) != 0)
		return (1);
/*	
	printf("p.nbr_philo = %d\n", p.nbr_philo);
	printf("p.t_die = %d\n", p.t_die);
	printf("p.t_eat = %d\n", p.t_eat);
	printf("p.t_sleep = %d\n", p.t_sleep);
	printf("p.t_philo_must_eat = %d\n", p.t_philo_must_eat);
	printf("success\n");
*/	
	
	destroy_mutex(&p);
	ft_free(&p);
	return (0);
}
