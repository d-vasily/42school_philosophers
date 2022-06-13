/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:51:34 by eelroy            #+#    #+#             */
/*   Updated: 2022/06/13 12:14:11 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

long long int	find_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_exit(t_philo *p, char *s, int code)
{
	if (s)
		printf("%s\n", s);
	if (!p)
		return (code);
	if (p->d->forks)
		free(p->d->forks);
	free(p);
	return (code);
}

void	logger(t_philo *p, char *s)
{
	if (p->d->stop)
		return ;
	pthread_mutex_lock(&p->d->printf);
	printf("%lld %d %s\n", find_time() - p->d->t_start, p->i, s);
	pthread_mutex_unlock(&p->d->printf);
}

void	destroy_mutex(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->d->n_philo)
		pthread_mutex_destroy(&p->d->forks[i]);
	pthread_mutex_destroy(&p->d->printf);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
		if (res < 0)
			return (-1);
	}
	if (str[i] != 0)
		return (-1);
	return (res);
}
