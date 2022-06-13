/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelroy <eelroy@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:51:34 by eelroy            #+#    #+#             */
/*   Updated: 2022/06/13 14:49:20 by eelroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	ft_usleep(long long int wait, t_philo *p)
{
	long long int	t;

	t = find_time();
	while (!p->stop)
	{
		if (find_time() - t >= wait)
			break ;
		usleep(500);
	}	
}

long long int	find_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_exit(char *s, int code)
{
	if (s)
		printf("%s\n", s);
	exit (code);
}

void	logger(t_philo *p, char *s)
{
	sem_wait(p->printf_sem);
	printf("%lld %d %s\n", find_time() - p->t_start, p->i, s);
	sem_post(p->printf_sem);
}
