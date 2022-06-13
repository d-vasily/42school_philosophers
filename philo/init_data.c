/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:52:27 by eelroy            #+#    #+#             */
/*   Updated: 2022/06/13 14:56:55 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	init_forks(t_data *d, t_philo *p)
{
	int	i;

	i = d->n_philo;
	d->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * d->n_philo);
	if (!d->forks)
		return (ft_exit(p, "Error: malloc *forks", -1));
	while (i-- > 0)
	{
		if (pthread_mutex_init(&d->forks[i], NULL) != 0)
		{
			while (++i < d->n_philo)
				pthread_mutex_destroy(&d->forks[i]);
			return (ft_exit(p, "Error: init forks mutex", -1));
		}
	}
	if (pthread_mutex_init(&d->printf, NULL) == 0)
		return (0);
	while (i < d->n_philo)
		pthread_mutex_destroy(&d->forks[i++]);
	return (ft_exit(p, "Error: init printf mutex", -1));
}

void	init_philos(t_data *d, t_philo *p)
{
	int	i;

	p->d->t_start = find_time();
	i = d->n_philo;
	while (--i >= 0)
	{
		p[i].meal_cnt = 0;
		p[i].d = d;
		p[i].eating = 0;
		p[i].i = i + 1;
		p[i].fork[0] = &d->forks[i];
		if (i == 0)
			p[i].fork[1] = &d->forks[d->n_philo - 1];
		else
			p[i].fork[1] = &d->forks[i - 1];
		p[i].t_last_meal = find_time();
	}
}

int	init_data(int argc, char **argv, t_data *d, t_philo **tmp)
{
	t_philo	*p;

	d->forks = NULL;
	d->n_philo = ft_atoi(argv[1]);
	d->t_2die = ft_atoi(argv[2]);
	d->t_2eat = ft_atoi(argv[3]);
	d->t_2sleep = ft_atoi(argv[4]);
	d->n_m_eat = 0;
	d->stop = 0;
	if (argc != 4)
		d->n_m_eat = ft_atoi(argv[5]);
	if (d->n_philo <= 0 || d->t_2die <= 0 || d->t_2eat <= 0 \
	|| d->t_2sleep <= 0 || d->n_m_eat < 0)
		return (ft_exit(NULL, "Error: wrong arguments", -1));
	p = (t_philo *)malloc(sizeof(t_philo) * d->n_philo);
	if (!p)
		return (ft_exit(NULL, "Error: malloc t_philo *p", -1));
	p->d = d;
	if (init_forks(d, p) == -1)
		return (-1);
	init_philos(d, p);
	*tmp = p;
	return (1);
}
