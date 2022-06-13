/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:49:57 by eelroy            #+#    #+#             */
/*   Updated: 2022/06/13 15:00:40 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	ft_usleep(long long int wait, t_philo *p)
{
	long long int	t;

	t = find_time();
	while (!p->d->stop)
	{
		if (find_time() - t >= wait)
			break ;
		usleep(200);
	}	
}

void	*ft_philo(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->i % 2)
		usleep(200);
	p->t_last_meal = find_time();
	while (!p->d->stop)
	{
		logger(p, "is thinking");
		pthread_mutex_lock(p->fork[0]);
		logger(p, "has taken a fork");
		pthread_mutex_lock(p->fork[1]);
		logger(p, "has taken a fork");
		p->t_last_meal = find_time();
		logger(p, "is eating");
		ft_usleep(p->d->t_2eat, p);
		pthread_mutex_unlock(p->fork[p->i % 2]);
		pthread_mutex_unlock(p->fork[p->i % 2 == 0]);
		p->meal_cnt += 1;
		logger(p, "is sleeping");
		ft_usleep(p->d->t_2sleep, p);
	}
	return (NULL);
}

int	start_threads(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->d->n_philo)
	{
		if (pthread_create(&p[i].thread, NULL, ft_philo, (void *)(p + i)) != 0)
		{
			destroy_mutex(p);
			return (ft_exit(p, "Error: create trhead", -1));
		}
		pthread_detach(p[i].thread);
		usleep(10);
	}
	return (0);
}

void	check_if_alive(t_philo *p)
{
	int	i;
	int	all_eat;

	while (!p->d->stop)
	{
		i = -1;
		all_eat = p->meal_cnt;
		while (++i < p->d->n_philo && !p->d->stop)
		{
			if (!p[i].eating && find_time() - p[i].t_last_meal >= p->d->t_2die)
			{
				logger(p + i, "died");
				p->d->stop = 1;
			}
			if (all_eat > p[i].meal_cnt)
				all_eat = p[i].meal_cnt;
		}
		if (p->d->n_m_eat != 0 && all_eat >= p->d->n_m_eat)
			p->d->stop = 1;
	}
	usleep(p->d->t_2eat * 1000);
	destroy_mutex(p);
}

int	main(int argc, char **argv)
{
	t_data	d;
	t_philo	*p;

	if (argc < 5 || argc > 6)
		return (ft_exit(NULL, "Error: wrong number of arguments", -1));
	if (init_data(argc - 1, argv, &d, &p) == -1)
		return (-1);
	if (start_threads(p) == -1)
		return (-1);
	check_if_alive(p);
	return (ft_exit(p, NULL, 0));
}
